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
 Check_Moffset
 Exit Sub
help:
MsgBox "TEXT2K7_TO7 NOMDUFICHIERTEXT.TXT" & vbCrLf & "Donne -> NOMDUFICHIER_TO7.K7", vbCritical, "Aide :"
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
Dim BlocHeader(13) As Byte
Dim Footer As Byte

ReDim Buffer(0)
ReDim Buffer2(1)

NbLine = 0
offset1 = -1
Lix = FreeFile

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

For a = 0 To 9: K7Header(a) = 255: Next
K7Header(10) = 1
K7Header(11) = 60
K7Header(12) = 0
K7Header(13) = 20
CopyMemoryS K7Header(14), TmpName, 8
K7Header(22) = Asc("B")
K7Header(23) = Asc("A")
K7Header(24) = Asc("S")
K7Header(26) = 255
K7Header(27) = 255

ReDim Preserve CRCbuffer(20)
CopyMemory CRCbuffer(0), K7Header(13), 21
K7Header(34) = CRC8(CRCbuffer())



For a = 0 To 9: BlocHeader(a) = 255: Next
BlocHeader(10) = 1
BlocHeader(11) = 60
BlocHeader(12) = 1
BlocHeader(13) = 255  ' Bloc Lenght.

Header(23) = 255


If Dir(SPECname & "_TO7.K7") <> "" Then Kill (SPECname & "_TO7.K7")

Dim ExtBuffer() As Byte

On Error GoTo K7Locked:

Open SPECname & "_TO7.K7" For Binary As Lix
Put #Lix, 1, K7Header

For a = 0 To (UBound(Buffer2) \ 255) * 255 Step 255

If UBound(Buffer2) - a < 255 Then
    ReDim ExtBuffer((UBound(Buffer2) Mod 255))
    CopyMemory ExtBuffer(0), Buffer2((UBound(Buffer2) \ 255) * 255), (UBound(Buffer2) Mod 255) + 1
    BlocHeader(13) = CByte((UBound(Buffer2) Mod 255) + 1) ' Bloc Lenght.
Else
    ReDim ExtBuffer(254)
    CopyMemory ExtBuffer(0), Buffer2(a), 255
End If

Dim CRCbloc As Long
CRCbloc = CRC8(ExtBuffer)
CRCbloc = (CRCbloc + CLng(BlocHeader(13)) + 1) And 255

Put #Lix, , BlocHeader
Put #Lix, , ExtBuffer
Put #Lix, , CByte(CRCbloc)
Next a
BlocHeader(10) = 1
BlocHeader(11) = 60
BlocHeader(12) = 255
BlocHeader(13) = 0
Put #Lix, , BlocHeader
Footer = 255
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

Private Function CRC8(BufferCrC() As Byte) As Byte
Dim a As Long
Dim CRC As Long
For a = 0 To UBound(BufferCrC)
CRC = (CRC + BufferCrC(a)) And 255
Next a
CRC8 = CByte(CRC)
End Function

Private Function ClrCmd() As String
Dim a
ClrCmd = ""
If Command$ = "" Then Exit Function
'MsgBox Command$, vbCritical, "Command :"

For a = 1 To Len(Command$)
If Mid(Command$, a, 1) <> Chr$(34) Then ClrCmd = ClrCmd + Mid(Command$, a, 1)
Next
ClrCmd = GetLongPathName(ClrCmd)
End Function

