#include <unistd.h>
#include "system.h"
#include "io.h"

int main()
{
	while(1)
	{
		for(char ii = 0; ii < 9; ++ii)
		{
			IOWR(RGBS_BASE,0,ii);
			usleep(500000);
		}
	}
}
