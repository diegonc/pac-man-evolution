#include <stdio.h>
#include "cpu_info.h"

int main()
{
	CPU_INFO ci;

	cpu_info_startup();
	cpu_info_init( &ci );
	cpu_info_print( &ci );
	cpu_info_free( &ci );
	return 0;
}
