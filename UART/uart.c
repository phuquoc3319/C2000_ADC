/*
 * uart.c
 *
 *  Created on: Jan 18, 2020
 *      Author: RICHARD
 */
#include "uart.h"

void UARTA_Init(uint32_t Baudrate)
{
    // GPIO28 is the SCI Rx pin.
    //
    GPIO_setMasterCore(43, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_43_SCIRXDA);
    GPIO_setDirectionMode(43, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(43, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(43, GPIO_QUAL_ASYNC);

    //
    // GPIO29 is the SCI Tx pin.
    //
    GPIO_setMasterCore(42, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_42_SCITXDA);
    GPIO_setDirectionMode(42, GPIO_DIR_MODE_OUT);
    GPIO_setPadConfig(42, GPIO_PIN_TYPE_STD);
    GPIO_setQualificationMode(42, GPIO_QUAL_ASYNC);


    //
    // Note: Clocks were turned on to the SCIA peripheral
    // in the Device_init() function
    //

    //
    // 8 char bits, 1 stop bit, no parity. Baud rate is 9600.
    //
    SCI_setConfig(SCIA_BASE, DEVICE_LSPCLK_FREQ, Baudrate, (SCI_CONFIG_WLEN_8 |
                                                        SCI_CONFIG_STOP_ONE |
                                                        SCI_CONFIG_PAR_NONE));
    SCI_disableLoopback(SCIA_BASE);

    SCI_enableFIFO(SCIA_BASE);


    SCI_enableInterrupt(SCIA_BASE, SCI_INT_RXFF);
    SCI_setFIFOInterruptLevel(SCIA_BASE, SCI_FIFO_TX16, SCI_FIFO_RX1);

    SCI_performSoftwareReset(SCIA_BASE);
    //
    // Relinquish SCI from Reset
    //
    SCI_enableModule(SCIA_BASE);
    DEVICE_DELAY_US(10);
}

//
// sciaRXFIFOISR - SCIA Receive FIFO ISR
//
__interrupt void sciaRXFIFOISR(void)
{
    SCI_writeCharNonBlocking(SCIA_BASE, (uint16_t)'s');

    GPIO_togglePin(34);

    SCI_clearOverflowStatus(SCIA_BASE);

    SCI_clearInterruptStatus(SCIA_BASE, SCI_INT_RXFF);

    //
    // Issue PIE ack
    //
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

}


