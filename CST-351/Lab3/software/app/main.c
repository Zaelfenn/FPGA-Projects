#include <stdio.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"


int main(void)
{
	printf("Hello NIOS V World\n");
	int switch_value;
	while(1)
	{
		switch_value = IORD_ALTERA_AVALON_PIO_DATA(SWITCHES_BASE);
		printf("Value on switch: %2x\n", switch_value);
		IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, switch_value);
	}

	return 0;
}
