#ifndef __CPU_INFO_H__
#define __CPU_INFO_H__

typedef struct __CPU_CACHE_INFO {
	unsigned char descriptor;
	struct __CPU_CACHE_INFO* next;
} CPU_CACHE_INFO;

typedef struct __CPU_INFO {
	/* Basic information. */
	unsigned int  max_cpuid_func;
	char          vendor_id[13];
	/* Version information. */
	unsigned int  family;
	unsigned int  model;
	unsigned char stepping;
	unsigned char type;
	unsigned char brand_index;
	/* Feature information. */
	unsigned int  features; /* bit map */
	/* Other info.*/
	unsigned char clflush_line_size; /* unidades de 8 bytes */
	unsigned char apic_id;
	/* Cache info. */
	CPU_CACHE_INFO* first_entry;
} CPU_INFO;

void cpu_info_init( CPU_INFO* ci );

#endif /* __CPU_INFO_H__ */
