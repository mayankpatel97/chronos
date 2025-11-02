#include "main.h"
#include "chronos.h"


static void blink(void *arg) {
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	/* toggle LED, etc. */
	LOG("LOG Message from blink1\r\n");
}

static void blink2(void *arg) {
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
    LOG("LOG Message from blink2\r\n");
}


int uart_write_char(char c) {
    while (!(USART2->SR & USART_SR_TXE));
    USART2->DR = c;
    return c;
}

void app(void)
{
	LOG_INIT(uart_write_char);
	/* Run blink every 500 ms, start after 0 ms */
	chronos_add(blink, NULL, 1000, 0);

	chronos_add(blink2, NULL, 1000, 50);

	/* Hand control to cooperative dispatcher (never returns) */
	chronos_run();
	while(1) {

	}
}
