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

poweroff = False


def release():
    print("Reboot")
    if not poweroff:
        check_call(['/sbin/reboot'])


def hold():
    held = button.held_time + button.hold_time
    if held > 2.0:
        print("Power off")
        check_call(['/sbin/poweroff'])
        poweroff = True


button=Button(use_button, hold_time=0.1, hold_repeat=True)
button.when_held = hold
button.when_released = release

pause()