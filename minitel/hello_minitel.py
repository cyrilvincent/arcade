import serial

port = "/dev/ttyUSB0"
port = "COM5"

with serial.Serial(port, 1200, parity=serial.PARITY_EVEN, bytesize=7, timeout=5) as socket:
    socket.write(b"Hello Minitel")
    s = socket.read(2)
    print(s)