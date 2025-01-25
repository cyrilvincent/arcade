import serial
import serial.tools.list_ports
import time
import random

serial_port = serial.tools.list_ports.comports()
for port in serial_port:
    print(f"{port}")

#print(bytes([0,10]))


port = serial.Serial("COM3", baudrate=1200, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE)
print(port)

# res = port.read(2)
# print(res)

port.write(b"Hello\n")
time.sleep(1)
port.write(b"\x1a")
for i in range(10000):
    c = random.randint(0,255)
    port.write(bytes([c]))
    print(c)
port.close()


