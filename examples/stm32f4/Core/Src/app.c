#include "main.h"
#include "chronos.h"


static void blink(void *arg) {
	HAL_GPIO_TogglePin(LD4_GPIO_Port, LD4_Pin);
	/* toggle LED, etc. */
}

static void blink2(void *arg) {
	HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
    /* read sensors without blocking */
}


void app(void)
{
	/* Run blink every 500 ms, start after 0 ms */
	chronos_add(blink, NULL, 1000, 0);

	chronos_add(blink2, NULL, 1000, 50);

	/* Hand control to cooperative dispatcher (never returns) */
	chronos_run();
	while(1) {

	}
}
