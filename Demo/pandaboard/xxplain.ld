/* Created by Dag Ågren, Åbo Akademi University - Dept. of Information Technologies */

ENTRY(Vector_Init);

SECTIONS
{

    __ld_Vectors_Size = 16 * 4;   /* Vectors at the very beginning of the memory (rounded up to 16) */
    __ld_Init_Addr = 0x80800000;     /* Qemu starts execution at this address */
    __ld_Svc_Stack_Size = 0x1000; /* Very generous size of the Supervisor mode's stack (4 kB) */
    __ld_Irq_Stack_size = 0x1000; /* Very generous size of the IRQ mode's stack (4 kB) */
    __ld_Ram_size = 128M;         /* Total capacity of RAM */


    . = __ld_Vectors_Size;        /* Move the pointer after the "reserved" area for exception vectors */
    . = ALIGN(16);                /* Align it to a multiple of 16; just in case... */

    . = . + __ld_Svc_Stack_Size;  /* Allocate memory for Supervisor mode's stack */
    svc_stack_top = .;            /* Initial stack pointer for the Supervisor mode */

    . = . + __ld_Irq_Stack_size; /* Allocate memory for IRQ mode's stack */
    irq_stack_top = .;           /* Initial stack pointer for the IRQ mode */

    /* Approx. 50 kB remains for the System mode's stack: */
    . = __ld_Init_Addr - 4;      /* Allocate memory for System mode's stack */
    stack_top = .;               /* It starts just in front of the startup address */


    . = __ld_Init_Addr;          /* uboot will boot from this address */

    .init :
    {
        *(.init)                 /* ARM exception vectors must be placed to startup address */
    }
    
    .text :
    {
        _text = .;
        __isr_vector_start = .;
        *(.isr_vector)
        __isr_vector_end = .;
        *(.text*)
        *(.rodata*)
        _etext = .;
    }
    
    .data : /*AT(ADDR(.text) + SIZEOF(.text))*/
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    }
    
    .bss :
    {
        _bss = .;
        __bss_begin = .;
        *(.bss)
        _ebss = .;
        __bss_end = .;
    }
}

