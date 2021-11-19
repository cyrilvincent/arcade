import keyboard  # using module keyboard
import time

# sudo apt-get update --allow-releaseinfo-change
# sudo apt install python3-pip
# sudo pip3 install keyboard

print("15")
time.sleep(15)
print("F4")
# keyboard.press_and_release("ENTER + 1")
keyboard.press_and_release("ALTGR")
keyboard.press_and_release("F4")
print("STOP")
quit(0)