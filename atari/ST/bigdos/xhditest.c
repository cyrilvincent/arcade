/* TABSIZE 4
 * @(#)XHDItest.c
 *
 * Public domain
 *
 * 1995-05-27 von Rainer Seitel, Rastatt, DE.
 * 1995-07-28 Zweisprachig: deutsch wenn _AKP = $??????01??, sonst englisch.
 * 1995-10-17 Alte DOS-Limits werden beim Programmende restauriert.
 * 1995-11-26 Ausgabeumleitung mit dem letzten Argument Ø>[Datei]Æ.
 *            Ohne Laufwerkskennung werden alle angezeigt.
 *            ZusÑtzlich wird Getbpb() benutzt.
 * 1995-11-30 Ohne den Cookie _AKP wird sysbase->os_conf als Sprache benutzt.
 *            Name und Version des XHDI-Plattentreibers wird ausgegeben.
 * 1995-12-14 Der BPB wird geprÅft wie in Big-DOS und Fehler angezeigt.
 *            FÅr die Laufwerke hinter Z: kann auch 1: bis 6: Åbergeben werden.
 * 1996-12-22 Der BPB wird geprÅft wie im neuen Big-DOS.
 *            Laufwerk B: wird nur befragt, wenn es laut _nflops vorhanden ist.
 */


#include <stdio.h>
#include <string.h>
#include "xhdi.h"  /* ØstaticÆ bei getcookie() auskommentieren */


#define E_OK 0
#define EDRVNR -2
#define EINVFN -32
#define FIRST_CLUSTER 2
#define NUM_DRIVES 32
#define DL_FILESYS ('D' << 8 | 15)  /* (XBRA-)Kennung des Dateisystems */
#define DL_VERSION ('D' << 8 | 16)  /* Version des Dateisystems */

#ifndef Dcntl
#define Dcntl(cmd, name, arg) gemdos(0x130, (short)cmd, name, (long)arg)
#endif


long get_os_conf( void )
{
#ifdef __TURBOC__
#define sysbase (*(SYSHDR **)0x4F2)
	return sysbase->os_base->os_palmode;
#else
#define sysbase (*(OSHEADER **)0x4F2)
	return sysbase->os_beg->os_conf;
#endif
}


long get_nflops( void )
{
#define _nflops (*(short *)0x4A6)
	return _nflops;
}


int main( int argc, unsigned char *argv[] )
{
	long german = 0, r, handle = 0, mint = 0, bigdos = 0;
	LONG old_secsiz, old_minfat, old_maxfat, old_minspc, old_maxspc, old_clusts,
	     old_maxsec, old_drives;
	UWORD dos_version, xhdi, major, minor, drive;
	ULONG start_sector = 0, blocks = 0;
	const BPB bpb, *p_bpb;
	unsigned char partid[4];
	unsigned char name[17], version[7] = "";
	UWORD bps, clusiz;


	/* Landessprache bestimmen */
	if (getcookie(0x5F414B50L, &german))  /* _AKP */
		german = (german & 0xFF00) == 0x100;
	else {
		german = Supexec(get_os_conf) >> 1;
		german = german == 1 || german == 8;
	}

	/* Beginnt das letzte Argument mit Ø>Æ Standardausgabe umleiten. */
	if (argc > 1 && argv[argc - 1][0] == '>') {
		argc--;
		if (argv[argc][1] == '\0' || argv[argc][1] == '\r')
			handle = Fcreate("xhditest.log", 0);
		else
			handle = Fcreate(&argv[argc][1], 0);
		if (handle < 0)
			if (german)
				printf("Kann Protokolldatei nicht îffnen! (%ld)\n", handle);
			else
				printf("Can't open log file! (%ld)\n", handle);
		else
			Fforce(1, handle);
	}

	dos_version = Sversion();
	getcookie(0x4D694E54L, &mint);  /* MiNT */
	if (Dcntl(DL_FILESYS, ".", NULL) == 'BDOS') {
		bigdos = Dcntl(DL_VERSION, ".", NULL);
	}
	printf("XHDI-Test 1996-12-22 Rainer Seitel\n\n"\
	       "GEMDOS Version %x.%02x, Big-DOS %ld, MiNT Version %x.%02x\n\n",
	       dos_version & 0xFF, dos_version >> 8, bigdos, (int)mint >> 8, (int)mint & 0xFF);

	if (german)
		strcpy(name, "Plattentreiber");
	else
		strcpy(name, "Hard disk driver");
	xhdi = XHGetVersion();
	if (xhdi)
		XHInqDriver('C'-'A', name, version, NULL, NULL, NULL);
	if (german)
		printf("%s %s hat XHDI %x.%02x", name, version, xhdi >> 8, xhdi & 0xFF);
	else
		printf("%s %s has XHDI %x.%02x", name, version, xhdi >> 8, xhdi & 0xFF);

	if (xhdi) {
		/* Aktuelle DOS-Limits ausgeben. */
		old_secsiz = XHDOSLimits(XH_DL_SECSIZ, 0);
		old_minfat = XHDOSLimits(XH_DL_MINFAT, 0);
		old_maxfat = XHDOSLimits(XH_DL_MAXFAT, 0);
		old_minspc = XHDOSLimits(XH_DL_MINSPC, 0);
		old_maxspc = XHDOSLimits(XH_DL_MAXSPC, 0);
		old_clusts = XHDOSLimits(XH_DL_CLUSTS, 0);
		old_maxsec = XHDOSLimits(XH_DL_MAXSEC, 0);
		old_drives = XHDOSLimits(XH_DL_DRIVES, 0);

		printf(", XHDOSLimits :-");
		if (XHDOSLimits(XH_DL_MAXSEC, 0xFFFFFFL) == EINVFN)
			printf("(");
		else if (XHDOSLimits(XH_DL_MAXSEC, 0xFFFFFFL) != 0xFFFFFFL)
			printf("/");
		else
			printf(")");

		printf("\nXHDI-DOS-Limits XH_DL_SECSIZ: %ld\n", old_secsiz);
		printf("XHDI-DOS-Limits XH_DL_MINFAT: %ld\n", old_minfat);
		printf("XHDI-DOS-Limits XH_DL_MAXFAT: %ld\n", old_maxfat);
		printf("XHDI-DOS-Limits XH_DL_MINSPC: %ld\n", old_minspc);
		printf("XHDI-DOS-Limits XH_DL_MAXSPC: %ld\n", old_maxspc);
		printf("XHDI-DOS-Limits XH_DL_CLUSTS: %ld\n", old_clusts);
		printf("XHDI-DOS-Limits XH_DL_MAXSEC: %ld\n", old_maxsec);
		printf("XHDI-DOS-Limits XH_DL_DRIVES: %ld\n", old_drives);

		/* Bei Plattentreiber mit XHDI 1.20 DOS-Limits einstellen. */
		if (xhdi >= 0x120) {
			if (german)
				printf("XHDI Ú 1.20, versuche Big-DOS-Werte einzustellen:\n");
			else
				printf("XHDI Ú 1.20, try to set Big-DOS limits:\n");
			XHDOSLimits(XH_DL_SECSIZ, 32768L);
			XHDOSLimits(XH_DL_MINFAT, 1);
			XHDOSLimits(XH_DL_MAXFAT, 2);
			XHDOSLimits(XH_DL_MINSPC, 1);
			XHDOSLimits(XH_DL_MAXSPC, 64);
			XHDOSLimits(XH_DL_CLUSTS, 0xFFF0L-FIRST_CLUSTER);
			XHDOSLimits(XH_DL_MAXSEC, 0xFFFFFFL);
			XHDOSLimits(XH_DL_DRIVES, NUM_DRIVES);
			printf("XHDI-DOS-Limits XH_DL_SECSIZ: %ld\n", XHDOSLimits(XH_DL_SECSIZ, old_secsiz));
			printf("XHDI-DOS-Limits XH_DL_MINFAT: %ld\n", XHDOSLimits(XH_DL_MINFAT, old_minfat));
			printf("XHDI-DOS-Limits XH_DL_MAXFAT: %ld\n", XHDOSLimits(XH_DL_MAXFAT, old_maxfat));
			printf("XHDI-DOS-Limits XH_DL_MINSPC: %ld\n", XHDOSLimits(XH_DL_MINSPC, old_minspc));
			printf("XHDI-DOS-Limits XH_DL_MAXSPC: %ld\n", XHDOSLimits(XH_DL_MAXSPC, old_maxspc));
			printf("XHDI-DOS-Limits XH_DL_CLUSTS: %ld\n", XHDOSLimits(XH_DL_CLUSTS, old_clusts));
			printf("XHDI-DOS-Limits XH_DL_MAXSEC: %ld\n", XHDOSLimits(XH_DL_MAXSEC, old_maxsec));
			printf("XHDI-DOS-Limits XH_DL_DRIVES: %ld\n", XHDOSLimits(XH_DL_DRIVES, old_drives));
		}
	} else  /* if (!xhdi) */
		printf("\n");

	/* Die Laufwerkskennungen 1: bis 6: liegen hinter Z:. */
	if (argc > 1 && argv[1][0] >= '1' && argv[1][0] <= '6')
		argv[1][0] += 'Z'-'0';

	for (drive = 0; drive < NUM_DRIVES; drive++) {
		/* Mit _nflops testen ob B: vorhanden ist. */
		if (drive == 1 && (short)Supexec(get_nflops) < 2)
			continue;
		if (argc > 1 && ((argv[1][0] & 0xDF) - 'A') != drive)
			continue;

		if (xhdi) {  /* Ab XHDI 1.10 */
			r = XHInqDev2(drive, &major, &minor, &start_sector, &bpb, &blocks, partid);
			if (r == E_OK || r == EDRVNR) {
				if (partid[0] == 0 && partid[1] == 'D') {  /* MS-DOS-Partition */
					partid[0] = ' ';
					partid[2] += '0';
				}
				if (german)
					printf("\nLaufwerk %c: major %u, minor %u, Start %ld, Grîûe %lu, ID %s,\n",
					       drive + 'A', major, minor, start_sector, blocks, partid);
				else
					printf("\nDrive %c: major %u, minor %u, start %ld, size %lu, ID %s,\n",
					       drive + 'A', major, minor, start_sector, blocks, partid);
				if (r == E_OK) {
					printf("BPB recsiz %u, ", bpb.recsiz);
					printf("BPB clsiz %d, ", bpb.clsiz);
					printf("BPB clsizb %u, ", bpb.clsizb);
					printf("BPB rdlen %d,\n", bpb.rdlen);
					printf("BPB fsiz %d, ", bpb.fsiz);
					printf("BPB fatrec %d, ", bpb.fatrec);
					printf("BPB datrec %d, ", bpb.datrec);
					printf("BPB numcl %u, ", bpb.numcl);
					printf("BPB bflags %d\n", bpb.bflags);
				}
			}
		}

		p_bpb = Getbpb(drive);
		if (p_bpb) {
			if (german)
				printf("\nLaufwerk %c: ", drive + 'A');
			else
				printf("\nDrive %c: ", drive + 'A');
			printf("BPB recsiz %u, ", p_bpb->recsiz);
			printf("BPB clsiz %d, ", p_bpb->clsiz);
			printf("BPB clsizb %u, ", p_bpb->clsizb);
			printf("BPB rdlen %d,\n", p_bpb->rdlen);
			printf("BPB fsiz %d, ", p_bpb->fsiz);
			printf("BPB fatrec %d, ", p_bpb->fatrec);
			printf("BPB datrec %d, ", p_bpb->datrec);
			printf("BPB numcl %u, ", p_bpb->numcl);
			printf("BPB bflags %d\n", p_bpb->bflags);

			/* BPB wie in Big-DOS auf sinnvolle Werte testen. */

			bps    = p_bpb->recsiz;
			clusiz = p_bpb->clsiz;

			if (bps < 128 || (bps & (bps - 1)))  /* Zweierpotenz ab 128 */
				if (german)
					printf("Sektorgrîûe ungÅltig!\n");
				else
					printf("Sector size invalid!\n");

			if (clusiz != 1 && clusiz != 2 && clusiz != 4 && clusiz != 8
			   && clusiz != 16 && clusiz != 32 && clusiz != 64)
				if (german)
					printf("Sektoren pro Cluster ungÅltig!\n");
				else
					printf("Sectors per cluster invalid!\n");

			if (bps * clusiz != p_bpb->clsizb)
				printf("BPB.recsiz * BPB.clsiz != BPB.clsizb\n");

			if (p_bpb->rdlen > 14 * clusiz)
				printf("BPB.rdlen > 14 * BPB.clsiz\n");

			if (bps / 32 * p_bpb->rdlen > 2032)
				printf("BPB.recsiz / 32 * BPB.rdlen > 2032\n");

			if (p_bpb->fatrec + p_bpb->fsiz + p_bpb->rdlen != p_bpb->datrec)
				printf("BPB.fatrec + BPB.fsiz + BPB.rdlen != BPB.datrec\n");

			if (!(p_bpb->bflags & 1)) {
				if (p_bpb->fsiz < (p_bpb->numcl + FIRST_CLUSTER
				             + (p_bpb->numcl + FIRST_CLUSTER) / 2 + bps - 1) / bps)
					if (german)
						printf("Grîûe der 12-Bit-FAT zu klein! Minix-Dateisystem oder TSFM.CPX?\n");
					else
						printf("Size of 12-bit FAT too small! Minix file system or TSFM.CPX?\n");
			} else
				if (p_bpb->fsiz < ((p_bpb->numcl + FIRST_CLUSTER) * 2L + bps - 1) / bps)
					if (german)
						printf("Grîûe der 16-Bit-FAT zu klein! Minix-Dateisystem?\n");
					else
						printf("Size of 16-bit FAT too small! Minix file system?\n");

			if (p_bpb->fsiz > 256)
				printf("BPB.fsiz > 256\n");

			if (p_bpb->numcl == 0)  /* Fehler in HDDRIVER bis 4.50 */
				printf("BPB.numcl = 0! HDDRIVER Û 4.50?\n");

			if (!(p_bpb->bflags & 1) && p_bpb->numcl > 0xFF0-FIRST_CLUSTER)
				if (german)
					printf("Zu viele Cluster fÅr eine 12-Bit-FAT!\n");
				else
					printf("Too many clusters for a 12-bit FAT!\n");

			if (p_bpb->numcl > 0xFFF0U-FIRST_CLUSTER)
				if (german)
					printf("Zu viele Cluster fÅr eine 16-Bit-FAT!\n");
				else
					printf("Too many clusters for a 16-bit FAT!\n");

			if (p_bpb->bflags & ~3)
				if (german)
					printf("BPB.bflags ungÅltig!\n");
				else
					printf("BPB.bflags invalid!\n");
		}
	}  /* for (drive) */

	/* Wenn keine Ausgabeumleitung, dann auf Tastendruck warten. */
	if (handle <= 0)  Cconin();  /* braucht 700 Byte weniger als getchar() */

	return 0;
}
