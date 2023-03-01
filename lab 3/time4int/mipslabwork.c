/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

int timeoutcount = 0;

/* Interrupt Service Routine */
void user_isr( void ) {

  int sw = getsw();

  if(IFS(0) & 0x100){
    timeoutcount++;
    IFS(0) = 0;
  }

  if(timeoutcount == 10){
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    IFS(0) = 0;
    timeoutcount = 0;
  }
  if(IFS(0) & 0x80000){
    (PORTE++);
    IFS(0) &= ~0X80000;
  }
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  volatile int* trise = 0xbf886100;
  volatile int* porte = 0xbf886110;
  (*trise) = 0XFF00;
  TRISD = 0xFFE0;

  //clock

  T2CON = 0x0; //empties timer control unit
  T2CONSET = 0x70; //set prescale to 1:256
  TMR2 = 0; //resets timer
  PR2 = (80000000/10)/256; //period; set to 80Mhz/prescale and /10 to get timeouts every 1/10th second
  T2CONSET = 0X8000; //turns on the timer

  //enable interrupts
  

  IEC(0) |= 0x100;
  IPC(2) |= 0x1C;

  IEC(4) |= 0x80000;
  IPC(4) |= 0x1F000000;

  enable_interrupt();

  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
prime = nextprime( prime );
display_string( 0, itoaconv( prime ) );
display_update();
}