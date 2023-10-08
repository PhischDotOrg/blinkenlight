ENTRY(Reset_Handler)

/* Stack is placed in the 64KB CCM memory */
/* NB. CCM memory cannot be accessed by peripherals or DMA! */
/* Always use static/global variables with peripherals/DMA. */
bstack = 0x10000000;
estack = bstack + 64K;

ucHeap = bstack;

/*
 * The stack is placed in the 64KB CCM memory. Please note that this memory
 * is neither DMA-capable nor accessible by peripherals!
 *
 * During startup, the main stack is placed in the region [0x10000000:0x10010000].
 * The top-of-stack pointer is located through the _estack symbol by the startup
 * assembly code in file 'startup_stm32f4xx.s'.
 *
 * The FreeRTOS Scheduler re-claims the main stack. It uses the NVIC offset
 * register to locate the address of the _estack symbol and uses the value stored
 * there to re-set the top-of-stack pointer. See the method 'prvPortStartFirstTask'
 * implemented in file 'port.c' for details.
 *
 * So in both cases, the top-of-stack is at address 0x10010000.
 *
 * FreeRTOS manages the stacks of the running tasks. It does so by using a heap
 * implementation. The implementation locates the heap through the ucHeap symbol
 * in combination with the 'configTOTAL_HEAP_SIZE' config option. In our case
 * this is set to a size of 60kB.
 *
 * Hence, the stacks of the tasks are located in the region [0x10000000-0x1000f000].
 */
MEMORY
{
	FLASH (rx)      : ORIGIN = 0x08000000, LENGTH = 1024K
	RAM (xrw)       : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
    /* Reset Vector */
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))
		. = ALIGN(4);
	} >FLASH

    .text :
	{
		. = ALIGN(4);
        stext = .;
		*(.text)
		*(.text*)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)         /* glue arm to thumb code */
		*(.glue_7t)        /* glue thumb to arm code */
		*(.eh_frame)

        . = ALIGN(4);
        _ctors_start_ = .;
        KEEP(*(.init_array));                 /* C++ constructors */
        KEEP(*(.ctors));                      /* C++ constructors */
        _ctors_end_ = .;

		. = ALIGN(4);
        etext = .;                                 /* For start-up statistics */
	} >FLASH

	_sidata = .;

	.data : AT ( _sidata )
	{
		. = ALIGN(4);
		sdata = .;
		*(.data)
		*(.data*)
		. = ALIGN(4);
		edata = .;
	} >RAM

	. = ALIGN(4);
	.bss :
	{
		sbss = .;
		__bss_start__ = sbss;
		*(.bss)
		*(.bss*)
		*(COMMON)
		. = ALIGN(4);
		ebss = .;
		__bss_end__ = ebss;
	} >RAM

	/* Remove information from the standard libraries */
	/DISCARD/ :
	{
		libc.a ( * )
		libm.a ( * )
		libgcc.a ( * )
	}

	.ARM.attributes 0 : { *(.ARM.attributes) }
}
