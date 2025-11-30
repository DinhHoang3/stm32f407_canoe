#ifndef _GPIO_H_
#define _GPIO_H_

/***************************************************************************************************
*                                        INCLUDE FILES
***************************************************************************************************/

#include "general_type.h"
 
/***************************************************************************************************
*                         LOCAL TYPEDEFS (DEFINE, STRUCTURES, UNIONS, ENUMS)
***************************************************************************************************/
 
typedef enum {
    GPIO_SPEED_LOW          = 0x00,  // Low speed
    GPIO_SPEED_MEDIUM       = 0x01,  // Medium speed
    GPIO_SPEED_HIGH         = 0x02,  // High speed
    GPIO_SPEED_VERY_HIGH    = 0x03   // Very high speed
} Gpio_SpeedType;

typedef enum {
    GPIO_STATE_BUSY         = 0x00,  
    GPIO_STATE_IDLE         = 0x01,  
} Gpio_StateType;

typedef enum {
    GPIO_MODE_INPUT         = 0x00,  // Input (reset state)
    GPIO_MODE_OUTPUT        = 0x01,  // General purpose output mode
    GPIO_MODE_ALTERNATE     = 0x02,  // Alternate function mode
    GPIO_MODE_ANALOG        = 0x03   // Analog mode
} Gpio_ModeType;

typedef enum {
    GPIO_NOPULL             = 0x00,  // No pull-up, pull-down
    GPIO_PULLUP             = 0x01,  // Pull-up
    GPIO_PULLDOWN           = 0x02  // Pull-down
} Gpio_PullType;

typedef struct GpioPinConfigType{
    Gpio_PullType       Pin_PullType;
    Gpio_ModeType       Pin_ModeType;
    Gpio_SpeedType      Pin_SpeedType;
    Gpio_StateType      Pin_State;
    uint8_t             Pin_Idx;
} Gpio_PinConfigType;

typedef struct GpioPortConfigType{
    Gpio_PinConfigType *Pin_Config;
    uint8_t             Port_Idx;
} Gpio_PortConfigType;

typedef struct {
    Gpio_PortConfigType *Port_Config;
} Gpio_ControllConfigType;
 
#define GPIO_PIN_0   0
#define GPIO_PIN_1   1
#define GPIO_PIN_2   2
#define GPIO_PIN_3   3
#define GPIO_PIN_4   4
#define GPIO_PIN_5   5
#define GPIO_PIN_6   6
#define GPIO_PIN_7   7
#define GPIO_PIN_8   8
#define GPIO_PIN_9   9
#define GPIO_PIN_10  10
#define GPIO_PIN_11  11
#define GPIO_PIN_12  12
#define GPIO_PIN_13  13
#define GPIO_PIN_14  14
#define GPIO_PIN_15  15

#define GPIO_PORT_A   0
#define GPIO_PORT_B   1
#define GPIO_PORT_C   2
#define GPIO_PORT_D   3
#define GPIO_PORT_E   4
#define GPIO_PORT_F   5
#define GPIO_PORT_G   6
#define GPIO_PORT_H   7
#define GPIO_PORT_I   8


/***************************************************************************************************
*                                      GLOBAL VARIABLES
***************************************************************************************************/
 

 
/***************************************************************************************************
*                                   		PROTOTYPE
***************************************************************************************************/

void Gpio_Init(void);
void Gpio_WritePin(uint8_t port, uint8_t pin, uint8_t state);
uint8_t Gpio_ReadPin(uint8_t port, uint8_t pin);
void Gpio_SetPinSpeed(uint8_t port, uint8_t pin, Gpio_SpeedType speed);
void Gpio_SetPinMode(uint8_t port, uint8_t pin, Gpio_ModeType mode);
void Gpio_SetPinPull(uint8_t port, uint8_t pin, Gpio_PullType pull);

/***************************************************************************************************
*                                 	FUNCTIONS DEFINITIONS
***************************************************************************************************/

#endif // _GPIO_H_