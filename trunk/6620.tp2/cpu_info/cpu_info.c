#include "cpu_info.h"
#include <stdlib.h>

#define CPUID_AS_MACRO 1

struct CPUID_REGS {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
};

#ifndef CPUID_AS_MACRO
void CPUID( struct CPUID_REGS* regs  )
{
	asm( /*"movl %0, %%eax\n\t"*/
	     "cpuid\n\t"
	  /* "movl %%eax, %0\n\t" */
	     "movl %%ebx, %1\n\t"
	     "movl %%ecx, %2\n\t" 
	     "movl %%edx, %3"
	     : "=a"(regs->eax), /* outputs */
	       "=o"(regs->ebx),
	       "=o"(regs->ecx),
	       "=o"(regs->edx) 
	     : "0"(regs->eax) /* input */
	     : "%ebx", "%ecx", "%edx", "memory" /* clobbered */
	   );
}
#else

#define CPUID( regs  ) asm(/* "movl %0, %%eax\n\t"*/                            \
                              "cpuid\n\t"                                       \
                            /* "movl %%eax, %0\n\t" */                          \
                               "movl %%ebx, %1\n\t"                             \
                               "movl %%ecx, %2\n\t"                             \
                               "movl %%edx, %3"                                 \
                           : "=a"((regs)->eax), /* outputs */                     \
                             "=o"((regs)->ebx),                                   \
                             "=o"((regs)->ecx),                                   \
                             "=o"((regs)->edx)                                    \
                           : "0"((regs)->eax) /* input */                         \
                           : "%ebx", "%ecx", "%edx", "memory" /* clobbered */   \
                          )
#endif

static CPU_CACHE_INFO* cpu_cache_alloc()
{
	return (CPU_CACHE_INFO*) malloc( sizeof(CPU_CACHE_INFO) );
}

static void cpu_cache_free( CPU_CACHE_INFO* ci )
{
	CPU_CACHE_INFO* aux;
	while( ci != 0 ) {
		aux = ci;
		ci = ci->next;
		free( aux );
	}
}

static void cpu_cache_add_descriptor( CPU_CACHE_INFO** ci, unsigned char d )
{
	if( d != 0 ) {
		CPU_CACHE_INFO* cci = cpu_cache_alloc();
		cci->descriptor = d;
		cci->next = *ci;
		*ci = cci;
	}
}

static void cpu_info_fill_basic( CPU_INFO* ci )
{
	struct CPUID_REGS cr;

	cr.eax = 0;
	CPUID( &cr );
	ci->max_cpuid_func = cr.eax;
	*((unsigned int*)ci->vendor_id) = cr.ebx;
	*((unsigned int*)(ci->vendor_id+4)) = cr.edx;
	*((unsigned int*)(ci->vendor_id+8)) = cr.ecx;
	ci->vendor_id[12] = 0;
}

static void cpu_info_fill_version( CPU_INFO* ci )
{
	struct CPUID_REGS cr;

	if( ci->max_cpuid_func >= 1 ) {
		cr.eax = 1;
		CPUID( &cr );
		ci->stepping = ( cr.eax & 0x000F );
		ci->model = (( cr.eax & 0x00F0 ) >> 4 );
		ci->family = (( cr.eax & 0x0F00 ) >> 8 );
		ci->type = (( cr.eax & 0x3000 ) >> 12 );
		if( ci->model == 0xF ) {
			ci->model |= ((cr.eax & 0xF0000)>>12);
		}
		if( ci->family == 0xF ) {
			ci->family |= ((cr.eax & 0xFF00000)>>16);
		}

		ci->brand_index = (cr.ebx & 0xFF);
		ci->clflush_line_size = ((cr.ebx & 0xFF00)>>8);
		ci->apic_id = ( cr.ebx >> 24 );

		ci->features = cr.edx;
	}
}

static void cpu_info_fill_cache( CPU_INFO* ci )
{
	struct CPUID_REGS cr;
	unsigned int steps;

	if( ci->max_cpuid_func >= 2 ) {
		cr.eax = 2;
		CPUID( &cr );

		steps = ( cr.eax & 0xFF ) - 1;

		if( (cr.eax & 0x80000000) == 0 ) {
			cr.eax >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.eax & 0xFF );
			cr.eax >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.eax & 0xFF );
			cr.eax >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.eax & 0xFF );
		}
		if( (cr.ebx & 0x80000000) == 0 ) {
			cpu_cache_add_descriptor( &ci->first_entry, cr.ebx & 0xFF );
			cr.ebx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.ebx & 0xFF );
			cr.ebx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.ebx & 0xFF );
			cr.ebx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.ebx & 0xFF );
		}
		if( (cr.ecx & 0x80000000) == 0 ) {
			cpu_cache_add_descriptor( &ci->first_entry, cr.ecx & 0xFF );
			cr.ecx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.ecx & 0xFF );
			cr.ecx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.ecx & 0xFF );
			cr.ecx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.ecx & 0xFF );
		}
		if( (cr.edx & 0x80000000) == 0 ) {
			cpu_cache_add_descriptor( &ci->first_entry, cr.edx & 0xFF );
			cr.edx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.edx & 0xFF );
			cr.edx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.edx & 0xFF );
			cr.edx >>= 8;
			cpu_cache_add_descriptor( &ci->first_entry, cr.edx & 0xFF );
		}
	}
}

void cpu_info_init( CPU_INFO* ci )
{
	cpu_info_fill_basic( ci );
	cpu_info_fill_version( ci );
}
