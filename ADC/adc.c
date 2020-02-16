/*
 * adc.c
 *
 *  Created on: Jan 17, 2020
 *      Author: RICHARD
 */
#include "adc.h"

void ADC_Init(void)
{
    ADC_setPrescaler(ADCA_BASE, ADC_CLK_DIV_1_0);

    ADC_setMode(ADCA_BASE, ADC_RESOLUTION_16BIT, ADC_MODE_DIFFERENTIAL);

    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER0, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN0, 64);
    ADC_setupSOC(ADCA_BASE, ADC_SOC_NUMBER1, ADC_TRIGGER_SW_ONLY,
                 ADC_CH_ADCIN1, 64);

    ADC_enableConverter(ADCA_BASE);
    DEVICE_DELAY_US(1000);
}

