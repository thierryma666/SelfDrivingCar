#include <wiringPi.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "PiPS2.h"
#include <pigpio.h>

#define READDELAYMS 50
#define SAFE_DISTANCE 15
#define ENA 13
#define IN1 19
#define IN2 16
#define ENB 20
#define IN3 21
#define IN4 26
#define SERVO 18
#define LED3 25
#define LED2 9
#define LED1 10

#define TRG 14
#define ECHO 15


#define SELECT_BIT 3
#define SELECT 1
#define START_BIT 3
#define START 4

#define LEFT_1_BIT 4
#define LEFT_1 4
#define LEFT_2_BIT 4
#define LEFT_2 2
#define RIGHT_1_BIT 4
#define RIGHT_1 5
#define RIGHT_2_BIT 4
#define RIGHT_2 3

#define BTN_UP_BIT 3
#define BTN_UP1 5
#define BTN_DOWN_BIT 3
#define BTN_DOWN1 7
#define BTN_LEFT_BIT 4
#define BTN_LEFT1 0
#define BTN_RIGHT_BIT 3
#define BTN_RIGHT1 6

#define BTN_TRIANGLE_BIT 4
#define BTN_TRIANGLE1 6
#define BTN_CIRCLE_BIT 4
#define BTN_CIRCLE1 7

#define BUTTON_SELECT 0
#define BUTTON_START 1
#define BUTTON_LEFT_1 2
#define BUTTON_LEFT_2 3
#define BUTTON_RIGHT_1 4
#define BUTTON_RIGHT_2 5
#define BUTTON_UP 6
#define BUTTON_DOWN 7
#define BUTTON_LEFT 8
#define BUTTON_RIGHT 9
#define BUTTON_TRIANGLE 10
#define BUTTON_CIRCLE 11

PIPS2 pips2;

int parse_speed(int speed){
	
	int pwm = 0;
	switch(speed){

		case 0:
			pwm = 90;
			break;
		case 1:
			pwm = 130;
			break;
		case 2:
			pwm = 170;
			break;
		case 3:
			pwm = 210;
			break;
		case 4:
			pwm = 255;
			break;
		default:
			pwm = 255;
	}

	return pwm;
}

void init_fullspeed(){

	pinMode(ENA, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(ENB, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);

}



void forward_fullspeed(){

	digitalWrite(ENA,1);
	digitalWrite(IN1,0);
	digitalWrite(IN2,1);
	digitalWrite(ENB,1);
	digitalWrite(IN3,1);
	digitalWrite(IN4,0);
}

void backward_fullspeed(){
	
	digitalWrite(ENA,1);
	digitalWrite(IN1,1);
	digitalWrite(IN2,0);
	digitalWrite(ENB,1);
	digitalWrite(IN3,0);
	digitalWrite(IN4,1);
}

void turn_left_fullspeed(){

	digitalWrite(ENA,0);
	digitalWrite(ENB,1);
	digitalWrite(IN3,1);
	digitalWrite(IN4,0);
}

void turn_right_fullspeed(){

	digitalWrite(ENA,1);
	digitalWrite(IN1,0);
	digitalWrite(IN2,1);
	digitalWrite(ENB,0);
}

void init(){
	
	gpioSetMode(ENA, PI_OUTPUT);
	gpioSetMode(IN1, PI_OUTPUT);
	gpioSetMode(IN2, PI_OUTPUT);
	gpioSetMode(ENB, PI_OUTPUT);
	gpioSetMode(IN3, PI_OUTPUT);
	gpioSetMode(IN4, PI_OUTPUT);
	gpioSetMode(SERVO, PI_OUTPUT);
	gpioSetMode(LED3, PI_OUTPUT);
	gpioSetMode(LED2, PI_OUTPUT);
	gpioSetMode(LED1, PI_OUTPUT);
	gpioSetMode(TRG, PI_OUTPUT);
	gpioSetMode(ECHO, PI_INPUT);
}

void forward(int speed){

	gpioWrite(ENA,1);
	gpioWrite(IN1, 0);
	gpioPWM(IN2, parse_speed(speed));
	
	gpioWrite(ENB,1);
	gpioPWM(IN3,parse_speed(speed));
	gpioWrite(IN4,0);
}

void backward(int speed){
	
	gpioWrite(ENA,1);
	gpioPWM(IN1, parse_speed(speed));
	gpioWrite(IN2, 0);
	
	gpioWrite(ENB,1);
	gpioWrite(IN3,0);
	gpioPWM(IN4,parse_speed(speed));
}

void turn_left(int speed){

	gpioWrite(ENA,1);
	gpioWrite(IN1, 0);
	gpioPWM(IN2, parse_speed(speed)/3);
	
	gpioWrite(ENB,1);
	gpioPWM(IN3,parse_speed(speed));
	gpioWrite(IN4,0);
}

void turn_right(int speed){
	
	gpioWrite(ENA,1);
	gpioWrite(IN1, 0);
	gpioPWM(IN2, parse_speed(speed));
	
	gpioWrite(ENB,1);
	gpioPWM(IN3,parse_speed(speed)/3);
	gpioWrite(IN4,0);
}

void back_left(int speed){
	
	gpioWrite(ENA,1);
	gpioPWM(IN1, parse_speed(speed)/3);
	gpioWrite(IN2, 0);
	
	gpioWrite(ENB,1);
	gpioWrite(IN3,0);
	gpioPWM(IN4,parse_speed(speed));
}

void back_right(int speed){
	
	gpioWrite(ENA,1);
	gpioPWM(IN1, parse_speed(speed));
	gpioWrite(IN2, 0);
	
	gpioWrite(ENB,1);
	gpioWrite(IN3,0);
	gpioPWM(IN4,parse_speed(speed)/3);
}

void turn_left_static(int speed){
	
	gpioWrite(ENA,0);
	gpioWrite(ENB,1);
	gpioPWM(IN3,parse_speed(speed));
	gpioWrite(IN4,0);
}

void turn_right_static(int speed){
	
	gpioWrite(ENA,1);
	gpioWrite(ENB,0);
	gpioWrite(IN1,0);
	gpioPWM(IN2,parse_speed(speed));
}


void stop(){

	gpioWrite(ENA,0);
	gpioWrite(ENB,0);
}

void speed_status(int speed){

	switch(speed){
		
		case 0:
			gpioPWM(LED1,250);
			gpioWrite(LED2,1);
			gpioWrite(LED3,1);
			break;
		case 1:
			gpioWrite(LED1,0);
			gpioWrite(LED2,1);
			gpioWrite(LED3,1);
			break;
		case 2:
			gpioWrite(LED1,0);
			gpioPWM(LED2,250);
			gpioWrite(LED3,1);
			break;
		case 3:
			gpioWrite(LED1,0);
			gpioWrite(LED2,0);
			gpioWrite(LED3,1);
			break;
		case 4:
			gpioWrite(LED1,0);
			gpioWrite(LED2,0);
			gpioWrite(LED3,0);
			break;
		default:
			gpioWrite(LED1,0);
			gpioWrite(LED2,0);
			gpioWrite(LED3,0);
	}
}


bool check_press_button(int button){

	bool pressed = false;
	switch(button){

		case BUTTON_SELECT:
			pressed = !CHK(pips2.PS2data[SELECT_BIT], SELECT);
			break;
		case BUTTON_START:
			pressed = !CHK(pips2.PS2data[START_BIT], START);
			break;
		case BUTTON_LEFT_1:
			pressed = !CHK(pips2.PS2data[LEFT_1_BIT], LEFT_1);
			break;
		case BUTTON_LEFT_2:
			pressed = !CHK(pips2.PS2data[LEFT_2_BIT], LEFT_2);
			break;
		case BUTTON_RIGHT_1:
			pressed = !CHK(pips2.PS2data[RIGHT_1_BIT], RIGHT_1);
			break;
		case BUTTON_RIGHT_2:
			pressed = !CHK(pips2.PS2data[RIGHT_2_BIT], RIGHT_2);
			break;
		case BUTTON_LEFT:
			pressed = !CHK(pips2.PS2data[BTN_LEFT_BIT], BTN_LEFT1);
			break;
		case BUTTON_RIGHT:
			pressed = !CHK(pips2.PS2data[BTN_RIGHT_BIT], BTN_RIGHT1);
			break;
		case BUTTON_UP:
			pressed = !CHK(pips2.PS2data[BTN_UP_BIT], BTN_UP1);
			break;
		case BUTTON_DOWN:
			pressed = !CHK(pips2.PS2data[BTN_DOWN_BIT], BTN_DOWN1);
			break;
		case BUTTON_CIRCLE:
			pressed = !CHK(pips2.PS2data[BTN_CIRCLE_BIT], BTN_CIRCLE1);
			break;
		case BUTTON_TRIANGLE:
			pressed = !CHK(pips2.PS2data[BTN_TRIANGLE_BIT], BTN_TRIANGLE1);
			break;
	}
	return pressed;
}

void look_around(){

	gpioServo(SERVO,1500);
    gpioDelay(100000);

    gpioServo(SERVO,800);
    
    gpioDelay(300000);
    gpioServo(SERVO,2500);
    gpioDelay(500000);
    gpioServo(SERVO,1500);
    gpioDelay(100000);
}

double measure_distance(){

	gpioWrite(TRG,0);
    gpioDelay(1000);
    gpioWrite(TRG,1);
    gpioDelay(10);
    gpioWrite(TRG,0);
    while(gpioRead(ECHO)==0);
    double start = time_time();
    while(gpioRead(ECHO)==1);
    double end = time_time();

	double distance = (end-start) * 17150;
	return distance;
}

int main(int argc, char **argv) 
{
	char *progname = *argv++; argc--;


	if (wiringPiSetupGpio() == -1)
	{
		return 1 ;
	}
	
	int nextRead = READDELAYMS;
	if (gpioInitialise() < 0)
	{
	   return 1;
	}

	while(1){

		if (!pips2.initializeController(8, 11,5, 7))
		{
			delay(200);
			continue;
		}
		int returnVal = pips2.reInitializeController(ALLPRESSUREMODE);
		if (returnVal == -1)
		{
			delay(200);
			continue;
		} else if (returnVal == -2)
		{
		}

		break;
	}
	
	delay(50);
	
	init();
	stop();

	int speed = 2;
	speed_status(speed);
	bool left1_pressed = false;
	bool left2_pressed = false;
	bool circle_pressed = false;
	bool start_pressed = false;
	while (1)
	{
		if (millis() > nextRead)
		{
			nextRead = millis() + READDELAYMS;
			
			pips2.readPS2();		
			char changedStates[2]; // Create the vector to hold changed states.
			pips2.getChangedStates(changedStates); // Populate the vector
			char btnDowns[2]; // Create the vector of buttons that have been pushed since last read.
			char btnUps[2]; 	// Create the vector of buttons that have been pushed since last read.
			// Buttons that have been pushed down are buttons that are currently down and have changed.
			btnDowns[0] = ~pips2.PS2data[3] & changedStates[0];
			// Buttons that have been released are buttons that are currently up and have changed.
			btnUps[0] = pips2.PS2data[3] & changedStates[0];
			
			if (check_press_button(BUTTON_LEFT_1)){

				if(!left1_pressed){

					speed += 1;
					
					left1_pressed = true;
					if(speed > 4){
						speed = 4;
					}

					speed_status(speed);
				}
			}else{

				left1_pressed = false;
			}

			if (check_press_button(BUTTON_LEFT_2)){

				if(!left2_pressed){

					speed -= 1;
					
					left2_pressed = true;
					if(speed < 0){
						speed = 0;
					}

					speed_status(speed);
				}
			}else{

				left2_pressed = false;
			}

			if (check_press_button(BUTTON_RIGHT_2)){

				if(check_press_button(BUTTON_UP)){

					if(check_press_button(BUTTON_LEFT)){

						turn_left(speed);

					}else if(check_press_button(BUTTON_RIGHT)){

						turn_right(speed);

					}else{

						forward(speed);

					}

				}else if(check_press_button(BUTTON_DOWN)){

					if(check_press_button(BUTTON_LEFT)){
						
						back_left(speed);

					}else if(check_press_button(BUTTON_RIGHT)){

						back_right(speed);

					}else{

						backward(speed);

					}

				}else if(check_press_button(BUTTON_LEFT)){

					turn_left_static(speed);

				}else if(check_press_button(BUTTON_RIGHT)){

					turn_right_static(speed);

				}else{

					stop();
				}
				
			}else if (check_press_button(BUTTON_RIGHT_1)){

				if(measure_distance()<SAFE_DISTANCE){

					backward(speed);
					for(int i=0;i<12;i++){

						delay(READDELAYMS);
						pips2.readPS2();
					}
					int random = (int)time_time();
					random = random % 3;
					switch(random){

						case 0:
							turn_left(speed);
							break;
						case 1:
							turn_right(speed);
							break;
						case 2:
							turn_left_static(speed);
							break;
						case 3:
							turn_right_static(speed);
						default:
							turn_left_static(speed);
					}
					for(int i=0;i<20;i++){

						delay(READDELAYMS);
						pips2.readPS2();
					}
				}else{

					forward(speed);
				}
			}
			else{
				stop();
			}

			if(check_press_button(BUTTON_CIRCLE)){

				if(!circle_pressed){

					circle_pressed = true;
					look_around();
				}
			}else{
				
				circle_pressed = false;
			}

			if(check_press_button(BUTTON_START)){

				if(!start_pressed){

					start_pressed = true;
					
					if (!pips2.initializeController(8, 11,5, 7))
					{
						
					}
					int returnVal = pips2.reInitializeController(ALLPRESSUREMODE);
					if (returnVal == -1)
					{
						
					} else if (returnVal == -2)
					{
						
					}
			
				}
			}else{
				
				start_pressed = false;
			}
		}
	}
	
	return 0;
}
