#include <string.h>
#include "stub.h"
#include "rcc_config.h"
#include "gpio_config.h"
#include "uart_config.h"


int main(void) {
    Rcc_Init();
		SysTick_DelayInit();
    USART3_Init(9600);
		Gpio_InitLed();
    const char *msg = "Hello from USART3!\r\n";
		Gpio_BlueLed_On();
    USART3_SendBuffer((const uint8_t*)msg, strlen(msg));
		
    while(1) 
		{
        uint8_t c = USART3_RecvByteBlocking();  // nhận ký tự
        USART3_SendByte(c);   
    }
}


