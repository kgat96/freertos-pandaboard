/* Standard includes. */
#include <stdlib.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"

#include "mux.h"

void do_set_mux(u32 base, struct pad_conf_entry const *array, int size)
{
    int i;
    struct pad_conf_entry *pad = (struct pad_conf_entry *) array;

    for (i = 0; i < size; i++, pad++)
        writew(pad->val, base + pad->offset);
}


void set_muxconf_regs_non_essential(void)
{
    do_set_mux((*ctrl)->control_padconf_core_base,
            core_padconf_array_non_essential,
            sizeof(core_padconf_array_non_essential)
                    / sizeof(struct pad_conf_entry));

    do_set_mux((*ctrl)->control_padconf_core_base,
            core_padconf_array_non_essential_4460,
            sizeof(core_padconf_array_non_essential_4460)
                    / sizeof(struct pad_conf_entry));

    do_set_mux((*ctrl)->control_padconf_wkup_base,
            wkup_padconf_array_non_essential,
            sizeof(wkup_padconf_array_non_essential)
                    / sizeof(struct pad_conf_entry));

}


void kputc(char c)
{
    volatile unsigned int *lsr = (unsigned int *) 0x48020014;
    volatile unsigned int *thr = (unsigned int *) 0x48020000;

    if (c == '\n') {
        while (!(*lsr & 0x20));
        *thr = '\r';
    }

    while (!(*lsr & 0x20));
    *thr = c;
}

void kputhex(unsigned int value, int digits)
{
    while (digits-- > 0) {
        unsigned int tmp = (value >> (4 * digits)) & 0xf;
        kputc(tmp > 9 ? tmp - 10 + 'a' : tmp + '0');
    }
}

void kputs(char *s)
{
    while (*s) {
        kputc(*s++);
    }
}


void mgpio_set(int en)
{
    if (en) {
        asm volatile ("nop\n\t"
                "ldr r2, =0x4000\n\t");
    } else {
        asm volatile ("nop\n\t"
                "ldr r2, =0xffffbfff\n\t");
    }

    asm volatile ("nop\n\t"
            "ldr r3, =0x4805913C\n\t"
            "str r2, [r3, #0]\n\t");

    asm volatile (
            "ldr r2, =0x48020014\n\t"
            "__mgpio_set_l2:\n\t"
            "ldr r3, [r2, #0]\n\t"
            "and.w  r3, r3, #0x20\n\t"
            "cmp r3, #0\n\t"
            "beq.n   __mgpio_set_l2\n\t"
            "mov r2, '#'\n\t"
            "ldr r3, =0x48020000\n\t"
            "str r2, [r3, #0]\n\t"
    );

}

void _init(void)
{
    kputc('#');

    {
        #define TIME_OUT 0x1fffff
        volatile u32 i;

        writel(0x0, 0x48059134);

        while(1) {
            mgpio_set(1);
            i = TIME_OUT;
            while (i--) ;

            mgpio_set(0);
            i = TIME_OUT;
            while (i--) ;

        }

    }


}


int _main(void)
{
    kputc('$');
    kputs("xxxinit\n");








    return 0;
}

