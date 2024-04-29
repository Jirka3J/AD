#include <stdbool.h>
#include <stm8s.h>
#include <stdio.h>
#include "main.h"
#include "milis.h"
//#include "delay.h"
#include "uart1.h"
#include "adc_helper.h"
#include "daughterboard.h"

void init(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      // taktovani MCU na 16MHz

    init_uart1();
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL14, DISABLE);
    ADC2_SchmittTriggerConfig(ADC2_SCHMITTTRIG_CHANNEL15, DISABLE);
    //clock 16/4 musi byt pod maximem adc
    ADC2_PrescalerConfig( ADC2_PRESSEL_FCPU_D4);
    ADC2_AlignConfig(ADC2_ALIGN_RIGHT);
    //nastavime multiplxer na nejakou knihovnu
    ADC2_Select_Channel(ADC2_CHANNEL_14);
    //rozběhnem adc
    ADC2_Cmd(ENABLE);
    ADC2_Startup_Wait();
}


int main(void)
{
  
    uint32_t time = 0;
    uint16_t vref,vtemp;
    init();
    while(1){
        if (milis()- time >1000){
            time = milis();
            vref = ADC_get(CHANNEL_VREF);
            vtemp = ADC_get(CHANNEL_VTEMP);
            printf("%d %d \n",vref,vtemp);
        }
    }
}

/*-------------------------------  Assert -----------------------------------*/
#include "__assert__.h"
