import keyboard  # using module keyboard
import time

# sudo apt-get update --allow-releaseinfo-change
# sudo apt install python3-pip

while True:  # making a loop
    if keyboard.is_pressed('q'):
        print('You Pressed Q Key!')
        break  # finishing the loop
    elif keyboard.is_pressed('a'):
        print('You Pressed A Key!')
    time.sleep(1)

