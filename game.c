
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

char map_start[4][18] = { {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ',' ',' ',' ','@',' ','t'}
						, {' ',' ',' ',' ',' ','@',' ',' ',' ',' ','@',' ',' ',' ',' ','@',' ','t'}
						, {' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ',' ',' ','@',' ','t'}
						, {' ',' ',' ',' ',' ','@',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','t'}};//the map at start
																									 //of the game
char map[4][18]; //the map


char lost[4][16] = 		{ {' ',' ',' ','Y','O','U',' ','L','O','S','T','!',' ',' ',' ',' ',' ','t'}
						, {' ',' ',' ','Y','O','U',' ','L','O','S','T','!',' ',' ',' ',' ',' ','t'}
						, {' ',' ',' ','Y','O','U',' ','L','O','S','T','!',' ',' ',' ',' ',' ','t'}
						, {' ',' ',' ','Y','O','U',' ','L','O','S','T','!',' ',' ',' ',' ',' ','t'}};//you lost screen



int alive = 1;//gamestate counter

int timeoutcount = 0;//global variable to handle timer2
int timeoutcount2 = 0;//global variable to handle timer3


void user_isr( void ) {//this method is the taken from lab 3

	int k;						//int used in for loop
	int l;						//int used in for loop

	for(k = 0; k<17; k++){				//prints the start map onto
		for(l = 0; l<4; l++){			//the map that will be modified
			map[l][k] = map_start[l][k];//during the game
		}
	}

	int button = getbtns();
	char structure = '@';

	int i;						//int used in for loop
	int j;						//int used in for loop

	int player_location = 1;//current location of the player


/*													BELOW IS DEAD LOGIC															*/


if(IFS(0) & 0x1000){//increments timeoutcount2 by 1 every interupt in timer3
			IFS(0) = 0;
			timeoutcount2++;
		}

if (timeoutcount2 == 10 ){
		while(alive == 0 && button == 1){
			for(k = 0; k<17; k++){			//these 2 for loops resets the map
				for(l = 0; l<4; l++){		//to the starting map
					map[l][k] = map_start[l][k];
				}
			}
			
			PORTE = 0;						//reset the score


			IFS(0) = 0;						//resets interrupt flag
			timeoutcount2 = 0;				//resets timeoutcount2
			alive = 1;						//turns the game on by reviving player

			map[player_location][1] = 'x';//prints the player onto the screen

			display_string(0, map[0]);//displays the first row of the map onto the first row from the display_string function
			display_string(1, map[1]);//displays the second row of the map onto the second row from the display_string function
			display_string(2, map[2]);//displays the third row of the map onto the third row from the display_string function
			display_string(3, map[3]);//displays the fourth row of the map onto the fourth row from the display_string function
			display_update();//update the display
	}
}
else if(timeoutcount2 > 10){
	timeoutcount2 = 0;//if one second has passed and the reset button
}					  //has not been pressed reset timeoutcount2
else{
	IFS(0) = 0;//resets interrupt flag
}


/*														DEAD LOGIC END															*/

/*												BELOW IS PLAYER ALIVE LOGIC														*/


	while (alive == 1){//checks if the the game is active
		if(IFS(0) & 0x100){//increments timeoutcount by 1 every interupt in timer2
			IFS(0) = 0;
			timeoutcount++;
		}

		if(timeoutcount == 10){//timer for how fast the map moves, same solutions as in lab3
			int btns = getbtns();

			for(i = 0; i < 17; i++){//scrolls through columns 0-17

				if(i == 0){
					map[0][17] = map[0][0];//copies the char in the first place in row 1 to the last place
					map[1][17] = map[1][0];//copies the char in the first place in row 2 to the last place
					map[2][17] = map[2][0];//copies the char in the first place in row 3 to the last place
					map[3][17] = map[3][0];//copies the char in the first place in row 4 to the last place
				}

				for(j = 0; j < 4; j++){
					if(!(j == player_location && i == 0)){
						map[j][i] = map[j][i+1];				//moves the map one step to the left
					}											//except for the char behind the player									
					else if(j == player_location && i == 0){
						map[j][17] = map[j][i];					//if we're on the char behind the player
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
			

			alive = 0;
			}

			map[player_location][1] = 'x';//prints the player onto the screen


			display_update();//update the display
			display_string(0, map[0]);//displays the first row of the map onto the first row from the display_string function
			display_string(1, map[1]);//displays the second row of the map onto the second row from the display_string function
			display_string(2, map[2]);//displays the third row of the map onto the third row from the display_string function
			display_string(3, map[3]);//displays the fourth row of the map onto the fourth row from the display_string function
									  // both display_string and display_update is used from the labs

			PORTE++;//increments the score
			IFS(0) = 0;//resets flag counter in timer
			timeoutcount = 0;//resets timeoutcount
		}
	}
}


/*												PLAYER ALIVE LOGIC END															*/


void labinit (void){//labinit is from lab3; intialisations for buttons, timers and LEDS 
	volatile int* trise = 0xbf886100;	//initializes the leds vår eller laben??
  	volatile int* porte = 0xbf886110;	//initializes the leds ------- 
  	(*trise) = 0XFF00;					//initializes the leds -------
  	TRISD = 0xFFE0;						//initializes the buttons??? -------

	
	//everything below is our solution to lab3 except enable_interrupt() which is taken from the instruction in the same lab
	T2CON = 0x0;			//zeroes timer2 control
	T2CONSET = 0x70;		//initialize timer2 256 scaling
	TMR2 = 0;				//16bit counter
	PR2 = (80000000/10)/256;//period register
	T2CONSET = 0x8000;		//turn on timer2
	//end setup for timer2

	//setup for timer3
	T3CON = 0x0;			//zeroes timer3 control
	T3CONSET = 0x70;		//initialize timer3 256 scaling
	TMR3 = 0;				//16bit counter
	PR3 = (80000000/10)/256;//period register
	T3CONSET = 0x8000;		//turn on timer3
	//end setup for timer3


	IEC(0) |= 0x100;		//enables interrupts for the timer?
  	IPC(2) |= 0x1D;			//sets priority for the timer

	IEC(0) |= 0x1000;
	IPC(3) |= 0x1C;
	enable_interrupt();		//enable interrupts globally

	return;
}
void labwork (void){//taken from the labs -- allows the game to run continously

}

