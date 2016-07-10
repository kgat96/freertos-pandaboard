/*
Copyright 2016, Kage Shen <kgat96@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

ENTRY(vectors_start)

SECTIONS
{
    __ld_Init_Addr = 0x80800000;   /* uboot starts execution at this address */
    __ld_Svc_Stack_Size = 0x1000;  /* Very generous size of the Supervisor mode's stack (4 kB) */
    __ld_Irq_Stack_size = 0x1000;  /* Very generous size of the IRQ mode's stack (4 kB) */
    __ld_Ram_size = 128M;          /* Total capacity of RAM */
    __ld_Ram_Addr = 0x80000000;
    
    . = __ld_Ram_Addr;

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
        __init_begin = .;
        *(.init)                 /* ARM exception vectors must be placed to startup address */
        __init_end = .;
    }

    /* The other sections follow: */
    .text :
    {
        __text_begin = .;
        *(.text)
        __text_end = .;
    }

    /* followed by other sections... */
    .rodata :
    {
        __rodata_begin = .;
        *(.rodata)
        __rodata_end = .;
    }

    .data :
    {
        __data_begin = .;
        *(.data)
        __data_end = .;
    }

    .bss :
    {
        __bss_begin = .;
        *(.bss)
        __bss_end = .;
    }
    . = ALIGN(4);                  /* The section size is aligned to the 4-byte boundary */

    /* The remainder of RAM is reserved for the heap (if malloc is ever used) */
    .heap :
    {
        __heap_begin = .;
        *(.heap)
        . = __ld_Ram_size;
        __heap_end = .;
    }
}

