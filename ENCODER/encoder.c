/*
 * encoder.c
 *
 *  Created on: Jan 19, 2020
 *      Author: RICHARD
 */
#include "encoder.h"

void Encoder_Init(void)
{
    EALLOW;
    GPIO_setPinConfig(GPIO_10_EQEP1A);
    GPIO_setPadConfig(10, GPIO_PIN_TYPE_STD);
//    GPIO_setPinConfig(GPIO_51_EQEP1B);
//    GPIO_setPadConfig(51, GPIO_PIN_TYPE_STD);




    //
    // Configure the decoder for up-count mode, counting both rising and
    // falling edges (that is, 2x resolution)
    //
    EQEP_setDecoderConfig(EQEP1_BASE, (EQEP_CONFIG_2X_RESOLUTION |
                                       EQEP_CONFIG_UP_COUNT |
                                       EQEP_CONFIG_SWAP));
    EQEP_setEmulationMode(EQEP1_BASE, EQEP_EMULATIONMODE_RUNFREE);



    //
    // Configure the position counter to reset on an index event
    //
    EQEP_setPositionCounterConfig(EQEP1_BASE, EQEP_POSITION_RESET_MAX_POS,
                                  0xFFFFFFFF);


    //
    // Enable the eQEP1 module
    //
    EQEP_enableModule(EQEP1_BASE);
}


