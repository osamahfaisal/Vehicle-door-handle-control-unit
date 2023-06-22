#ifndef GPIO_PRIVATE_H
#define  GPIO_PRIVATE_H

#include "Std_Types.h"






// ((( uint32 *)(0x40020000))+1) == ==  (*(uint32 *)((BASE_ADDR) + (OFFSET)) // (*pointer derefranceing pointer )

// passed address 
#define GPIOA_BASE_ADDR     0x40020000
#define GPIOB_BASE_ADDR     0x40020400
#define GPIOC_BASE_ADDRESS   0x40020800
#define GPIOD_BASE_ADDRESS   0x40020C00





typedef struct {  // by sort element by offset  this mean when create pointer refrancing to  GpioA or GpioB  ..
                  // int *p = GPIOA_BASE_ADDR --> if  want go to  moder  i will do --->> (*p).GPIO_MODER=0;-->> == (GPIOA_BASE_ADDR+0x00) and so on

	uint32 GPIO_MODER;
	uint32 GPIO_OTYPER;
	uint32 GPIO_OSPEEDR;
	uint32 GPIO_PUPDR;
	uint32 GPIO_IDR;
	uint32 GPIO_ODR;
	uint32 GPIO_BSRR;
	uint32 GPIO_LCKR;
	uint32 GPIO_AFRL;
	uint32 GPIO_AFRH;
} GpioType;

#endif
