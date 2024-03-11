import time
import sys
import serial
import os

class MinitelMenu:

    def __init__(self, baudrate=1200):
        self.port = self.get_port()
        self.baudrate = baudrate
        self.connect()

    def connect(self):
        self.socket = serial.Serial(self.port, self.baudrate, parity=serial.PARITY_EVEN, bytesize=7, timeout=5)

    def close(self):
        self.socket.close()

    def get_port(self):
        if sys.platform.startswith('win'):
            return "COM3"
        else:
            return "/dev/ttyUSB0"

    def read_envoi(self):
        s = b""
        while True:
            c = self.socket.read(1)
            print(c)
            if c == b'\x1b' or c == b'\x13':
                break
            s += c
        return s.decode("utf8")

    def read_char(self):
        c = self.socket.read(1)
        print(c)
        return c.decode("utf8")

    def writeln(self, s):
        self.socket.write(s + b"\r\n")

    def write(self, s):
        self.socket.write(s)

    def clear(self):
        self.socket.write(b"\033\143")

    def mode_ta(self, mode_p=1):
        self.writeln(b"")
        self.writeln(b"FNCT+T A")
        self.writeln(b"FNCT+T E")
        if mode_p == 1:
            self.writeln(b"FNCT+P 1")
        else:
            self.writeln(b"FNCT+P 4")

    def mode_tv(self, mode_p=1):
        self.writeln(b"FNCT+T V")
        self.writeln(b"FNCT+T E")
        if mode_p == 1:
            self.writeln(b"FNCT+P 1")
        else:
            self.writeln(b"FNCT+P 4")

    def annuaire(self):
        print("Annuaire")
        self.close()
        time.sleep(5)
        os.chdir("/home/pi/pynitel")
        os.system("python annu.py")
        time.sleep(1)
        self.connect()
        self.writeln(b"\n\n")

    def linux(self):
        print("Linux")
        self.mode_ta(mode_p=4)
        self.writeln(b"sudo reboot et FNCT+P 1 pour revenir au menu")
        self.writeln(b"Login : pi")
        self.writeln(b"Mot de passe : raspberry")
        self.close()
        time.sleep(15)
        os.chdir("/home/pi")
        print("Start Linux")
        os.system("bash linux.sh")
        sys.exit()

    def hello(self):
        print("Hello")
        self.mode_ta()
        self.close()
        time.sleep(5)
        os.chdir("/home/pi")
        os.system("python hello_minitel.py")
        time.sleep(1)
        self.connect()

    def starwars(self):
        print("StarWars")
        self.mode_ta(mode_p=4)
        self.writeln(b"bash starwars.sh")
        time.sleep(15)
        self.close()
        os.chdir("/home/pi")
        print("Start Linux")
        os.system("bash linux.sh")
        sys.exit()

    def google(self):
        print("Google")
        self.mode_ta(mode_p=4)
        self.writeln(b"Lynx")
        time.sleep(15)
        self.close()
        os.chdir("/home/pi")
        print("Start Lynx")
        os.system("./lynx www.google.fr")
        sys.exit()

    def ulla(self):
        print("Ulla")
        # Il faut follower des users sur mastodon
        self.close()
        time.sleep(5)
        os.chdir("/home/pi/pynitel")
        os.system("python ulla.py")
        time.sleep(1)
        self.connect()

    def ascii(self):
        print("Ascii")
        self.mode_ta()
        self.close()
        time.sleep(5)
        os.chdir("/home/pi")
        os.system("python ascii.py")
        time.sleep(1)
        self.connect()

    def history(self):
        print("History")
        self.mode_ta()
        self.close()
        time.sleep(5)
        os.chdir("/home/pi")
        os.system("python history.py")
        time.sleep(1)
        self.connect()

    def gpt(self):
        print("GPT")
        self.close()
        time.sleep(1)
        os.chdir("/home/pi")
        os.system("python minitelgpt.py")
        time.sleep(1)
        self.connect()

    def start(self):
        print("Start minitel menu")
        self.clear()
        while True:
            self.writeln(b"Minitel 2024 par Cyril")
            self.writeln(b"======================")
            self.writeln(b"")
            self.writeln(b"Services disponibles : 3611, 3615 LINUX HELLO STARWARS ULLA ASCII HISTORY GPT GOOGLE")
            self.write(b"Numero : ")
            s = self.read_envoi().upper()
            if s.__contains__("EXI") or s == "":
                self.writeln(b"\r\nExit")
                time.sleep(1)
                sys.exit(0)
            self.writeln(b"")
            if s == "3611":
                self.annuaire()
            else:
                self.write(b"Service : ")
                s = self.read_envoi().upper()
                print("Select "+s)
                if s.__contains__("HEL"):
                    self.hello()
                elif s.__contains__("LIN"):
                    self.linux()
                elif s.__contains__("STA"):
                    self.starwars()
                elif s.__contains__("ULL"):
                    self.ulla()
                elif s.__contains__("ASC"):
                    self.ascii()
                elif s.__contains__("HIS"):
                    self.history()
                elif s.__contains__("GPT"):
                    self.gpt()
                elif s.__contains__("GOO"):
                    self.google()
            self.writeln(b"")

if __name__ == '__main__':
    print("Minitel Menu")
    print("============")
    print()
    print("FNCT+T V : mode videotext (annuaire, menu, par défaut)")
    print("FNCT+T E : mode terminal (linux, menu)")
    print("FNCT+P 1 : 1200 bauds (annuaire, menu, par défaut)")
    print("FNCT+P 4 : 4800 bauds (linux)")
    m = MinitelMenu()
    m.start()

