/**
 * ei.cfg Removal/Restore Utility
 * Copyright (C) Kai Liu.  Licensed under a standard BSD-style license.
 * CRC16 code was adapted from 7-Zip, which is licensed under the GPL.
 **/

#include <windows.h>
#include <shlwapi.h>

#define CB_WORK_RANGE   (0x1000000)
#define CCH_WORK_RANGE  (CB_WORK_RANGE/sizeof(WCHAR))
#define CCH_PATH_BUFFER (MAX_PATH << 1)

#define countof(x) (sizeof(x)/sizeof(x[0]))
#pragma intrinsic(memset, memcmp, memcpy)

typedef struct {
	UINT16 ident;
	UINT16 version;
	UINT8 checksum;
	UINT8 reserved;
	UINT16 serial;
	UINT16 crc;
	UINT16 crclen;
	UINT32 location;
} UDFTAG, *PUDFTAG;

typedef struct {
	UINT32 cbExtent;
	BYTE location[6];
	BYTE iu[6];
} LONGALLOC, *PLONGALLOC;

typedef struct {
	UDFTAG tag;
	UINT16 version;
	UINT8 characteristics;
	UINT8 cbIdentifier;
	LONGALLOC ICB;
	UINT16 cbIU;
	BYTE misc[2];
} UDFFILEDESC, *PUDFFILEDESC;


// CRC16 adapted from 7-Zip
void Crc16GenerateTable();
UINT16 Crc16Calc(const void *data, size_t size);
// CRC16 adapted from 7-Zip


#pragma comment(linker, "/version:1.2")
#pragma comment(linker, "/entry:eicfg_remover")
void eicfg_remover( )
{
	PVOID pvBuffer = LocalAlloc(LMEM_FIXED, CB_WORK_RANGE);

	// Set up the OPENFILENAME structure

	TCHAR szFileName[CCH_PATH_BUFFER];

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFilter = TEXT("ISO Disc Image (*.iso)\0*.iso\0");
	ofn.lpstrFile = szFileName;
	ofn.lpstrFile[0] = 0;
	ofn.nMaxFile = CCH_PATH_BUFFER;
	ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

	if (pvBuffer && GetOpenFileName(&ofn))
	{
		HANDLE hFile = CreateFile(
			ofn.lpstrFile,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
			NULL
		);

		UINT64 cbFile;
		DWORD cbOperation;

		if ( hFile != INVALID_HANDLE_VALUE &&
		     GetFileSizeEx(hFile, (PLARGE_INTEGER)&cbFile) &&
		     cbFile > CB_WORK_RANGE &&
		     ReadFile(hFile, pvBuffer, CB_WORK_RANGE, &cbOperation, NULL) &&
		     cbOperation == CB_WORK_RANGE )
		{
			PWSTR pszBuffer = pvBuffer;
			UINT32 posStart;
			PUDFFILEDESC pDesc = NULL;
			int i;

			// Locate the file name entry
			// Roping off an arbitrary 0x100 bytes from both ends lets us avoid
			// the hassles of bounds checking

			for (i = 0x100; i < CCH_WORK_RANGE - 0x100; ++i)
			{
				static const WCHAR szNeedle[] = L"ei.cfg";

				if (StrCmpNI(pszBuffer + i, szNeedle, countof(szNeedle) - 1) == 0)
				{
					posStart = i * sizeof(WCHAR) - sizeof(UDFFILEDESC);
					pDesc = (PUDFFILEDESC)((PBYTE)pvBuffer + posStart);

					if ( pDesc->tag.ident == 257 &&
					     pDesc->tag.version == 2 &&
					     pDesc->tag.reserved == 0 &&
					     pDesc->tag.crclen == sizeof(UDFFILEDESC) - sizeof(UDFTAG) + (sizeof(szNeedle) - sizeof(WCHAR)) &&
					     pDesc->cbIdentifier == sizeof(szNeedle) - 1 &&
					     pDesc->cbIU == 0 &&
					    (pDesc->characteristics == 0 || pDesc->characteristics == 5) )
					{
						// Passed sanity check
						break;
					}
					else
					{
						pDesc = NULL;
					}
				}
			}

			if (pDesc)
			{
				PBYTE pbRaw = (PBYTE)pDesc;

				// Bit 0 is hidden/visible, bit 2 is deletion

				pDesc->characteristics = (pDesc->characteristics) ? 0 : 5;

				// Recalculate the descriptor CRC16

				Crc16GenerateTable();
				pDesc->tag.crc = Crc16Calc(&pDesc->version, pDesc->tag.crclen);

				// Recalculate the tag checksum

				pDesc->tag.checksum = 0;

				for (i = 0; i < 4; ++i)
					pDesc->tag.checksum += pbRaw[i];
				for (i = 5; i < 16; ++i)
					pDesc->tag.checksum += pbRaw[i];

				// Update the ISO file

				SetFilePointer(hFile, posStart, NULL, FILE_BEGIN);
				WriteFile(hFile, pDesc, sizeof(UDFFILEDESC), &cbOperation, NULL);

				MessageBox(
					NULL,
					(pDesc->characteristics) ? TEXT("ei.cfg removed.") : TEXT("ei.cfg restored."),
					TEXT("Success"),
					MB_ICONINFORMATION
				);
			}
			else
			{
				MessageBox(
					NULL,
					TEXT("ei.cfg not found.\n\nMake sure that the disc image is uncorrupted and that the file system is UDF, not Joliet."),
					NULL,
					MB_ICONERROR
				);
			}
		}
		else
		{
			MessageBox(
				NULL,
				TEXT("Error opening or reading the disc image.\n\nMake sure that you have write access, that the disc image is not locked by another application, and that it is uncorrupted."),
				NULL,
				MB_ICONERROR
			);
		}

		if (hFile != INVALID_HANDLE_VALUE)
			CloseHandle(hFile);
	}

	LocalFree(pvBuffer);
	ExitProcess(0);
}


// CRC16 adapted from 7-Zip
#define CRC16_INIT_VAL 0
#define CRC16_GET_DIGEST(crc) (crc)
#define CRC16_UPDATE_BYTE(crc, b) (g_Crc16Table[(((crc) >> 8) ^ (b)) & 0xFF] ^ ((crc) << 8))

#define kCrc16Poly 0x1021
UINT16 g_Crc16Table[256];

void Crc16GenerateTable()
{
  UINT32 i;
  int j;
  for (i = 0; i < 256; i++)
  {
    UINT32 r = (i << 8);
    for (j = 8; j > 0; j--)
      r = ((r & 0x8000) ? ((r << 1) ^ kCrc16Poly) : (r << 1)) & 0xFFFF;
    g_Crc16Table[i] = (UINT16)r;
  }
}

UINT16 Crc16_Update(UINT16 v, const void *data, size_t size)
{
  const BYTE *p = (const BYTE *)data;
  for (; size > 0 ; size--, p++)
    v = CRC16_UPDATE_BYTE(v, *p);
  return v;
}

UINT16 Crc16Calc(const void *data, size_t size)
{
  return Crc16_Update(CRC16_INIT_VAL, data, size);
}
// CRC16 adapted from 7-Zip
