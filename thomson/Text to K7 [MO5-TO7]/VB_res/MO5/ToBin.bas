Attribute VB_Name = "ToBin"
Option Explicit
Private Declare Function GetLongPathNameA Lib "kernel32.dll" (ByVal lpszShortPath As String, ByVal lpszLongPath As String, ByVal cchBuffer As Long) As Long
Private Declare Sub CopyMemoryS Lib "kernel32" Alias "RtlMoveMemory" (lpvDest As Any, ByVal lpvSource As String, ByVal cbCopy As Long)
Private Declare Sub CopyMemory Lib "kernel32" Alias "RtlMoveMemory" (lpvDest As Any, lpvSource As Any, ByVal cbCopy As Long)

Dim Lix As Integer
Dim OFFStart As Long
Dim ComDos As String

Sub Main()
ComDos = ClrCmd
If Trim(ComDos) = "" Then GoTo help
On Error GoTo help:
If Dir(Trim(ComDos)) = "" Then GoTo help
On Error Resume Next
 Check_Moffset
 Exit Sub
help:
MsgBox "TEXT2K7_MO5 NOMDUFICHIERTEXT.TXT" & vbCrLf & "Donne -> NOMDUFICHIER_MO5.K7", vbCritical, "Aide :"

End Sub

Sub Check_Moffset()
Dim Line As String
Dim offset1 As Long, offset2 As Long, NbLine As Long

Dim Buffer() As Byte
Dim Buffer2() As Byte
Dim CRCbuffer() As Byte

Dim Codes As Long, NbCodes As Integer
Dim a As Long

Dim K7Header(34) As Byte
Dim BlocHeader(19) As Byte
Dim Footer As Byte

ReDim Buffer(0)
ReDim Buffer2(1)

NbLine = 0
offset1 = -1
Lix = FreeFile
If Dir(Trim(ComDos)) = "" Then Stop
Open Trim(ComDos) For Binary As Lix

ReDim Buffer(LOF(Lix) - 1)
Get #Lix, 1, Buffer
Close #Lix

ReDim Preserve Buffer2(0)
Buffer2(0) = &HD

For a = 0 To UBound(Buffer)

Select Case Buffer(a)
Case &HA
Case Else
                 ReDim Preserve Buffer2(UBound(Buffer2) + 1)
                 Buffer2(UBound(Buffer2)) = Buffer(a)
                 
   If Buffer2(UBound(Buffer2) - 1) = &HD And Buffer2(UBound(Buffer2)) = &HD Then
   ReDim Preserve Buffer2(UBound(Buffer2) - 1)
   End If

End Select
Next a

If Buffer2(UBound(Buffer2)) <> &HD Then
                ReDim Preserve Buffer2(UBound(Buffer2) + 1)
                Buffer2(UBound(Buffer2)) = &HD
End If



Lix = FreeFile
Dim SPECname As String
Dim TmpName As String * 8
SPECname = UCase(Cut_attr(Cut_Name(Trim(ComDos))))
If Len(SPECname) > 8 Then TmpName = Left(SPECname, 8) Else TmpName = SPECname


Dim Header(23) As Byte

For a = 0 To 15: K7Header(a) = 1: Next
K7Header(16) = 60
K7Header(17) = &H5A
K7Header(18) = 0
K7Header(19) = &H10
CopyMemoryS K7Header(20), TmpName, 8
K7Header(28) = Asc("B")
K7Header(29) = Asc("A")
K7Header(30) = Asc("S")
K7Header(31) = 0
K7Header(32) = 255
K7Header(33) = 255

ReDim Preserve CRCbuffer(13)
CopyMemory CRCbuffer(0), K7Header(20), 14
K7Header(34) = CRC8(CRCbuffer(), 0)



For a = 0 To 15: BlocHeader(a) = 1: Next
BlocHeader(16) = 60
BlocHeader(17) = &H5A
BlocHeader(18) = 1
BlocHeader(19) = 255  ' Bloc Lenght.

Header(23) = 255

On Error GoTo K7Locked:
If Dir(SPECname & "_MO5.K7") <> "" Then Kill (SPECname & "_MO5.K7")

Dim ExtBuffer() As Byte



Open SPECname & "_MO5.K7" For Binary As Lix
Put #Lix, 1, K7Header

For a = 0 To (UBound(Buffer2) \ 254) * 254 Step 254

If UBound(Buffer2) - a < 254 Then
    ReDim ExtBuffer((UBound(Buffer2) Mod 254))
    CopyMemory ExtBuffer(0), Buffer2((UBound(Buffer2) \ 254) * 254), (UBound(Buffer2) Mod 254) + 1
    BlocHeader(19) = CByte(((UBound(Buffer2)) Mod 254) + 3)  ' Bloc Lenght.
Else
    ReDim ExtBuffer(253)
    CopyMemory ExtBuffer(0), Buffer2(a), 254
    BlocHeader(19) = 0
End If

Dim CRCbloc As Long
CRCbloc = CRC8(ExtBuffer, 0)

If BlocHeader(19) = 1 Then CRCbloc = CByte((CRCbloc - IIf((CRCbloc - BlocHeader(19)) < 0, -255, BlocHeader(19))) And 255)


Put #Lix, , BlocHeader
Put #Lix, , ExtBuffer
Put #Lix, , CByte(CRCbloc)
Next a

BlocHeader(18) = 255
BlocHeader(19) = 2
Put #Lix, , BlocHeader
Footer = 0
Put #Lix, , Footer
Close #Lix
Err.Clear

Exit Sub
K7Locked:
MsgBox "Le fichier " & SPECname & "_MO5.K7" & vbCrLf & "est vérouillé par une autre application", vbCritical, "Aide :"

End Sub

' Retrive name in a long file name string ( "c:\vb\tmp\file.txt" -> "file.txt" )
Public Function Cut_Name(ByRef Ln_file As String) As String
Dim LastSlash, scan_path As Integer
Dim char_path As String * 1
Dim lng_file As String
lng_file = GetLongPathName(Ln_file)
Ln_file = lng_file

'If Ln_file = "" Then Cut_Name = "": Exit Function
If InStr(Ln_file, "\") = 0 Then Cut_Name = Ln_file: Exit Function
   
    scan_path = Len(Ln_file)
    Do While InStr(1, Mid(Ln_file, scan_path, 1), "\", vbBinaryCompare) = 0
     scan_path = scan_path - 1
    Loop
 LastSlash = scan_path
Cut_Name = Trim(Right(Ln_file, Len(Ln_file) - LastSlash))

End Function

Public Function GetLongPathName(Shortpath As String) As String
   Dim s As String
   Dim i As Long
   
   i = 255
   s = String(i, 0)
   GetLongPathNameA Shortpath, s, i
   
   GetLongPathName = Left$(s, InStr(s, Chr$(0)) - 1)
End Function

' Internal function cut attributes "disk.TXT" = "disk"
Public Function Cut_attr(char As String) As String
Dim cmp
For cmp = Len(char) To 1 Step -1
If Mid(char, cmp, 1) = "." Then Cut_attr = Mid(char, 1, cmp - 1): Exit For
If Mid(char, cmp, 1) = "\" Then Cut_attr = char: Exit For
Next cmp
End Function

Private Function CRC8(BufferCrC() As Byte, CRC As Long) As Byte
Dim a As Long
For a = 0 To UBound(BufferCrC)
CRC = (CRC - BufferCrC(a)) And 255
Next a
CRC8 = CByte(CRC)
End Function

Private Function ClrCmd() As String
Dim a
ClrCmd = ""
If Command$ = "" Then Exit Function
For a = 1 To Len(Command$)
If Mid(Command$, a, 1) <> Chr$(34) Then ClrCmd = ClrCmd + Mid(Command$, a, 1)
Next
ClrCmd = GetLongPathName(ClrCmd)
End Function

