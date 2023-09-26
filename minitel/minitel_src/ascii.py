import art
import serial
import sys
import time

s = "\n\n"
s += art.text2art("ASCII Art", "big")
s += "\n\n"
while True:
    s += "Matis 22/05/2010".center(80)
    s += "\n\n"
    with open("ascii/matis.txt") as f:
        s += f.read()
    s += "\n\n"
    s += "Elisa 02/06/2006".center(80)
    s += "\n\n"
    with open("ascii/elisa.txt") as f:
        s += f.read()
    s += "\n\n"
    s += "Souad 07/09/1975".center(80)
    s += "\n\n"
    with open("ascii/souad.txt") as f:
        s += f.read()
    s += "\n\n"
    s += "Cyril 15/11/1972".center(80)
    s += "\n\n"
    with open("ascii/cyril.txt") as f:
        s += f.read()
    s += "\n\n"
    print(s)

    if sys.platform.startswith('win'):
        port = "COM3"
    else:
        port = "/dev/ttyUSB0"
    socket = serial.Serial(port, 1200, parity=serial.PARITY_EVEN, bytesize=7, timeout=5)
    rows = s.split("\n")
    for row in rows:
        b = row.encode("ascii")
        time.sleep(0.1)
        socket.write(b)
        socket.write(b"\r\n")
    s = "\n\n"

