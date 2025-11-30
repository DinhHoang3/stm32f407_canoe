
#include "stm32f407xx.h"
#include "stub.h"



int main(void) {
    // 1. B?t clock cho GPIOD (bit 3 trong RCC_AHB1ENR)
    RCC->AHB1ENR |= (1 << 3);

    // 2. C?u hình PD12 là Output (MODER12 = 01)
    GPIOD->MODER &= ~(3 << (12 * 2));  // Xóa 2 bit
    GPIOD->MODER |=  (1 << (12 * 2));  // Set bit 01

    // 3. Push-Pull & No Pull-up/down (tu? ch?n)
    GPIOD->OTYPER &= ~(1 << 12);       // Push-Pull
    GPIOD->PUPDR &= ~(3 << (12 * 2));  // No Pull
		SysTick_DelayInit();
    while(1) {
        GPIOD->ODR |= (1 << 12);   // B?t LED
        SysTick_Delay(500);

        GPIOD->ODR &= ~(1 << 12);  // T?t LED
        SysTick_Delay(500);
    }
}