REM ECHO="Y" to echo all screen output to stdout
REM 8K="Y" to use the 8K ROM with BASIC, Assembler and Monitor,
REM otherwise just the monitor will be in ROM

java -DECHO="N" -D65C02="Y" -DROMFILE="65C02.rom.bin" -cp Pom1.jar pom1.Exec
