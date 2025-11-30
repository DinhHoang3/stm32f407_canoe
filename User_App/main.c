#include "stm32f407xx.h"
#include "rcc_config.h"
#include "gpio_config.h"
#include "stub.h"


int main(void) {
    Rcc_Init();
		SysTick_DelayInit();
		Gpio_InitLed();
    while(1) 
		{
			  Gpio_OrangeLed_Off(); 
        SysTick_Delay(200);

        Gpio_OrangeLed_On();  
        SysTick_Delay(200);
    }
}


