ep32 1.20 - enteprise computer emulation

"ep32" is a heavily modified version of kevin thacker's (amstrad@aiind.upv.es) 
"enter" emulator  by vincze béla györgy, aka egzo (ex-exosworm - egzo@freemail.hu)

"enter" is released with full source under the gnu public license. see the
original "doc.txt" for more details.

what's new in version 1.20:

- now segment number can be also specified for breakpoints
- small fix in nick emulation to get VENUS working
- compiled with vs2005

what's new in version 1.19:

- nick port reading fixed to get renegade working

what's new in version 1.18:

- hopefully sound problems are gone...

what's new in version 1.17:

- Varró György's configurator in the hardware menu
- handling of winimage files (contribution of Varró György)
- logo displays well in windows xp
- some small fixes

what's new in version 1.16:

- small fixes in sound handler
- hungarian faq added
- modifications in help

what's new in version 1.15:

- gui fixes (improved fullscreen/windowed mode switching)
- some speedups
- better timing for nasa guy demos (they use the 'wait on all memory access' flag)
- shell integration (snapshot files are associated with ep32)
- updated icons
- changed ep32 URL (http://web.axelero.hu/egzo/ep)

what's new in version 1.14:

- some speedups
- no more hangs when you try to save a screenshot in fullscreen
- waveout interface (now this is the default) for better sound compatibility
- direct-x 8 no more required. direct-x 7 should be enough.

what's new in version 1.13:

- modifications in screen update and timing routines to get some special
  programs working (e.g. joe's rockmonitor)
- modifictation in sound routines to make sound of magnetron audible

what's new in version 1.12:

- even better video ram timing
- faster tape load
- upper 8 colors are correctly updated after screen mode changing
- lpt animations work correctly (e.g. in scroll demo, antiriad or tilitoli)
- adjustable timing accuracy (it speeds up the emulation)

what's new in version 1.11:

- dave clock divider now works
- restoring dave's state on snapshot load fixed 
- better video memory read/write timing

what's new in version 1.1:

- 4,5 and 7 bit polynomial counter distortion on tone channels (now sound effects
  in "nodes of yesod" are fine)
- correct handling of very high tone generator frequencies (for games with 
  48k zx spectrum sounds)
- bias setting on snapshot load fixed
- fixes in soundsystem (buffer size can be smaller than 100 ms)
- programmable external joystick emulation
- new z80 timing with wait states on M1 and video memory access (this slows
  down the emulation a bit)
- fixes in z80 emulation. garbaged screen in chase h.q. and wec le mans gone.

what's new in version 1.0:

- new, optimized nick routines. for now on, ep32 runs only in 16 and 32 bit display
  modes. rendering became WAY (2x-5x) faster.
- ALTIND0 and ALTIND1 in character modes fixed (scrolls in cauldron display correctly)
- user interface fixes
- win98 support improved 

what's new in version 1.0beta:

- snapshot saving/loading (with zip support)
- directinput changes for better compatibility
- entirely rewritten keyboard handler
- keyboard setup
- non-documented nick ports are emulated (all nick registers can be reached at 84-8f
  ports !!!) this way "nautilus" runs.
- external joystick emulation removed (caused many strange problems :)
  
what's new in version 1.0alpha rc5:

- config file loader
- reorganized menus
- tape patch filename problems fixed
- invalid reqistry values are checked
- other small fixes

what's new in version 1.0alpha rc4:

- screenshot saving
- tape patch is back...
- when no filename given for tape loading (e.g. with 'load "tape:"' command in basic),
  the emulator will display a dialog to select a file to load
- ep32 now remembers some settings (using the registry)
- fixes in interrupt system (now 1Hz interrupt works)
- cmos clock emulation (works with zozotools)

what's new in version 1.0alpha rc3:

- right DAC output fixed
- color bias fixed (still needs some tuning)
- exos nn mnemonic in deubugger
- lots of fixes in debugger and user interface
- step over for call, djnz, exos, ldir/lddr, etc. in debugger
- port i/o
- ring modulator and low pass filter on noise channel
- missing key "^" fixed
- started to work on help file
- brand new interrupt system emulation better, video interrupts, etc. now pddemo works :)
- "run to address" is back
- vertical retrace timing fixed

what's new in version 1.0alpha rc2:

- disk interface now works under win9x/me
- lockup when no disk in drive under 2k/xp fixed
- floppy disk write support
- screen size changed
- pause in main menu fixed
- volume slider positon fixed
- buggy sound capture fixed
- invalid margins now display correctly

what's new in version 1.0alpha rc1:

- terrible slowdonws under win9x fixed (i'm working under xp :)
- new disk interface. now floppy drives on the emulated enteprise are mapped to their respective drive 
  in your pc. so you can use your original enterprise disks on the emulator :) 
  (on nt-like operating systems (nt/2k/xp) you will need administrator privileges to use this feature)
  to use hd disks (with 1.2,1.44 or bigger capacity) you must use turbo-exdos 1.3 !
- some debugger fixes 
- sound under pause fixed

major modifications to kevin's emulator (2001.aug.26) in version:

- keyboard scan rate increased (this way is much easier to type...)
- keyboard handler fixed (no more keyboard lockups when REM1 or REM2 is set) 
- F6 fixed (it's on keypad 6)
- programmable frequency timer interrupts fixed (now the frequency is correct)
- entirely rewritten directsound handler and dave sound emulation
- entirely rewritten directdraw interface (now windowed/full screen works)
- better colors (with adjustable brightness)
- debugger changed
- sound output saving to .wav file
- new timing routines for more accuracy and less processor load

requirements:

pentium-2 300 MHz
agp video card
windows 9x/me/2k/xp whatever
direct-x 7 installed
sound card

nick graphics chip emulation:

- all documented video modes
- video interrupts
- some interlace modes
- vres operation in pixel and lpixel

dave sound emulation:

- 3 tone generators + noise generator using 7,9,11,15 or 17 bit polynomial counters
- 4,5 or 7 bit polynomial counter distortion on tone channels
- ring modulation
- low pass filter on noise channel
- programmable noise frequency
- direct output to DAC (for digitalized sound)

still missing:

- high pass filters, clocked by tone generators (no information at all)

planned new features:

- serial interface (for mouse)

if you have information on missing features, now-working programs or whatever, e-mail me:

egzo@freemail.hu 

the latest version can be downloaded from

http://web.axelero.hu/egzo site's "enterprise" part
(http://web.axelero.hu/egzo/ep)

Thanks to Miklán Attila (The Art of Code) and Pertik László (Garfield) who have
helped in developing the emulator.

