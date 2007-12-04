#include <stdio.h>
#include "cpu_info.h"

int main()
{
	CPU_INFO ci;

	cpu_info_init( &ci );
	printf( "max_cpuid_func: %i\n", ci.max_cpuid_func );
	printf( "vendor_id: %s\n", ci.vendor_id );

	return ci.max_cpuid_func;
}
