/*
  Name:Osamah Faisal Abdulatef
  Sec:1
  B.N:11

 * */

#include "../Gpio/Gpio.h"
#include "Std_Types.h"
#include "../Gpio/Gpio_Private.h"

// (*(uint32 *)((PORT_ID) + (REG_ID)))  with * this mean read operation mean --> read contant of this address 
//((uint32 *)((PORT_ID) + (REG_ID)))    without *   this mean address not value of address 

//GPIO_REG(offset macros , based address )  ((uint32 *)((integer +  integer )) 


#define GPIO_REG(REG_ID, PORT_ID) ((uint32 *)((PORT_ID) + (REG_ID)))  



uint32 gpioAddresses[4] = {GPIOA_BASE_ADDR, GPIOB_BASE_ADDR , GPIOC_BASE_ADDRESS , GPIOD_BASE_ADDRESS};
//uint32 gpioAddresses[4] = {0x40020000, 0x40020400 , 0x40020800 , 0x40020C00};


void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode, uint8 DefaultState) {


  uint8 OutputState = DefaultState & 0x1;
  uint8 InputState = DefaultState >> 1;

  uint8 portId = PortName - GPIO_A;
  GpioType * GpioReg= gpioAddresses[portId];


  // set moder
  (*GpioReg).GPIO_MODER &=~(0x3 << (2 * PinNum));   // clear  pinnumber
  (*GpioReg).GPIO_MODER |=(PinMode << (2 * PinNum));  // set pinnumb

  


  /* in cases following we see input data type and output data type put i one is do the other not change  */

  // output data type
  (*GpioReg).GPIO_OTYPER &= ~(0x01 << PinNum);  //  clear pinnumber
  (*GpioReg).GPIO_OTYPER |= (OutputState << PinNum); // setpinnumber

  	 /* we can do by this way */
	//  GpioReg->GPIO_OTYPER &= ~(0x01 << PinNum);  //  clear pinnumber
	//  GpioReg->GPIO_OTYPER  |= (OutputState << PinNum); // setpinnumber



  // input data type register
  GpioReg->GPIO_PUPDR  &= ~(0x3 << (2 * PinNum));  // clear
  GpioReg->GPIO_PUPDR  |= (InputState << (2 * PinNum)); // set




}





void Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data) {
  uint8 portId = PortName - GPIO_A;
  GpioType * GpioReg= gpioAddresses[portId];
  GpioReg->GPIO_ODR &= ~(0x01 << PinNum);  // clear pinnum
  GpioReg->GPIO_ODR |= (Data << PinNum);  // set data

}




uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum) {
  uint8 data = 0;
  uint8 portId = PortName - GPIO_A;
  GpioType * GpioReg= gpioAddresses[portId];
  // first way
  data=(((*GpioReg).GPIO_IDR) &(1<<PinNum) )>> PinNum;

  // second way
  data=((GpioReg->GPIO_IDR)&(1<<PinNum))>> PinNum ;




  return data;
}












