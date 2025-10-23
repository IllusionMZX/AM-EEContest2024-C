/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "oled.h"
#include "bmp.h"

/*
 * DAC12 Reference Voltage in mV
 *  Adjust this value according to DAC12 reference settings in SysConfig
 *    Or, in registers CTL1.REFSN and CTL1.REFSP
 */
#define DAC12_REF_VOLTAGE_mV (2500)
/*
 * DAC12 static output voltage in mV
 *  Adjust output as needed and check in DAC_OUT pin
 */
unsigned int DAC12_OUTPUT_VOLTAGE_mV = 10;
uint32_t DAC_value = 0;
uint32_t Key_Value = 0;
uint32_t Key_Down = 0;
uint32_t Key_Old = 0;

int main(void)
{
    SYSCFG_DL_init();

    /* Set output voltage:
     *  DAC value (12-bits) = DesiredOutputVoltage x 4095
     *                          -----------------------
     *                              ReferenceVoltage
     */
    
    uint8_t t=' ';
    OLED_Init();		//初始化OLED
    OLED_DrawBMP(0,0,128,64,BMP1);
    delay_ms(3000);
    OLED_Clear();
    OLED_ShowChinese(0,0,0,16);
    OLED_ShowChinese(18,0,1,16);
    OLED_ShowChinese(36,0,2,16);
    OLED_ShowChinese(54,0,3,16);
    OLED_ShowChinese(72,0,4,16);
    OLED_ShowChinese(90,0,5,16);
    OLED_ShowChinese(108,0,6,16);
    OLED_ShowChinese(0,2,7,16);
    OLED_ShowChinese(18,2,8,16);
    OLED_ShowChinese(36,2,9,16);
    OLED_ShowString(60,6,(uint8_t *)"DAC",16);
    DAC_value = (DAC12_OUTPUT_VOLTAGE_mV * 4095) / DAC12_REF_VOLTAGE_mV;

    DL_DAC12_output12(DAC0, DAC_value);
    DL_DAC12_enable(DAC0);
    /* LED on by default */

    while (1) {
        
        Key_Value = DL_GPIO_readPins(GPIO_SWITCHES_USER_SWITCH_2_PORT, GPIO_SWITCHES_USER_SWITCH_2_PIN)|DL_GPIO_readPins(GPIO_SWITCHES_USER_SWITCH_1_PORT, GPIO_SWITCHES_USER_SWITCH_1_PIN);
        Key_Down = Key_Value & (Key_Old ^ Key_Value);
        Key_Old = Key_Value;
        
        if (Key_Down) {
            switch (Key_Down) {   
                case 262144:
                    DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
                    if(DAC12_OUTPUT_VOLTAGE_mV>10)
                        DAC12_OUTPUT_VOLTAGE_mV -= 20;
                    else
                        DAC12_OUTPUT_VOLTAGE_mV = DAC12_OUTPUT_VOLTAGE_mV;
                    break;
                case 2097152:
                    DL_GPIO_togglePins(GPIO_LEDS_PORT, GPIO_LEDS_USER_LED_1_PIN);
                    if(DAC12_OUTPUT_VOLTAGE_mV<2000)
                        DAC12_OUTPUT_VOLTAGE_mV += 20;
                    else
                        DAC12_OUTPUT_VOLTAGE_mV = DAC12_OUTPUT_VOLTAGE_mV;
                    break;
                default:
                    break;
            }
        }
        DAC_value = (DAC12_OUTPUT_VOLTAGE_mV * 4095) / DAC12_REF_VOLTAGE_mV;
        DL_DAC12_output12(DAC0, DAC_value);
        OLED_ShowNum(87,6,DAC12_OUTPUT_VOLTAGE_mV,4,16);
    }
}
