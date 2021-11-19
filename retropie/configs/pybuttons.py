import pygame
import time

pygame.init()
nbj = pygame.joystick.get_count()
if nbj == 0:
    print("No joystick, no buttons")
    quit(1)
pygame.joystick.init()
nbb = pygame.joystick.get_numbuttons()
print(f"Found {nbj} joysticks with {nbb} buttons")
joystick = pygame.joystick.Joystick(0)
joystick.init()
nbjb = joystick.get_numbuttons()
print(f"Listen to {joystick.get_name()} with {nbjb} buttons")
done = False
while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        if event.type == pygame.JOYBUTTONDOWN:
            print("Joystick button pressed.")
        if event.type == pygame.JOYBUTTONUP:
            print("Joystick button released.")
    joystick.init() # D'après exemple ?? get_init() ?
    for i in range(nbjb):
        button = joystick.get_button(i)
        print(f"Button {i} => {button}")
    time.sleep(1)
pygame.quit()

# TOP 2x6 buttons sur le top ABCDL1L2
# FRONT 1P R1 2P (R1 est le special)
# BOTTOM COIN R2(mappé à rien) INTERRUPTEUR

# Autre méthode mieux : https://opendomotech.com/raspberry-pi-bouton-ventilateur-automatique/
# Simuler la touche F4 : https://artheodoc.wordpress.com/2019/08/01/simulation-du-clavier-avec-python/
# Et eventuellement Entree + 1



