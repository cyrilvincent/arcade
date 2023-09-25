#!/bin/sh
stty -F /dev/ttyUSB0 4800 istrip cs7 parenb -parodd brkint \
ignpar icrnl ixon ixany opost onlcr cread hupcl isig icanon \
echo echoe echok
# Tester l'envoi vers le minitel
echo 'Started' > /dev/ttyUSB0
sudo systemctl start serial-getty@ttyUSB0.service

