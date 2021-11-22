#!/usr/bin/python3

# sudo apt install python3-gpiozero
# chmod +x shutdown_button.py
# sudo cp shutdown_button.py /usr/local/bin
# sudo cp shutdown_button.service /etc/systemd/system
# sudo systemctl enable shutdown_button.service
# sudo systemctl start shutdown_button.service

use_button=21
print("Start Shutdown button on port "+str(use_button))

from gpiozero import Button
from signal import pause
from subprocess import check_call


class ShutDownButton:

    def __init__(self):
        self.reboot = True
        self.button = Button(use_button, hold_time=0.1, hold_repeat=True)
        self.button.when_held = self.hold
        self.button.when_released = self.release

    def release(self):
        print("Reboot")
        if self.reboot:
            check_call(['/sbin/reboot'])

    def hold(self):
        held = self.button.held_time + self.button.hold_time
        if held > 2.0:
            self.reboot = False
            print("Power off")
            check_call(['/sbin/poweroff'])


if __name__ == '__main__':
    ShutDownButton()
    pause()