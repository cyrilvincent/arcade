SALTO - Xerox Alto I/II Simulator.
Copyright by Juergen Buchmueller <pullmoll@t-online.de>
Partially based on info found in Eric Smith's Alto simulator: Altogether.

1.) Building
=================================

Things you need before you can give it a try.




1.1) Prerequisites
=================================

You need the GNU compiler collection. SALTO was developed and tested with
GCC 3.3.3, while others should work. You also need GNU make.
Both can be found at http://www.fsf.org/

apt-get install build-essential


You also need SDL - Simple Direct Media Layer - installed, and "sdl-config"
in your path. It is used to determine the required compiler switches and
the path to the SDL libraries. SDL can be found at http://libsdl.org/

apt-get install libsdl1.2-dev


Some build tools are required, such as (g)make, ar, ranlib, flex, yacc.
You should have these ready, if you installed the GNU binutils, and if
you installed the flex and yacc lexer and parser generators.

apt-get install flex bison




1.2) Settings
=================================

The only really maintainable switch in tha Makefile is the DEBUG=1 or
DEBUG=0 switch. With DEBUG=1 you can (and should) select the output generated
by running bin/salto. If you just want to execute some code, you should
choose DEBUG=0, which removes all the logprintf calls from the code and
makes it a lot smaller and faster.




2.) Running
=================================

After building a binary by running "make" or "gmake" on the command line,
and assuming all went wll, you can now run

bin/salto disks/games.dsk.Z




2.1) Running the debug build
=================================

There's a whole lot of command line switches to disable and enable
the logging for certain tasks and other sections of the emulation.
The default settings for logging are:

switch name default
-----------------------------------------------------
emu emulator task on
task1 task 1 on
task2 task 2 on
task3 task 3 on
ksec disk sector task on
task5 task 5 on
task6 task 6 on
ether ethernet task on
mrt memory refresh task on
dwt display word task on
curt cursor task on
dht display horizontal task on
dvt display vertical task on
part parity error task on
kwd disk word task on
task17 task 17 on
mem memory functions off
tmr timer functions off
dsp display functions off
dsk disk functions on
drv disk drive emulation on

To turn everything off you use "-all", to turn everything on you use "+all".
To disable a single type "-switch", to enable it "+switch".
Thus if you want to log just the display word task and display functions,
your command line would look like this:

bin/salto -all +dwt +dsp

If you want to supply a software image to load when pressing the "insert" key,
you just specify its name after the switches:

bin/salto -all +dwt +dsp helloworld.bin

To start the emulation in a paused mode and with the debugger window shown
first, you add a switch "-d" to the command line:

bin/salto -all +dwt +dsp -d helloworld.bin

You can toggle between paused mode and running with the "pause" key
on your keyboard, and you can toggle between the debugger window and the
Alto display with the "scroll lock" key.

You can even fine-tune the loglevels with -switch=value or +switch=value.
If you want to see just the most important disk function log output:
bin/salto -all +dsk=1

While the debugger window is visible, you can use the cursor keys to move
the flashing memory cursor:
left previous word
right next word
up previous row (-8 words)
down next row (+8 words)
page up previous page (-256 words)
ctrl + page up 16 pages back
page down next page (+256 words)
ctrl + page dn 16 pages forward
home cursor to top, left in page
end cursor to bottom, right in page
ctrl + home go to page 0
ctrl + end go to last page
space stack address, and follow the address at the cursor
back space return to stacked address

You can also toggle the display base between octal (o), decimal (d),
hexadecimal (h), and ASCII (a) by pressing the corresponding key.

If you don't want to see the log output that's written to the console, too,
you can just redirect it to /dev/null:

bin/salto -all +dwt +dsp -d helloworld.bin >/dev/null

Or if you want to keep it for later, you can of course redirect it to
a file:

bin/salto -all +dwt +dsp -d helloworld.bin >hw.log




2.2) Running the normal build
=================================

The only thing you can specify on the command line is the name of a
disk image file to open up. Dual disks do not (yet) work right, because
there are still bugs to find in the disk drive selection emulation.

You can toggle to the debugger window with "scroll lock", and
you can inspect memory just like described above.





2.3) Included disks
=================================
bcpl.dsk.Z
diag.dsk.Z
gamesb.dsk.Z
games.dsk.Z
nonprog.dsk.Z
st76boot.dsk.Z
tdisk4.dsk.Z
tdisk8.bin