
      Great Giana Sisters   for Atari STE
     With audio track playback from mass storage

Currently only basic ACSI and IDE storage adapters
supported - so in case of ACSI  max 1GB , 
or need to place on first or second partititon
on your SD card.

This is based on Zamuel_a STE enhanced
version of Giana Sisters - with scroll and
DMA sound effects.

Min RAM for this is 1MB, but if your hard disk
driver SW uses lot of RAM 2MB may be needed.

Recommended is usage with UltraSatan,
or Compact Flash cards.
But should work with classic SCSI hard
disks too, if they are not very old and
slow. 


Most interesting feature is optional
usage of user's audio tracks.

You need to replace file GS.RAW
with your custom audio file.

Format must be:  Mono, 25033 Hz sample
rate, 8-bit unsigned, RAW (no header).
It's very easy to convert in such format
with freeware Audacity. Length of
files may be between 100KB and
510 MB (max partititon size in TOS).
1 minute music with this format
takes about 1.5 MB, so
can play even very long files - over 
2 hours.
But it needs some postprocessing too,
and special converting. I will add instructions
and SW soon.


Important:  audio files must be
defragmented, otherwise will hear
some nasty noise instead music
for more-less time during play.
If you copy this to partition where did
not delete files, it will be defragmented.

Hard disk drivers:  should work with any 
decent Atari ST hard disk driver, which 
supports PUN info. 

Unlimited lives opt. Highscore save
works not - it will work with 
Haga version.

This is mostly test version - first
audio track play during game
with only STE audio DMA used.
Mixing music and game sound
effects is done in SW.

Falcon: will work well only
at 50 Hz refresh rate - so
PAL on (RGB) monitor, or TV.


  PP, Febr. 2015
