  Wolfenstein 3D for Atari ST(E), Falcon


This game is intended to be played from hard disks. An unofficial and unfisished port for Atari  ST(E), Falcon. What I did is mostly bug fixing and alloving saving of gamestates.
Possible problems with game: works not with Hddriver and other hard disk drivers.   Loosing controls.  Desync on TV/monitor as it sets 60 Hz refresh rate.
If have 2MB RAM may play only without savestates. Then run with
file START2M.TOS .  Game will run with 50 Hz refresh rate - if started on PAL system. Fixed IKBD mode setting code and Timer-C fix .

With 4MB of RAM run with START.TOS .  Then will have option to break/exit game in any moment with key F9, and then possible to permanently save gamestate with GXUT204.PRG . Gamestate files are 2MB long, as game needs 2MB RAM.
Works with ST, STE, Mega ST, Mega STE, Falcon (STE DMA fix added).
Sound is much better with STE, Falcon.

PP, Nov. 2010


More about bugs:
Hard disk problems happen with drivers sensitive on Timer-C
counter. If it runs not, will stuck. Author could solve it by restoring
regular Timer-C counting before every disk access. Here, it is solved by hooking vector $476 (RWABS).

Loosing controls: IKBD chip mode setting code is flawed (wrong status checking). It is replaced with good one when run game
with START.TOS . 
Note: control loss happened mostly at 50Hz refresh rate, but ocassionaly at 60 Hz too.

As in DOCS stays, some levels work not.

PP
