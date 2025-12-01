/***************************************************************************************************
*                                        INCLUDE FILES
***************************************************************************************************/

#include <string.h>
#include "uart_config.h"
#include "stm32f4xx.h"
#include "stub.h"
 
/***************************************************************************************************
*                         LOCAL TYPEDEFS (DEFINE, STRUCTURES, UNIONS, ENUMS)
***************************************************************************************************/
 
 
/***************************************************************************************************
*                                      GLOBAL VARIABLES
***************************************************************************************************/
 
static volatile uint32_t  rx_count = 0;
static volatile uint8_t rx_buf[USART3_RX_BUF_SIZE];
 
/***************************************************************************************************
*                                   		INTERNAL PROTOTYPE
***************************************************************************************************/


 
/***************************************************************************************************
*                                 	FUNCTIONS DEFINITIONS
***************************************************************************************************/

/* Helper: compute APB1 clock from SystemCoreClock and RCC->CFGR PPRE1 */
static uint32_t GetPCLK1Freq(void)
{
    uint32_t ppre1 = (RCC->CFGR & RCC_CFGR_PPRE1_Msk) >> RCC_CFGR_PPRE1_Pos;
    uint32_t presc = 1U;
    if (ppre1 >= 4U) {
        /* mapping: 100 -> /2 (ppre1==4), 101 -> /4 (5), 110 -> /8 (6), 111 -> /16 (7) */
        presc = (1U << (ppre1 - 3U));
    }
    return SystemCoreClock / presc;
}

/* Configure PD8 (AF7 USART3 TX) and PD9 (AF7 USART3 RX), enable USART3 clock and setup BRR */
void USART3_Init(uint32_t baudrate)
{
    /* 1. Enable GPIOD clock if not already (safe to set) */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    (void)RCC->AHB1ENR; /* readback */

    /* 2. Configure PD8, PD9 as AF (alternate function 7 = USART1/2/3) */
    /* Set MODER8/9 = 10 (alternate) */
    GPIOD->MODER &= ~( (3U << (8*2)) | (3U << (9*2)) );
    GPIOD->MODER |=  ( (2U << (8*2)) | (2U << (9*2)) );

    /* Set OTYPER = push-pull (0) */
    GPIOD->OTYPER &= ~( (1U << 8) | (1U << 9) );

    /* Set OSPEEDR = high */
    GPIOD->OSPEEDR &= ~( (3U << (8*2)) | (3U << (9*2)) );
    GPIOD->OSPEEDR |=  ( (2U << (8*2)) | (2U << (9*2)) );

    /* Pull-up RX/TX (common) */
    GPIOD->PUPDR &= ~( (3U << (8*2)) | (3U << (9*2)) );
    GPIOD->PUPDR |=  ( (1U << (8*2)) | (1U << (9*2)) ); /* pull-up */

    /* Set AF7 for PD8/PD9 (AFR[1], pin 8 -> pos 0, pin 9 -> pos 4) */
    GPIOD->AFR[1] &= ~((0xFU << ((8 - 8) * 4)) | (0xFU << ((9 - 8) * 4)));
    GPIOD->AFR[1] |=  ((7U & 0xFU) << ((8 - 8) * 4)) | ((7U & 0xFU) << ((9 - 8) * 4));

    /* 3. Enable USART3 clock on APB1 */
    RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
    (void)RCC->APB1ENR; /* readback */

    /* 4. Disable USART before config */
    USART3->CR1 &= ~USART_CR1_UE;

    /* 5. Compute and set BRR (oversampling by 16) */
    uint32_t pclk1 = GetPCLK1Freq(); /* Hz */
    /* usartdiv * 16 to compute mantissa and fraction with integers */
    uint64_t usartdiv16 = ((uint64_t)pclk1 * 16ULL + (baudrate/2)) / (uint64_t)baudrate;
    uint32_t mantissa = (uint32_t)(usartdiv16 / 16ULL);
    uint32_t fraction = (uint32_t)(usartdiv16 - (mantissa * 16U));
    USART3->BRR = (mantissa << 4) | (fraction & 0xF);

    /* 6. Configure CR1: 8 data bits, no parity, enable TE and RE */
    USART3->CR1 &= ~(USART_CR1_M | USART_CR1_PCE); /* M=0 -> 8 data; PCE=0 parity off */
    USART3->CR1 |= (USART_CR1_TE | USART_CR1_RE);

    /* 7. Optionally configure CR2/CR3 (1 stop-bit default) - keep defaults */

    /* 8. Enable USART */
    USART3->CR1 |= USART_CR1_UE;

    /* 9. Wait until TE/RE are effective (optional small delay) */
    SysTick_Delay(10);
}

/* Disable USART3 and optionally disable clock */
void USART3_DeInit(void)
{
    USART3->CR1 &= ~USART_CR1_UE;
    // optionally disable clock:
    RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
}

/* Blocking send one byte */
void USART3_SendByte(uint8_t b)
{
    /* Wait until TXE = 1 (data register empty) */
    while (!(USART3->SR & USART_SR_TXE)) { /* wait */ }
    USART3->DR = (b & 0xFF);
    /* Wait until TC = 1 (transmission complete) if you need
       to ensure last byte fully sent: */
    while (!(USART3->SR & USART_SR_TC)) { /* wait */ }
}

/* Send buffer (blocking) */
void USART3_SendBuffer(uint8_t *buf)
{
    uint32_t i = 0;
    uint32_t len = strlen(buf);
    for (uint32_t i = 0; i < len; ++i) {
        /* Wait TXE */
        while (!(USART3->SR & USART_SR_TXE)) { }
        USART3->DR = buf[i];
    }
    /* wait for final byte complete */
    while (!(USART3->SR & USART_SR_TC)) { }
}

/* Blocking receive one byte (wait until RXNE) */
uint8_t USART3_RecvByteBlocking(void)
{
    while (!(USART3->SR & USART_SR_RXNE)) { }
    uint8_t val = (uint8_t)(USART3->DR & 0xFF);
    return val;
}

static int rx_buf_push(uint8_t b)
{
    if (rx_count >= USART3_RX_BUF_SIZE) 
    {
        return 0; /* full */
    }
    rx_buf[rx_count] = b;
    rx_count++;
    return 1;
}

/* Pop a string from ring buffer. Return 1 if ok, 0 if empty. */
static int rx_buf_pop(uint8_t *b, uint32_t maxlen)
{
    uint32_t i = 0;
    if (rx_count == 0) 
    {
        return 0;
    }
    NVIC_DisableIRQ(USART3_IRQn);
    for (i = 0; i < maxlen; i++) 
    {
        b[i] = rx_buf[i];
        rx_buf[i] = 0; /* optional: clear */
        if(rx_count == 0)
        {
            break;
        }
        rx_count--;
    }
    NVIC_EnableIRQ(USART3_IRQn);
    return 1;
}

uint8_t USART3_ReadBuffer(uint8_t *buf, uint32_t maxlen)
{
    uint8_t Retval = 0;
    Retval = rx_buf_pop (buf, maxlen);
    return Retval;
}

/* Public APIs */
void USART3_EnableRxIT(void)
{
    /* Enable RXNE interrupt in USART3 */
    USART3->CR1 |= USART_CR1_RXNEIE;

    /* Enable NVIC IRQ for USART3 with medium priority */
    NVIC_SetPriority(USART3_IRQn, 5); /* adjust priority as needed */
    NVIC_EnableIRQ(USART3_IRQn);
}

void USART3_DisableRxIT(void)
{
    USART3->CR1 &= ~USART_CR1_RXNEIE;
    NVIC_DisableIRQ(USART3_IRQn);
}

void USART3_IRQHandler(void)
{
    uint32_t sr = USART3->SR;

    /* RXNE: Read data register - reading DR clears RXNE */
    if (sr & USART_SR_RXNE)
    {
        uint8_t b = (uint8_t)(USART3->DR & 0xFF); /* reading DR clears RXNE */
        /* push into ring buffer; if full, drop silently (or count overflow) */
        rx_buf_push(b);
    }

    /* handle other IRQ sources if you enable them later (TXE, TC, ORE, etc) */
    /* e.g., clear ORE by reading SR and DR if needed */
    if (sr & USART_SR_ORE)
    {
        volatile uint32_t tmp = USART3->DR; (void)tmp; /* clear ORE by reading DR */
    }
}

/***************************************************************************************************
*                                 	END OF FILE
***************************************************************************************************/