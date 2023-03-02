Written by Erik Pagès Svärd & Jonathan Nilsson Cullgert
in game.c time4io.c, and labwork.S. We also slightly modified miplabmain.c

The files mipslabmain.c, mibslabfunc.c, vectors.S, stubs.c, labwork.S and mipslab.h 
were written by Axel Isaksson and F. Lundevall

This is a small game designed to be played on the chipKIT Uno32 board and the chipKIT Basic I/O. 

COMPILE AND RUN:
The game needs MCB32 toolchain installed on your computer in order to compile and run. 
When you have the MCB32 terminal window open and ChipKIT connected to your computer, change directory to the folder you saved the game in.
Type "make" in order to compile, and then "make install" in order to run the game on the ChipKIT Uno32 board.
In some cases, you have to find out the name of your USB port, then issue the command "make install TTYDEV=(USB port name)"

HOW TO PLAY:
Steer the dolphin by pressing and holding down button 4, (BNT4), in order to make it dive down since it will automaticly float upwards as time goes on.
Avoid obstacles coming towards the dolphin by steering. If you hit an obstacle, you lose.
When you lose press button 2, (BTN2), to restart the game.
The LEDs on the chipKIT basic I/O keeps track of your score.
