/* Created by Dag Ågren, Åbo Akademi University - Dept. of Information Technologies */

ENTRY(Vector_Init);

MEMORY
{
	ram (rwx) : ORIGIN = 0x80800000, LENGTH = 128M
}

PROVIDE(__stack = 0x80700000);

SECTIONS
{
    .text :
    {
        _text = .;
        __isr_vector_start = .;
        *(.isr_vector)
        __isr_vector_end = .;
        *(.text*)
        *(.rodata*)
        _etext = .;
    } > ram
    .data : /*AT(ADDR(.text) + SIZEOF(.text))*/
    {
        _data = .;
        *(vtable)
        *(.data*)
        _edata = .;
    } > ram
    .bss :
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > ram
}

