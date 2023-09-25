import time
import sys
import serial
import glob

if sys.platform.startswith('win'):
    port = "COM3"
elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
    port = "/dev/ttyUSB0"

#FNCT+T puis A, (T = Teleinformatique, A = Ascii)
#FNCT+T puis E désactive l'echo local ?
#FNCT+P puis 4 = 4800 bauds
#FNCT+T V active le mode videotext
#FNCT E F = 40 colonnes
#Envoi = \x1b

def read_envoi(socket):
    s = b""
    while True:
        c = socket.read(1)
        print(c)
        if c == b'\x1b':
            break
        s += c
    return s.decode("utf8")

with serial.Serial(port, 1200, parity=serial.PARITY_EVEN, bytesize=7, timeout=5) as socket:
    socket.write(b"\033\143") #Clear
    socket.write(b"Hello Minitel\r\nCyril\r\n")
    #s = socket.read(2)
    s = read_envoi(socket)
    print(s)
    time.sleep(0.1)
    socket.write(b"\r\n")