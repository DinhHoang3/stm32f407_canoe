#ifndef _RCC_CFG_H_
#define _RCC_CFG_H_

/***************************************************************************************************
*                                        INCLUDE FILES
***************************************************************************************************/

#include "general_type.h"
 
 /***************************************************************************************************
*                                   		GLOBAL PROTOTYPE
***************************************************************************************************/

 void Rcc_Init(void);
 
/***************************************************************************************************
*                         LOCAL TYPEDEFS (DEFINE, STRUCTURES, UNIONS, ENUMS)
***************************************************************************************************/
 
typedef enum
{
    RCC_AHB_NO_DIVIDED      = 0x00,
    RCC_AHB_DIVIDED_2       = 0x04,
    RCC_AHB_DIVIDED_4       = 0x05,
    RCC_AHB_DIVIDED_8       = 0x06,
    RCC_AHB_DIVIDED_16      = 0x07
} Rcc_APBPrescType;

typedef enum
{
    RCC_SYSCLK_NO_DIVIDED   = 0x00,
    RCC_SYSCLK_DIVIDED_2    = 0x08,
    RCC_SYSCLK_DIVIDED_4    = 0x09,
    RCC_SYSCLK_DIVIDED_8    = 0x0A,
    RCC_SYSCLK_DIVIDED_16   = 0x0B,
    RCC_SYSCLK_DIVIDED_64   = 0x0C,
    RCC_SYSCLK_DIVIDED_128  = 0x0D,
    RCC_SYSCLK_DIVIDED_256  = 0x0E,
    RCC_SYSCLK_DIVIDED_512  = 0x0F
} Rcc_AHBPrescType;

typedef enum {
    RCC_PLLP_DIV_2 = 0x00,  // PLLP = 2
    RCC_PLLP_DIV_4 = 0x01,  // PLLP = 4
    RCC_PLLP_DIV_6 = 0x02,  // PLLP = 6
    RCC_PLLP_DIV_8 = 0x03   // PLLP = 8
} Rcc_PLLPPrescType;

#define HSI                    0
#define HSE                    1
#define PLL                    2

#define CLOCK_INPUT            HSE

#define SYS_CLOCK_SRC          PLL

#define PLL_SRC                HSE

#define HSE_RTC_PRESC          2

#define AHB_PRESC              RCC_SYSCLK_NO_DIVIDED

#define APB1_PRESC             RCC_AHB_NO_DIVIDED

#define APB2_PRESC             RCC_AHB_NO_DIVIDED

#define PLLM_PRESC             8

#define PLLP_PRESC             RCC_PLLP_DIV_2

#define PLLQ_PRESC             7

#define PLLN_MUL               336


// APB1 Peripheral Clock Enable
#define RCC_APB1ENR_DAC         STD_OFF
#define RCC_APB1ENR_PWR         STD_OFF
#define RCC_APB1ENR_CAN2        STD_OFF
#define RCC_APB1ENR_CAN1        STD_OFF
#define RCC_APB1ENR_I2C3        STD_OFF
#define RCC_APB1ENR_I2C2        STD_OFF
#define RCC_APB1ENR_I2C1        STD_OFF
#define RCC_APB1ENR_UART5       STD_OFF
#define RCC_APB1ENR_UART4       STD_OFF
#define RCC_APB1ENR_USART3      STD_OFF
#define RCC_APB1ENR_USART2      STD_OFF
#define RCC_APB1ENR_SPI3        STD_OFF
#define RCC_APB1ENR_SPI2        STD_OFF
#define RCC_APB1ENR_WWDG        STD_OFF
#define RCC_APB1ENR_TIM2        STD_OFF
#define RCC_APB1ENR_TIM3        STD_OFF
#define RCC_APB1ENR_TIM4        STD_OFF
#define RCC_APB1ENR_TIM5        STD_OFF
#define RCC_APB1ENR_TIM6        STD_OFF
#define RCC_APB1ENR_TIM7        STD_OFF
#define RCC_APB1ENR_TIM12       STD_OFF
#define RCC_APB1ENR_TIM13       STD_OFF
#define RCC_APB1ENR_TIM14       STD_OFF

// APB2 Peripheral Clock Enable
#define RCC_APB2ENR_SYSCFG      STD_OFF
#define RCC_APB2ENR_USART6      STD_OFF
#define RCC_APB2ENR_USART1      STD_OFF
#define RCC_APB2ENR_SDIO        STD_OFF
#define RCC_APB2ENR_SPI1        STD_OFF
#define RCC_APB2ENR_ADC3        STD_OFF
#define RCC_APB2ENR_ADC2        STD_OFF
#define RCC_APB2ENR_ADC1        STD_OFF
#define RCC_APB2ENR_TIM1        STD_OFF
#define RCC_APB2ENR_TIM8        STD_OFF
#define RCC_APB2ENR_TIM9        STD_OFF
#define RCC_APB2ENR_TIM10       STD_OFF
#define RCC_APB2ENR_TIM11       STD_OFF

// AHB GPIO Peripheral Clock Enable
#define GPIOA_RCCEN                   STD_OFF
#define GPIOB_RCCEN                   STD_OFF
#define GPIOC_RCCEN                   STD_OFF
#define GPIOD_RCCEN                   STD_ON
#define GPIOE_RCCEN                   STD_OFF
#define GPIOF_RCCEN                   STD_OFF
#define GPIOG_RCCEN                   STD_OFF
#define GPIOH_RCCEN                   STD_OFF
#define GPIOI_RCCEN                   STD_OFF
 
/***************************************************************************************************
*                                      GLOBAL VARIABLES
***************************************************************************************************/
 

 
/***************************************************************************************************
*                                   		PROTOTYPE
***************************************************************************************************/



/***************************************************************************************************
*                                 	FUNCTIONS DEFINITIONS
***************************************************************************************************/

#endif // _RCC_CFG_H_