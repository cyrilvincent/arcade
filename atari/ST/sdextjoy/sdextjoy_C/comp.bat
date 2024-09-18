set VBCC=C:\Users\conta\git-CVC\Retro\git-retro\atari\ST\sdextjoy\sdextjoy_C\vbcc_bin_win64
set path=%VBCC%\bin

vc +%VBCC%\config\tos -O2 -nostdlib -o sdextjoy.prg init.s main.c sd.c xbioshook.s spi_extjoy.s

pause

