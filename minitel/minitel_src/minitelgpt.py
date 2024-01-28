import sys
import serial
import time
from openai import OpenAI

port = "/dev/ttyUSB0"
if sys.platform.startswith('win'):
    port = "COM3"

with open("openai.env") as f:
    key = f.read()
client = OpenAI(api_key=key)
chat_model = "gpt-3.5-turbo-1106"

def read_envoi(socket):
    s = b""
    while True:
        c = socket.read(1)
        if c == b'\x1b':
            break
        s += c
    return s.decode("utf8")

def chat(msg: str) -> str:
    completion = client.chat.completions.create(
        model=chat_model,
        messages=[{"role": "user", "content": msg}])
    return completion.choices[0].message.content

with serial.Serial(port, 1200, parity=serial.PARITY_EVEN, bytesize=7, timeout=5) as socket:
    socket.write(b"Minitel GPT\r\n")
    socket.write(b"===========\r\n")
    while True:
        socket.write(b"> ")
        s = read_envoi(socket)
        if s.upper().__contains__("EXIT"):
            quit(0)
        time.sleep(0.01)
        socket.write(b"\r\n")
        res = chat(s)
        socket.write(res.encode("ascii"))
        socket.write(b"\r\n")
        time.sleep(0.01)

