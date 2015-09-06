lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o PingPongDiplomacy.o PingPongDiplomacy.c
lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -Wl-yt1 -Wl-yo4 -Wl-ya0 -o PingPongDiplomacy-rom.gb PingPongDiplomacy.o

del *.o *.lst *.map *.sym



pause


