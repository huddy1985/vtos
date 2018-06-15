#include <drivers/tx2_uart.h>

int init_uart(void)
{
    clock_enable(PERIPH_ID_UART1);
    return 0;
}
