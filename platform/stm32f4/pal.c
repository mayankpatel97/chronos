#include "pal.h"
#include "stm32f4xx.h"

static volatile uint32_t ms_tick;

void SysTick_Handler(void) { ms_tick++; }

void pal_init(void) {
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);   // 1 ms
    NVIC_SetPriority(SysTick_IRQn, 0);
    /* UART2 for console (optional) */
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= (2<<6) | (2<<8);          // PA2/TX, PA3/RX
    GPIOA->AFR[0] |= (7<<8) | (7<<12);
    USART2->BRR = SystemCoreClock / 115200;
    USART2->CR1 = USART_CR1_TE | USART_CR1_UE;
}