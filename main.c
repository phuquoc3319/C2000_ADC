#include "driverlib.h"
#include "device.h"

#include "adc.h"
#include "uart.h"
#include "encoder.h"
/**
 * main.c
 */
int64_t test = 0;
uint32_t adc_result = 0;
uint32_t adc_result1 = 0;
const char *c = "\r\nHello World";

int64_t EncoderPos = 0;
int16_t Direction = 0;

// Functions
void LED_Init(void);


int main(void)
{
    Device_init();
    Device_initGPIO();

    Interrupt_initModule();
    Interrupt_initVectorTable();

    Interrupt_register(INT_SCIA_RX, &sciaRXFIFOISR);

    LED_Init();
    ADC_Init();



    UARTA_Init(115200);

    Interrupt_enable(INT_SCIA_RX);

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP9);

    //
    // Enable Global Interrupt (INTM) and realtime interrupt (DBGM)
    //
    EINT;
    ERTM;

    Encoder_Init();

    while(1)
    {
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER0);
        ADC_forceSOC(ADCA_BASE, ADC_SOC_NUMBER1);
        GPIO_togglePin(31);
        test += 1;
        adc_result = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER0);
        adc_result1 = ADC_readResult(ADCARESULT_BASE, ADC_SOC_NUMBER1);

//        SCI_writeCharArray(SCIA_BASE,(uint16_t *) c, strlen(c));
        EncoderPos = EQEP_getPosition(EQEP1_BASE);
        Direction = EQEP_getDirection(EQEP1_BASE);
        DEVICE_DELAY_US(100000);
    }
}


void LED_Init(void)
{
    GPIO_setPadConfig(31, GPIO_PIN_TYPE_STD);
    GPIO_setDirectionMode(31, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(31, GPIO_CORE_CPU1);
    GPIO_setPinConfig(GPIO_31_GPIO31);

    GPIO_setDirectionMode(34, GPIO_DIR_MODE_OUT);
    GPIO_setMasterCore(34, GPIO_CORE_CPU1);
    GPIO_setPadConfig(34, GPIO_PIN_TYPE_STD);
    GPIO_setPinConfig(GPIO_34_GPIO34);
}


