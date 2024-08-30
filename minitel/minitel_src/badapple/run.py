import sys
import time
import os

if __name__ == '__main__':
	f = open('play.txt', 'r')
	frame_raw = f.read()
	frame_raw = frame_raw.replace('.', ' ')
	f.close()
	frames = frame_raw.split('SPLIT')
	for frame in frames:
		if sys.platform.startswith('win'):
			os.system('cls')
		else:
			os.system('clear')
		print(frame)
		if sys.platform.startswith('win'):
			time.sleep(0.1)



