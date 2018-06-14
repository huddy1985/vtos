/*
 *  (C) Copyright 2010,2011
 *  NVIDIA Corporation <www.nvidia.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _UART_H_
#define _UART_H_

#include <clock.h>

/* UART registers */
struct uart_ctlr {
	unsigned int uart_thr_dlab_0;		/* UART_THR_DLAB_0_0, offset 00 */
	unsigned int uart_ier_dlab_0;		/* UART_IER_DLAB_0_0, offset 04 */
	unsigned int uart_iir_fcr;		/* UART_IIR_FCR_0, offset 08 */
	unsigned int uart_lcr;			/* UART_LCR_0, offset 0C */
	unsigned int uart_mcr;			/* UART_MCR_0, offset 10 */
	unsigned int uart_lsr;			/* UART_LSR_0, offset 14 */
	unsigned int uart_msr;			/* UART_MSR_0, offset 18 */
	unsigned int uart_spr;			/* UART_SPR_0, offset 1C */
	unsigned int uart_irda_csr;		/* UART_IRDA_CSR_0, offset 20 */
	unsigned int uart_reserved[6];		/* Reserved, unused, offset 24-38*/
	unsigned int uart_asr;			/* UART_ASR_0, offset 3C */
};

#define NVRM_PLLP_FIXED_FREQ_KHZ	216000
#define NV_DEFAULT_DEBUG_BAUD		115200

#define UART_FCR_FIFO_EN	0x01 /* Fifo enable */
#define UART_FCR_CLEAR_RCVR	0x02 /* Clear the RCVR FIFO */
#define UART_FCR_CLEAR_XMIT	0x04 /* Clear the XMIT FIFO */
#define UART_FCR_DMA_SELECT	0x08 /* For DMA applications */
#define UART_FCR_TRIGGER_MASK	0xC0 /* Mask for the FIFO trigger range */
#define UART_FCR_TRIGGER_1	0x00 /* Mask for trigger set at 1 */
#define UART_FCR_TRIGGER_3	0x30	/* Mask for trigger set at 3 */
#define UART_FCR_TRIGGER_4	0x40 /* Mask for trigger set at 4 */
#define UART_FCR_TRIGGER_8	0x80 /* Mask for trigger set at 8 */
#define UART_FCR_TRIGGER_14	0xC0 /* Mask for trigger set at 14 */

#define UART_FCR_RXSR		0x02 /* Receiver soft reset */
#define UART_FCR_TXSR		0x04 /* Transmitter soft reset */

/*
 * These are the definitions for the Modem Control Register
 */
#define UART_MCR_DTR	0x01		/* DTR   */
#define UART_MCR_RTS	0x02		/* RTS   */
#define UART_MCR_OUT1	0x04		/* Out 1 */
#define UART_MCR_OUT2	0x08		/* Out 2 */
#define UART_MCR_LOOP	0x10		/* Enable loopback test mode */
#define UART_MCR_AFE	0x20		/* Enable auto-RTS/CTS */

#define UART_MCR_DMA_EN	0x04
#define UART_MCR_TX_DFR	0x08

/*
 * These are the definitions for the Line Control Register
 *
 * Note: if the word length is 5 bits (UART_LCR_WLEN5), then setting
 * UART_LCR_STOP will select 1.5 stop bits, not 2 stop bits.
 */
#define UART_LCR_WLS_MSK 0x03		/* character length select mask */
#define UART_LCR_WLS_5	0x00		/* 5 bit character length */
#define UART_LCR_WLS_6	0x01		/* 6 bit character length */
#define UART_LCR_WLS_7	0x02		/* 7 bit character length */
#define UART_LCR_WLS_8	0x03		/* 8 bit character length */
#define UART_LCR_STB	0x04		/* # stop Bits, off=1, on=1.5 or 2) */
#define UART_LCR_PEN	0x08		/* Parity eneble */
#define UART_LCR_EPS	0x10		/* Even Parity Select */
#define UART_LCR_STKP	0x20		/* Stick Parity */
#define UART_LCR_SBRK	0x40		/* Set Break */
#define UART_LCR_BKSE	0x80		/* Bank select enable */
#define UART_LCR_DLAB	0x80		/* Divisor latch access bit */

/*
 * These are the definitions for the Line Status Register
 */
#define UART_LSR_DR	0x01		/* Data ready */
#define UART_LSR_OE	0x02		/* Overrun */
#define UART_LSR_PE	0x04		/* Parity error */
#define UART_LSR_FE	0x08		/* Framing error */
#define UART_LSR_BI	0x10		/* Break */
#define UART_LSR_THRE	0x20		/* Xmit holding register empty */
#define UART_LSR_TEMT	0x40		/* Xmitter empty */
#define UART_LSR_ERR	0x80		/* Error */

#define UART_MSR_DCD	0x80		/* Data Carrier Detect */
#define UART_MSR_RI	0x40		/* Ring Indicator */
#define UART_MSR_DSR	0x20		/* Data Set Ready */
#define UART_MSR_CTS	0x10		/* Clear to Send */
#define UART_MSR_DDCD	0x08		/* Delta DCD */
#define UART_MSR_TERI	0x04		/* Trailing edge ring indicator */
#define UART_MSR_DDSR	0x02		/* Delta DSR */
#define UART_MSR_DCTS	0x01		/* Delta CTS */

/*
 * These are the definitions for the Interrupt Identification Register
 */
#define UART_IIR_NO_INT	0x01	/* No interrupts pending */
#define UART_IIR_ID	0x06	/* Mask for the interrupt ID */

#define UART_IIR_MSI	0x00	/* Modem status interrupt */
#define UART_IIR_THRI	0x02	/* Transmitter holding register empty */
#define UART_IIR_RDI	0x04	/* Receiver data interrupt */
#define UART_IIR_RLSI	0x06	/* Receiver line status interrupt */

/*
 * These are the definitions for the Interrupt Enable Register
 */
#define UART_IER_MSI	0x08	/* Enable Modem status interrupt */
#define UART_IER_RLSI	0x04	/* Enable receiver line status interrupt */
#define UART_IER_THRI	0x02	/* Enable Transmitter holding register int. */
#define UART_IER_RDI	0x01	/* Enable receiver data interrupt */

/* useful defaults for LCR */
#define UART_LCR_8N1	0x03

/* whole of uart init operations */
int init_uart(void);

/* third step: enabling internal loopback */
int enable_loopback(void);

/*
 * forth step:
 * 16450: set fcr[0] -> 0
 * 16550: set fcr[0] -> 1
 */
int fifo_transfer(int enable);

/* fifth step: enable interrupt for uart */
int enable_interrupt(void);

/* sixth step: write data into the thr register */
int write2uart(const char *data);

/* seventh step: wait for THR interrupt if enabled the interrupt */
int wait4int(void);

/* eighth step: monitoring recv interrupt for read. uart callback */

/* ninth step: read data from uart buffer */
char *read4uart(int which);

#endif	/* UART_H */

