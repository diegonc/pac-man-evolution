#include "cpu_info.h"
#include <stdlib.h>
#include <stdio.h>

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

typedef struct {
	unsigned char id;
	char* desc;
} CC_HR_INFO;

#define CPU_CACHE_DESCRIPTOR_TABLE_SIZE	70
static CC_HR_INFO descriptor_table[CPU_CACHE_DESCRIPTOR_TABLE_SIZE];

static void cpu_cache_init_table()
{
	descriptor_table[1-1].id = 0x00;
	descriptor_table[1-1].desc = "Null";
	descriptor_table[2-1].id = 0x01;
	descriptor_table[2-1].desc = "Instruction TLB: 4 KB Pages, 4-way set associative, 32 entries";
	descriptor_table[3-1].id = 0x02;
	descriptor_table[3-1].desc = "Instruction TLB: 4 MB Pages, fully associative, 2 entries";
	descriptor_table[4-1].id = 0x03;
	descriptor_table[4-1].desc = "Data TLB: 4 KB Pages, 4-way set associative, 64 entries";
	descriptor_table[5-1].id = 0x04;
	descriptor_table[5-1].desc = "Data TLB: 4 MB Pages, 4-way set associative, 8 entries";
	descriptor_table[6-1].id = 0x05;
	descriptor_table[6-1].desc = "Data TLB: 4 MB Pages, 4-way set associative, 32 entries";
	descriptor_table[7-1].id = 0x06;
	descriptor_table[7-1].desc = "1st-level instruction cache: 8 KB, 4-way set associative, 32-byte line size";
	descriptor_table[8-1].id = 0x08;
	descriptor_table[8-1].desc = "1st-level instruction cache: 16 KB, 4-way set associative, 32-byte line size";
	descriptor_table[9-1].id = 0x0A;
	descriptor_table[9-1].desc = "1st-level data cache: 8 KB, 2-way set associative, 32-byte line size";
	descriptor_table[10-1].id = 0x0C;
	descriptor_table[10-1].desc = "1st-level data cache: 16 KB, 4-way set associative, 32-byte line size";
	descriptor_table[11-1].id = 0x22;
	descriptor_table[11-1].desc = "3rd-level cache: 512 KB, 4-way set associative, sectored cache, 64-byte line size";
	descriptor_table[12-1].id = 0x23;
	descriptor_table[12-1].desc = "3rd-level cache: 1 MB, 8-way set associative, sectored cache, 64-byte line size";
	descriptor_table[13-1].id = 0x25;
	descriptor_table[13-1].desc = "3rd-level cache: 2 MB, 8-way set associative, sectored cache, 64-byte line size";
	descriptor_table[14-1].id = 0x29;
	descriptor_table[14-1].desc = "3rd-level cache: 4 MB, 8-way set associative, sectored cache, 64-byte line size";
	descriptor_table[15-1].id = 0x2C;
	descriptor_table[15-1].desc = "1st-level data cache: 32 KB, 8-way set associative, 64-byte line size";
	descriptor_table[16-1].id = 0x30;
	descriptor_table[16-1].desc = "1st-level instruction cache: 32 KB, 8-way set associative, 64-byte line size";
	descriptor_table[17-1].id = 0x39;
	descriptor_table[17-1].desc = "2nd-level cache: 128 KB, 4-way set associative, sectored cache, 64-byte line size";
	descriptor_table[18-1].id = 0x3A;
	descriptor_table[18-1].desc = "2nd-level cache: 192 KB, 6-way set associative, sectored cache, 64-byte line size";
	descriptor_table[19-1].id = 0x3B;
	descriptor_table[19-1].desc = "2nd-level cache: 128 KB, 2-way set associative, sectored cache, 64-byte line size";
	descriptor_table[20-1].id = 0x3C;
	descriptor_table[20-1].desc = "2nd-level cache: 256 KB, 4-way set associative, sectored cache, 64-byte line size";
	descriptor_table[21-1].id = 0x3D;
	descriptor_table[21-1].desc = "2nd-level cache: 384 KB, 6-way set associative, sectored cache, 64-byte line size";
	descriptor_table[22-1].id = 0x3E;
	descriptor_table[22-1].desc = "2nd-level cache: 512 KB, 4-way set associative, sectored cache, 64-byte line size";
	descriptor_table[23-1].id = 0x40;
	descriptor_table[23-1].desc = "No 2nd-level cache or, if processor contains a valid 2nd-level cache, no 3rd-level cache";
	descriptor_table[24-1].id = 0x41;
	descriptor_table[24-1].desc = "2nd-level cache: 128 KB, 4-way set associative, 32-byte line size";
	descriptor_table[25-1].id = 0x42;
	descriptor_table[25-1].desc = "2nd-level cache: 256 KB, 4-way set associative, 32-byte line size";
	descriptor_table[26-1].id = 0x43;
	descriptor_table[26-1].desc = "2nd-level cache: 512 KB, 4-way set associative, 32-byte line size";
	descriptor_table[27-1].id = 0x44;
	descriptor_table[27-1].desc = "2nd-level cache: 1 MB, 4-way set associative, 32-byte line size";
	descriptor_table[28-1].id = 0x45;
	descriptor_table[28-1].desc = "2nd-level cache: 2 MB, 4-way set associative, 32-byte line size";
	descriptor_table[29-1].id = 0x46;
	descriptor_table[29-1].desc = "3rd-level cache: 4 MB, 4-way set associative, 64-byte line size";
	descriptor_table[30-1].id = 0x47;
	descriptor_table[30-1].desc = "3rd-level cache: 8 MB, 8-way set associative, 64-byte line size";
	descriptor_table[31-1].id = 0x49;
	descriptor_table[31-1].desc = "3rd-level cache: 4 MB, 16-way set associative, 64-byte line size (Intel Xeon processor MP,Family F, Model 6) 2nd-level cache: 4 MB, 16-way set associative, 64-byte line size";
	descriptor_table[32-1].id = 0x4A;
	descriptor_table[32-1].desc = "3rd-level cache: 6 MB, 12-way set associative, 64-byte line size";
	descriptor_table[33-1].id = 0x4B;
	descriptor_table[33-1].desc = "3rd-level cache: 8 MB, 16-way set associative, 64-byte line size";
	descriptor_table[34-1].id = 0x4C;
	descriptor_table[34-1].desc = "3rd-level cache: 12 MB, 12-way set associative, 64-byte line size";
	descriptor_table[35-1].id = 0x4D;
	descriptor_table[35-1].desc = "3rd-level cache: 16 MB, 16-way set associative, 64-byte line size";
	descriptor_table[36-1].id = 0x50;
	descriptor_table[36-1].desc = "Instruction TLB: 4 KB, 2 MB or 4 MB pages, fully associative, 64 entries";
	descriptor_table[37-1].id = 0x51;
	descriptor_table[37-1].desc = "Instruction TLB: 4 KB, 2 MB or 4 MB pages, fully associative, 128 entries";
	descriptor_table[38-1].id = 0x52;
	descriptor_table[38-1].desc = "Instruction TLB: 4 KB, 2 MB or 4 MB pages, fully associative, 256 entries";
	descriptor_table[39-1].id = 0x56;
	descriptor_table[39-1].desc = "L0 Data TLB: 4 MB pages, 4-way set associative, 16 entries";
	descriptor_table[40-1].id = 0x57;
	descriptor_table[40-1].desc = "L0 Data TLB: 4 MB pages, 4-way set associative, 16 entries";
	descriptor_table[41-1].id = 0x5B;
	descriptor_table[41-1].desc = "Data TLB: 4 KB or 4 MB pages, fully associative, 64 entries";
	descriptor_table[42-1].id = 0x5C;
	descriptor_table[42-1].desc = "Data TLB: 4 KB or 4 MB pages, fully associative, 128 entries";
	descriptor_table[43-1].id = 0x5D;
	descriptor_table[43-1].desc = "Data TLB: 4 KB or 4 MB pages, fully associative, 256 entries";
	descriptor_table[44-1].id = 0x60;
	descriptor_table[44-1].desc = "1st-level data cache: 16 KB, 8-way set associative, sectored cache, 64-byte line size";
	descriptor_table[45-1].id = 0x66;
	descriptor_table[45-1].desc = "1st-level data cache: 8 KB, 4-way set associative, sectored cache, 64-byte line size";
	descriptor_table[46-1].id = 0x67;
	descriptor_table[46-1].desc = "1st-level data cache: 16 KB, 4-way set associative, sectored cache, 64-byte line size";
	descriptor_table[47-1].id = 0x68;
	descriptor_table[47-1].desc = "1st-level data cache: 32 KB, 4 way set associative, sectored cache, 64-byte line size";
	descriptor_table[48-1].id = 0x70;
	descriptor_table[48-1].desc = "Trace cache: 12 K-uops, 8-way set associative";
	descriptor_table[49-1].id = 0x71;
	descriptor_table[49-1].desc = "Trace cache: 16 K-uops, 8-way set associative";
	descriptor_table[50-1].id = 0x72;
	descriptor_table[50-1].desc = "Trace cache: 32 K-uops, 8-way set associative";
	descriptor_table[51-1].id = 0x73;
	descriptor_table[51-1].desc = "Trace cache: 64 K-uops, 8-way set associative";
	descriptor_table[52-1].id = 0x78;
	descriptor_table[52-1].desc = "2nd-level cache: 1 MB, 4-way set associative, 64-byte line size";
	descriptor_table[53-1].id = 0x79;
	descriptor_table[53-1].desc = "2nd-level cache: 128 KB, 8-way set associative, sectored cache, 64-byte line size";
	descriptor_table[54-1].id = 0x7A;
	descriptor_table[54-1].desc = "2nd-level cache: 256 KB, 8-way set associative, sectored cache, 64-byte line size";
	descriptor_table[55-1].id = 0x7B;
	descriptor_table[55-1].desc = "2nd-level cache: 512 KB, 8-way set associative, sectored cache, 64-byte line size";
	descriptor_table[56-1].id = 0x7C;
	descriptor_table[56-1].desc = "2nd-level cache: 1 MB, 8-way set associative, sectored cache, 64-byte line size";
	descriptor_table[57-1].id = 0x7D;
	descriptor_table[57-1].desc = "2nd-level cache: 2 MB, 8-way set associative, 64-byte line size";
	descriptor_table[58-1].id = 0x7F;
	descriptor_table[58-1].desc = "2nd-level cache: 512 KB, 2-way set associative, 64-byte line size";
	descriptor_table[59-1].id = 0x82;
	descriptor_table[59-1].desc = "2nd-level cache: 256 KB, 8-way set associative, 32-byte line size";
	descriptor_table[60-1].id = 0x83;
	descriptor_table[60-1].desc = "2nd-level cache: 512 KB, 8-way set associative, 32-byte line size";
	descriptor_table[61-1].id = 0x84;
	descriptor_table[61-1].desc = "2nd-level cache: 1 MB, 8-way set associative, 32-byte line size";
	descriptor_table[62-1].id = 0x85;
	descriptor_table[62-1].desc = "2nd-level cache: 2 MB, 8-way set associative, 32-byte line size";
	descriptor_table[63-1].id = 0x86;
	descriptor_table[63-1].desc = "2nd-level cache: 512 KB, 4-way set associative, 64-byte line size";
	descriptor_table[64-1].id = 0x87;
	descriptor_table[64-1].desc = "2nd-level cache: 1 MB, 8-way set associative, 64-byte line size";
	descriptor_table[65-1].id = 0xB0;
	descriptor_table[65-1].desc = "Instruction TLB: 4 KB Pages, 4-way set associative, 128 entries";
	descriptor_table[66-1].id = 0xB1;
	descriptor_table[66-1].desc = "Instruction TLB: 4 MB Pages, 4-way set associative, 4 entries Instruction TLB: 2 MB Pages, 4-way set associative, 8 entries";
	descriptor_table[67-1].id = 0xB3;
	descriptor_table[67-1].desc = "Data TLB: 4 KB Pages, 4-way set associative, 128 entries";
	descriptor_table[68-1].id = 0xB4;
	descriptor_table[68-1].desc = "Data TLB: 4 KB Pages, 4-way set associative, 256 entries";
	descriptor_table[69-1].id = 0xF0;
	descriptor_table[69-1].desc = "64-byte Prefetching";
	descriptor_table[70-1].id = 0xF1;
	descriptor_table[70-1].desc = "128-byte Prefetching";
}

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

static void cpu_cache_print_descriptor( unsigned char d )
{
	int i;
	
	for( i=0; i < CPU_CACHE_DESCRIPTOR_TABLE_SIZE; i++ ) {
		if( descriptor_table[i].id == d ) {
			printf( "%s\n", descriptor_table[i].desc );
			break;
		}
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

void cpu_info_startup()
{
	cpu_cache_init_table();
}

void cpu_info_init( CPU_INFO* ci )
{
	cpu_info_fill_basic( ci );
	cpu_info_fill_version( ci );
	cpu_info_fill_cache( ci );
}

void cpu_info_print( CPU_INFO* ci )
{
	printf( "max_cpuid_func: %x\n", ci->max_cpuid_func );
	printf( "vendor_id: %s\n", ci->vendor_id );
	printf( "model: %i\n", ci->model );
	printf( "family: %i\n", ci->family );
	printf( "stepping: %i\n", ci->stepping );
	printf( "Cache Info:\n" );
	if( ci->first_entry ) {
		CPU_CACHE_INFO* cci = ci->first_entry;
		while( cci ) {
			printf( "\t" );
			cpu_cache_print_descriptor( cci->descriptor );
			cci = cci->next;
		}
	} else printf( "\tNo hay informacion disponible.\n" );
}

void cpu_info_free( CPU_INFO* ci )
{
	cpu_cache_free( ci->first_entry );
}
