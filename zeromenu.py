from subprocess import run
import os

os.chdir("/home/pi")
print()
print("Welcome to the Cyril's Arcade")
print("=============================")
print("Street Fighter II: [Enter]")
print("1942: [A+Enter]")
s = input()
s = s.upper()
cmd = ["/opt/retropie/supplementary/runcommand/runcommand.sh", "0", "_SYS_", "arcade",  "/home/pi/Retropie/roms/arcade/"]
if s == "A":
    cmd[-1] += "1942.zip"
else:
    cmd[-1] += "sf2ce.zip"
print(f"Run {cmd}")
run(cmd)
