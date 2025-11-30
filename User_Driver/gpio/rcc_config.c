
/***************************************************************************************************
*                                        INCLUDE FILES
***************************************************************************************************/

#include "gpio_config.h"
#include "stm32f4xx.h"
 
/***************************************************************************************************
*                         LOCAL TYPEDEFS (DEFINE, STRUCTURES, UNIONS, ENUMS)
***************************************************************************************************/
 
/***************************************************************************************************
*                                      GLOBAL VARIABLES
***************************************************************************************************/
 
/***************************************************************************************************
*                                   		PROTOTYPE
***************************************************************************************************/

static GPIO_TypeDef* Gpio_GetPortPtr(uint8_t port_idx);
 
/***************************************************************************************************
*                                 	FUNCTIONS DEFINITIONS
***************************************************************************************************/

void Gpio_InitPin(uint8_t port, uint8_t pin, Gpio_ModeType mode, Gpio_SpeedType speed, Gpio_PullType pull, uint8_t initial_state, uint8_t alt_func)
{
    GPIO_TypeDef *PortPtr = Gpio_GetPortPtr(port);
    if (PortPtr == NULL || pin > 15) return;

    PortPtr->MODER &= ~(3U << (pin * 2));                    // clear
    PortPtr->MODER |=  ((uint32_t)mode << (pin * 2));        // set

    if (mode == GPIO_MODE_OUTPUT || mode == GPIO_MODE_ALTERNATE) {
        PortPtr->OTYPER &= ~(1U << pin);     // push-pull
    }

    PortPtr->OSPEEDR &= ~(3U << (pin * 2));
    PortPtr->OSPEEDR |= ((uint32_t)speed << (pin * 2));

    PortPtr->PUPDR &= ~(3U << (pin * 2));
    PortPtr->PUPDR |= ((uint32_t)pull << (pin * 2));

    if (mode == GPIO_MODE_ALTERNATE) {
        if (pin < 8) {
            PortPtr->AFR[0] &= ~(0xFU << (pin * 4));
            PortPtr->AFR[0] |= ((uint32_t)(alt_func & 0x0F) << (pin * 4));
        } else {
            uint8_t p = pin - 8;
            PortPtr->AFR[1] &= ~(0xFU << (p * 4));
            PortPtr->AFR[1] |= ((uint32_t)(alt_func & 0x0F) << (p * 4));
        }
    }

    if (mode == GPIO_MODE_OUTPUT) {
        if (initial_state) {
            PortPtr->BSRR = (1U << pin);           // set
        } else {
            PortPtr->BSRR = (1U << (pin + 16));    // reset
        }
    }
}

static GPIO_TypeDef* Gpio_GetPortPtr(uint8_t port_idx)
{
    switch (port_idx)
    {
        case GPIO_PORT_A: return GPIOA;
        case GPIO_PORT_B: return GPIOB;
        case GPIO_PORT_C: return GPIOC;
        case GPIO_PORT_D: return GPIOD;
        case GPIO_PORT_E: return GPIOE;
        case GPIO_PORT_F: return GPIOF;
        case GPIO_PORT_G: return GPIOG;
        case GPIO_PORT_H: return GPIOH;
        case GPIO_PORT_I: return GPIOI;
        default:          return NULL;
    }
}

void Gpio_WritePin(uint8_t port, uint8_t pin, uint8_t state)
{
    GPIO_TypeDef *PortPtr = Gpio_GetPortPtr(port);
    if (PortPtr == NULL || pin > 15) return;

    if (state)
        PortPtr->BSRR = (1U << pin);         // Set pin
    else
        PortPtr->BSRR = (1U << (pin + 16));  // Reset pin
}

uint8_t Gpio_ReadPin(uint8_t port, uint8_t pin)
{
    GPIO_TypeDef *PortPtr = Gpio_GetPortPtr(port);
    if (PortPtr == NULL || pin > 15) return 0;

    return (uint8_t)((PortPtr->IDR >> pin) & 0x01);
}

void Gpio_SetPinSpeed(uint8_t port, uint8_t pin, Gpio_SpeedType speed)
{
    GPIO_TypeDef *PortPtr = Gpio_GetPortPtr(port);
    if (PortPtr == NULL || pin > 15) return;

    PortPtr->OSPEEDR &= ~(3U << (pin * 2));
    PortPtr->OSPEEDR |= ((uint32_t)speed << (pin * 2));
}

void Gpio_SetPinMode(uint8_t port, uint8_t pin, Gpio_ModeType mode)
{
    GPIO_TypeDef *PortPtr = Gpio_GetPortPtr(port);
    if (PortPtr == NULL || pin > 15) return;

    PortPtr->MODER &= ~(3U << (pin * 2));
    PortPtr->MODER |= ((uint32_t)mode << (pin * 2));
}

void Gpio_SetPinPull(uint8_t port, uint8_t pin, Gpio_PullType pull)
{
    GPIO_TypeDef *PortPtr = Gpio_GetPortPtr(port);
    if (PortPtr == NULL || pin > 15) return;

    PortPtr->PUPDR &= ~(3U << (pin * 2));
    PortPtr->PUPDR |= ((uint32_t)pull << (pin * 2));
}

void Gpio_InitLed()
{
	Gpio_InitPin(GPIO_PORT_D, GPIO_PIN_12, GPIO_MODE_OUTPUT, GPIO_SPEED_HIGH, GPIO_NOPULL, 0, 0);
	Gpio_InitPin(GPIO_PORT_D, GPIO_PIN_13, GPIO_MODE_OUTPUT, GPIO_SPEED_HIGH, GPIO_NOPULL, 0, 0);
	Gpio_InitPin(GPIO_PORT_D, GPIO_PIN_14, GPIO_MODE_OUTPUT, GPIO_SPEED_HIGH, GPIO_NOPULL, 0, 0);
	Gpio_InitPin(GPIO_PORT_D, GPIO_PIN_15, GPIO_MODE_OUTPUT, GPIO_SPEED_HIGH, GPIO_NOPULL, 0, 0);
}

void Gpio_GreenLed_On()
{
	Gpio_WritePin(GPIO_PORT_D, GPIO_PIN_12, 1);
}

void Gpio_GreenLed_Off()
{
	Gpio_WritePin(GPIO_PORT_D, GPIO_PIN_12, 0);
}

void Gpio_OrangeLed_On()
{
	Gpio_WritePin(GPIO_PORT_D, GPIO_PIN_13, 1);
}

void Gpio_OrangeLed_Off()
{
	Gpio_WritePin(GPIO_PORT_D, GPIO_PIN_13, 0);
}

void Gpio_RedLed_On()
{
	Gpio_WritePin(GPIO_PORT_D, GPIO_PIN_14, 1);
}

void Gpio_RedLed_Off()
{
	Gpio_WritePin(GPIO_PORT_D, GPIO_PIN_14, 0);
}

void Gpio_BlueLed_On()
{
	Gpio_WritePin(GPIO_PORT_D, GPIO_PIN_15, 1);
}

void Gpio_BlueLed_Off()
{
	Gpio_WritePin(GPIO_PORT_D, GPIO_PIN_15, 0);
}


///////////////////////////////// END OF FILE ///////////////////////////////