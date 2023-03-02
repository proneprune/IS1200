
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

const char map_start[4][25] = {   {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','@','t'}
                                , {' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','@','t'}
                                , {' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ','t'}    	//written by Erik
                                , {' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@','t'}};	//the map at start	
																																			//of the game
char map[4][25]; //the map


char lost[4][16] = 		{ {' ',' ',' ','Y','O','U',' ','L','O','S','T','!',' ',' ',' ',' '}
						, {' ',' ',' ','Y','O','U',' ','L','O','S','T','!',' ',' ',' ',' '}
						, {' ',' ',' ','Y','O','U',' ','L','O','S','T','!',' ',' ',' ',' '}	//written by Jonathan
						, {' ',' ',' ','Y','O','U',' ','L','O','S','T','!',' ',' ',' ',' '}};//you lost screen



int alive = 1;//gamestate counter

int timeoutcount = 0;//global variable to handle timer2


void user_isr( void ) {//this method is the taken from lab 3

	int k;						//int used in for loop
	int l;						//int used in for loop

	for(k = 0; k<24; k++){				//prints the start map onto 
		for(l = 0; l<4; l++){			//the map that will be modified		written by Erik
			map[l][k] = map_start[l][k];//during the game
		}
	}

	int button = getbtns();
	char structure = '@';

	int i;						//int used in for loop
	int j;						//int used in for loop

	int player_location = 1;//current location of the player written by Erik


/*											BELOW IS DEAD LOGIC	WRITTEN BY ERIK												*/


if(IFS(0) & 0x100){//increments timeoutcount by 1 every interupt in timer
			IFS(0) = 0;
			timeoutcount++;
		}

if (timeoutcount == 1 ){
		while(alive == 0 && button == 1){
			for(k = 0; k<24; k++){			//these 2 for loops resets the map
				for(l = 0; l<4; l++){		//to the starting map
					map[l][k] = map_start[l][k];
				}
			}
			
			PORTE = 0;						//reset the score


			IFS(0) = 0;						//resets interrupt flag
			timeoutcount = 0;				//resets timeoutcount
			alive = 1;						//turns the game on by reviving player

			map[player_location][1] = 'x';//prints the player onto the screen

			display_string(0, map[0]);//displays the first row of the map onto the first row from the display_string function
			display_string(1, map[1]);//displays the second row of the map onto the second row from the display_string function
			display_string(2, map[2]);//displays the third row of the map onto the third row from the display_string function
			display_string(3, map[3]);//displays the fourth row of the map onto the fourth row from the display_string function
			display_update();//update the display
	}
}
else if(timeoutcount > 1){
	timeoutcount = 0;//if one second has passed and the reset button
	IFS(0) = 0;		//has not been pressed reset timeoutcount
}					
else{
	IFS(0) = 0;//resets interrupt flag
}


/*														DEAD LOGIC END															*/

/*										BELOW IS PLAYER ALIVE LOGIC	WRITTEN BY JONATHAN											*/


	while (alive == 1){//checks if the the game is active
		if(IFS(0) & 0x100){//increments timeoutcount by 1 every interupt in timer
			IFS(0) = 0;
			timeoutcount++;
		}

		if(timeoutcount == 5){//timer for how fast the map moves, same solutions as in lab3
			int btns = getbtns();

			for(i = 0; i < 24; i++){//scrolls through columns 0-17

				if(i == 0){
					map[0][24] = map[0][0];//copies the char in the first place in row 1 to the last place
					map[1][24] = map[1][0];//copies the char in the first place in row 2 to the last place
					map[2][24] = map[2][0];//copies the char in the first place in row 3 to the last place
					map[3][24] = map[3][0];//copies the char in the first place in row 4 to the last place
				}

				for(j = 0; j < 4; j++){
					if(!(j == player_location && i == 0)){
						map[j][i] = map[j][i+1];				//moves the map one step to the left
					}											//except for the char behind the player									
					else if(j == player_location && i == 0){
						map[j][24] = map[j][i];					//if we're on the char behind the player
						map[j][i] = ' ';						//store its char in the last place on its row
					}											//and set it to ' '
				}												
			}

			
			if(btns == 4 && player_location < 3){//checks if btn 4 is pressed in that case character goes down one row
				player_location = player_location + 1;
			}
			else if(player_location > 0 && btns != 4){//if player is not at the top of the screen
				player_location = player_location - 1;//they are moved up one row
			}

			

			if(map[player_location][1] == structure){//checks if the player will be on a structure
													 //if so the game is killed
			display_update();
			display_string(0, lost[0]);				//displays the lose screen
			display_string(1, lost[1]);
			display_string(2, lost[2]);
			display_string(3, lost[3]);
			display_update();
			
			
		
			alive = 0;
			timeoutcount = 0;
			}
			else{
			map[player_location][1] = 'x';//prints the player onto the screen

		 	 //update the display
			display_string(0, map[0]);//displays the first row of the map onto the first row from the display_string function
			display_string(1, map[1]);//displays the second row of the map onto the second row from the display_string function
			display_string(2, map[2]);//displays the third row of the map onto the third row from the display_string function
			display_string(3, map[3]);//displays the fourth row of the map onto the fourth row from the display_string function
			display_update();		  // both display_string and display_update is used from the labs
			}

			PORTE++;//increments the score
			IFS(0) = 0;//resets flag counter in timer
			timeoutcount = 0;//resets timeoutcount
		}
	}
}


/*												PLAYER ALIVE LOGIC END															*/


void labinit (void){//labinit is from lab3; intialisations for buttons, timers and LEDS 
	volatile int* trise = 0xbf886100;	//initializes the leds our solution from lab3
  	volatile int* porte = 0xbf886110;	//initializes the leds our solution from lab3
  	(*trise) = 0XFF00;					//initializes the leds our solution from lab3
  	TRISD = 0xFFE0;						//initializes the buttons

	
	//everything below is our solution to lab3 except enable_interrupt() which is taken from the instruction in the same lab
	T2CON = 0x0;			//zeroes timer2 control
	T2CONSET = 0x70;		//initialize timer2 256 scaling
	TMR2 = 0;				//16bit counter
	PR2 = (80000000/10)/256;//period register
	T2CONSET = 0x8000;		//turn on timer2
	//end setup for timer


	IEC(0) |= 0x100;		//enables interrupts for the timer
  	IPC(2) |= 0x1D;			//sets priority for the timer

	enable_interrupt();		//enable interrupts globally

	return;
}
void labwork (void){//taken from the labs -- allows the game to run continously

}