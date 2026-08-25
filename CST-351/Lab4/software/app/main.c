#include <stdio.h>
#include "system.h"
#include "intel_lw_uart_regs.h"
#include "altera_avalon_pio_regs.h"
#include <unistd.h>

int main(void)
{
	char button_in, uart_in, button_state = 0, button_prev = 1;
	unsigned int distance = 0;
	printf("TOF210120 Sensor Start\n");
	while(1)
	{
		button_in = IORD_ALTERA_AVALON_PIO_DATA(BUTTON_IN_BASE) & 1;
		if (!button_in && button_prev)
		{
			button_state = !button_state;
		}
		button_prev = button_in;

		if (IORD_INTEL_LW_UART_STATUS(LW_UART_BASE) & INTEL_LW_UART_STATUS_TRDY_MSK)
		{
			uart_in = IORD_INTEL_LW_UART_RXDATA(LW_UART_BASE);
			if(uart_in > 0x29 && uart_in < 0x3a)
			{
				distance = (distance * 10) + (uart_in - 0x30); //convert char to mm
			}
			else if (uart_in == '\n')
			{
				if (distance)
				{
					if(button_state) //inches
					{
						printf("Distance: %4.2f in\n", (float)distance / 25.4);

					}
					else			//mm
					{
						printf("Distance: %d mm\n", distance);
					}

				}
				distance = 0;
			}

		}


	}

	return 0;
}
