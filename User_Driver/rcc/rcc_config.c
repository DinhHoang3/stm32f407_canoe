
/***************************************************************************************************
*                                        INCLUDE FILES
***************************************************************************************************/

#include "rcc_config.h"
#include "stm32f4xx.h"
 
/***************************************************************************************************
*                         LOCAL TYPEDEFS (DEFINE, STRUCTURES, UNIONS, ENUMS)
***************************************************************************************************/
 
 
/***************************************************************************************************
*                                      GLOBAL VARIABLES
***************************************************************************************************/
 

 
/***************************************************************************************************
*                                   		INTERNAL PROTOTYPE
***************************************************************************************************/

void Rcc_EnablePeripheralClocks(void);
 
/***************************************************************************************************
*                                 	FUNCTIONS DEFINITIONS
***************************************************************************************************/

void Rcc_Init(void) 
{
    
#if CLOCK_INPUT == HSE
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY));
#elif CLOCK_INPUT == HSI
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));
#endif

#if SYS_CLOCK_SRC == PLL
    if (PLL_SRC == HSE)
        RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;
    else
        RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_HSE;

    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk |
                      RCC_PLLCFGR_PLLP_Msk | RCC_PLLCFGR_PLLQ_Msk);
    RCC->PLLCFGR |= (PLLM_PRESC << RCC_PLLCFGR_PLLM_Pos) |
                    (PLLN_MUL << RCC_PLLCFGR_PLLN_Pos) |
                    (PLLP_PRESC << RCC_PLLCFGR_PLLP_Pos) |
                    (PLLQ_PRESC << RCC_PLLCFGR_PLLQ_Pos);

    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN;
    FLASH->ACR |= FLASH_ACR_LATENCY_5WS;

    RCC->CFGR &= ~(3 << RCC_CFGR_SW_Pos);
    RCC->CFGR |= (2 << RCC_CFGR_SW_Pos); // PLL as SYSCLK

#elif SYS_CLOCK_SRC == HSE
    RCC->CFGR &= ~(3 << RCC_CFGR_SW_Pos);
    RCC->CFGR |= (1 << RCC_CFGR_SW_Pos); // HSE as SYSCLK

#elif SYS_CLOCK_SRC == HSI
    RCC->CFGR &= ~(3 << RCC_CFGR_SW_Pos);
    RCC->CFGR |= (0 << RCC_CFGR_SW_Pos); // HSI as SYSCLK
#endif

    RCC->CFGR |= ((AHB_PRESC << RCC_CFGR_HPRE_Pos) | (APB1_PRESC << RCC_CFGR_PPRE1_Pos) | (APB2_PRESC << RCC_CFGR_PPRE2_Pos));
  
    SystemCoreClockUpdate();
    Rcc_EnablePeripheralClocks();
}

void Rcc_EnablePeripheralClocks(void) 
{
    RCC->AHB1ENR |= 0x00100000;
    RCC->APB1ENR |= 0x00;
    RCC->APB2ENR |= 0x00;

    /* Enable GPIO Clocks */
#if GPIOA_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
#endif
#if GPIOB_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
#endif
#if GPIOC_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
#endif
#if GPIOD_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
#endif
#if GPIOE_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
#endif
#if GPIOF_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
#endif
#if GPIOG_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
#endif
#if GPIOH_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
#endif
#if GPIOI_RCCEN == STD_ON
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
#endif

    /* Enable APB1 Peripheral Clocks */
#if RCC_APB1ENR_DAC == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_DACEN;
#endif
#if RCC_APB1ENR_PWR == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
#endif
#if RCC_APB1ENR_CAN1 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
#endif
#if RCC_APB1ENR_CAN2 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;
#endif
#if RCC_APB1ENR_I2C1 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
#endif
#if RCC_APB1ENR_I2C2 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
#endif
#if RCC_APB1ENR_I2C3 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_I2C3EN;
#endif
#if RCC_APB1ENR_USART2 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
#endif
#if RCC_APB1ENR_USART3 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
#endif
#if RCC_APB1ENR_UART4 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
#endif
#if RCC_APB1ENR_UART5 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
#endif
#if RCC_APB1ENR_SPI2 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
#endif
#if RCC_APB1ENR_SPI3 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_SPI3EN;
#endif
#if RCC_APB1ENR_TIM2 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
#endif
#if RCC_APB1ENR_TIM3 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
#endif
#if RCC_APB1ENR_TIM4 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
#endif
#if RCC_APB1ENR_TIM5 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
#endif
#if RCC_APB1ENR_TIM6 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
#endif
#if RCC_APB1ENR_TIM7 == STD_ON
    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
#endif

    /* Enable APB2 Peripheral Clocks */
#if RCC_APB2ENR_SYSCFG == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
#endif
#if RCC_APB2ENR_USART1 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
#endif
#if RCC_APB2ENR_USART6 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_USART6EN;
#endif
#if RCC_APB2ENR_SDIO == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_SDIOEN;
#endif
#if RCC_APB2ENR_SPI1 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
#endif
#if RCC_APB2ENR_ADC1 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
#endif
#if RCC_APB2ENR_ADC2 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
#endif
#if RCC_APB2ENR_ADC3 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
#endif
#if RCC_APB2ENR_TIM1 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
#endif
#if RCC_APB2ENR_TIM8 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
#endif
#if RCC_APB2ENR_TIM9 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
#endif
#if RCC_APB2ENR_TIM10 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_TIM10EN;
#endif
#if RCC_APB2ENR_TIM11 == STD_ON
    RCC->APB2ENR |= RCC_APB2ENR_TIM11EN;
#endif
}

/***************************************************************************************************
*                                 	END OF FILE
***************************************************************************************************/