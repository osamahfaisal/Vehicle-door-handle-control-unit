#include "RCC.h"
#include "GPIO.h"
#include "stm32f401xe.h"
#include "Gpt.h"




// Constants for GPIO pin mappings

#define HANDLE_BUTTON_PIN   1  // handle button  pin
#define DOOR_BUTTON_PIN     2  // door  button pin 

#define VEHICLE_LOCK_LED    3  // vehicle lock led pin
#define HAZARD_LED          4  // hazer led pin
#define AMBIENT_LED         5 //   ambient led pin  

char flag  =0 ;
char doorCLose=1; 
//// Global variables
volatile uint8 doorUnlocked = 0;
volatile uint8 doorOpen = 0;
volatile uint8 antiTheftLock = 0;


void DefaultState(void);
void DoorUnlockState(void);
void DoorOpenState(void) ;
void AntiTheftLockState(void) ;

void ClosingDoorState(void);
void LockingDoorState(void);

int main(){


	Rcc_Init();
	GPT_Init();
	Rcc_Enable(RCC_GPIOA);


	Gpio_ConfigPin(GPIO_A , HANDLE_BUTTON_PIN , GPIO_INPUT , GPIO_PULL_UP );  // door handler
	Gpio_ConfigPin(GPIO_A , DOOR_BUTTON_PIN , GPIO_INPUT , GPIO_PULL_UP );

	Gpio_ConfigPin(GPIO_A, VEHICLE_LOCK_LED,GPIO_OUTPUT, GPIO_PUSH_PULL);  //vehicle lock,
	Gpio_ConfigPin(GPIO_A, HAZARD_LED,GPIO_OUTPUT, GPIO_PUSH_PULL);    //hazard lights
	Gpio_ConfigPin(GPIO_A, AMBIENT_LED,GPIO_OUTPUT, GPIO_PUSH_PULL);    ///ambient light.



	DefaultState();





   while(1){


		if (!doorUnlocked && !antiTheftLock){ // unlock  defualte state doorlocked
		if (!Gpio_ReadPin(GPIO_A ,1)){  
			 DoorUnlockState() ;

		}

		}

		if (doorUnlocked){ // open door 
			if (!Gpio_ReadPin(GPIO_A ,2)){ // done 
				DoorOpenState();
				
			}
		}


		if (doorUnlocked && !antiTheftLock){  //anti theft 
			
			if (flag==0)
			{
				GPT_StartTimer (10000) ;
				flag=1 ;
				

			}
			else if (GPT_CheckTimeIsElapsed())
			{
				AntiTheftLockState();
				flag=0 ;
			}
		}

		if (doorUnlocked && antiTheftLock){ // close door 
			if (!Gpio_ReadPin(GPIO_A ,2)){
				ClosingDoorState();
				
			}

		}

		if (doorUnlocked && !antiTheftLock){  // lock door 
			if (!Gpio_ReadPin(GPIO_A ,1)){
				LockingDoorState() ;			
		}
		}


   } // end while 
	return 0 ;
}




void DefaultState(void) {
    // Lock the vehicle door
	Gpio_WritePin(GPIO_A,VEHICLE_LOCK_LED, LOW);
    // Turn off the hazard LED
	Gpio_WritePin(GPIO_A,HAZARD_LED, LOW);
    // Turn off the ambient light LED
	Gpio_WritePin(GPIO_A,AMBIENT_LED, LOW);

    doorUnlocked = 0;
    antiTheftLock = 0;
}



//// Implementation of use case: Door unlock
void DoorUnlockState(void) {
    // Unlock the vehicle door
	Gpio_WritePin(GPIO_A,VEHICLE_LOCK_LED, HIGH);
    // Blink the hazard LED once every second
	Gpio_WritePin(GPIO_A,HAZARD_LED, HIGH);
	Gpio_WritePin(GPIO_A,AMBIENT_LED, HIGH);

	GPT_StartTimer(500);
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,HAZARD_LED, LOW);
	GPT_StartTimer(500);
	while (! GPT_CheckTimeIsElapsed());
	GPT_StartTimer(1000);
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,AMBIENT_LED, LOW);
    doorUnlocked = 1;
    antiTheftLock = 0;
}


void DoorOpenState(void) {
   // Unlock the vehicle door and turn on the ambient light LED
   Gpio_WritePin(GPIO_A,AMBIENT_LED, HIGH);
   GPT_StartTimer(1000) ;
   while (! GPT_CheckTimeIsElapsed());
   doorUnlocked = 1;
   antiTheftLock = 1;

  
   
}

void AntiTheftLockState(void) {

	 // lock the vehicle door
	Gpio_WritePin(GPIO_A,VEHICLE_LOCK_LED, LOW);
	Gpio_WritePin(GPIO_A,AMBIENT_LED, LOW);
	 // Blink the hazard LED once every second
	Gpio_WritePin(GPIO_A,HAZARD_LED, HIGH);
	GPT_StartTimer(500);
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,HAZARD_LED, LOW);
	GPT_StartTimer(500);
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,HAZARD_LED, HIGH);
	GPT_StartTimer(500);
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,HAZARD_LED, LOW);



 	doorUnlocked = 0;
 	antiTheftLock=0;	

}



void ClosingDoorState(void){

	Gpio_WritePin(GPIO_A,VEHICLE_LOCK_LED, LOW);
	Gpio_WritePin(GPIO_A,HAZARD_LED, LOW);
	Gpio_WritePin(GPIO_A,AMBIENT_LED, LOW);
	GPT_StartTimer(1000) ;
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,AMBIENT_LED, HIGH);
	GPT_StartTimer(1000) ;
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,AMBIENT_LED, LOW);
   doorUnlocked = 1;
   antiTheftLock = 0;



}



void LockingDoorState(void){

	Gpio_WritePin(GPIO_A,VEHICLE_LOCK_LED, LOW);
	Gpio_WritePin(GPIO_A,AMBIENT_LED, LOW);

	Gpio_WritePin(GPIO_A,HAZARD_LED, HIGH);
	GPT_StartTimer(500);
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,HAZARD_LED, LOW);
	GPT_StartTimer(500);
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,HAZARD_LED, HIGH);
	GPT_StartTimer(500);
	while (! GPT_CheckTimeIsElapsed());
	Gpio_WritePin(GPIO_A,HAZARD_LED, LOW);
	
  doorUnlocked = 0;
  antiTheftLock = 0;

}


