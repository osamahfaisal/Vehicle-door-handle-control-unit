#ifndef GPIO_H
#define GPIO_H
#include "Std_Types.h"

/* portName */
#define GPIO_A 'A'
#define GPIO_B 'B'
#define GPIO_C 'C'
#define GPIO_D 'D'


/* pinMode */
#define  GPIO_INPUT          0x00
#define  GPIO_OUTPUT         0x01
#define  GPIO_ANALOG         0x02
#define  GPIO_AF             0x03


/* defualte state  push_pull or open_drain*/
#define GPIO_PUSH_PULL  0x00
#define   GPIO_OPEN_DRAIN   0x01

// #define  GPIO_INPUT_PULL_UP 0x01
// #define  GPIO_INPUT_PUL_DWAN  0x02

#define GPIO_NO_PULL   (0x00 << 1)
#define GPIO_PULL_UP   (0x01 << 1)
#define GPIO_PULL_DOWN (0x02 << 1)


#define HIGH       0x01
#define LOW        0x00

#define OK  0x00
#define  NOK 0x01




void Gpio_ConfigPin(uint8 PortName, uint8 PinNum, uint8 PinMode, uint8 DefaultState);
void Gpio_WritePin(uint8 PortName, uint8 PinNum, uint8 Data);
uint8 Gpio_ReadPin(uint8 PortName, uint8 PinNum);

                  //  (portNAme (port A or B or C), pinNumber (position of pin in port ),pinMode(the pi is output or input or analog ) , unit8 DefaultState);
// void GPIO_ConfigPin(uint8 portName , uint8 pinNumber, uint8 pinMode , uint8 DefaultState);



// uint8 GPIO_WritePin( uint8 portName, uint8 pinNumber , uint8 Data);
// uint8 GPIO_ReadPin( uint8 portName  , uint8 pinNumber) ;



#endif
