/*
 * uart.h
 *
 *  Created on: Jan 18, 2020
 *      Author: RICHARD
 */

#ifndef UART_UART_H_
#define UART_UART_H_


#include "driverlib.h"
#include "device.h"
#include "string.h"
#include "stdlib.h"

void UARTA_Init(uint32_t Baudrate);
__interrupt void sciaRXFIFOISR(void);

#endif /* UART_UART_H_ */
