/*! @file : K32L2B31A_Project.c
 * @author  Luis Carlos Niginis Alvarez
 * @version 0.0.000
 * @date    23/08/2021
 * @brief   Funcion principal main
 * @details
 *			v0.0.000	Proyecto base creado usando MCUXpresso
 *
 *
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"

#include "leds.h"
#include "sensor_de_luz.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/

/*******************************************************************************
 * External vars
 ******************************************************************************/

/*******************************************************************************
 * Local vars
 ******************************************************************************/
unsigned int test_global_var=100;
float dato_float=3.145;

/*******************************************************************************
 * Private Source Code
 ******************************************************************************/

/*
 * @brief generar bloqueo a microcontrolador por tiempo fijo
 */

void delay_block(){
	uint32_t i;
	for(i=0;i<0x100000;i++);
}

int main(void) {
	uint32_t adc_sensor_de_luz;
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    PRINTF("Hello World\r\n");
    PRINTF("test_global_var: %d\r\n",test_global_var);
    PRINTF("dato_float: %g\r\n",dato_float);
    led_on_green();

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    unsigned char cont_LR = 0;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        led_on_green();
        delay_block();
        led_off_green();
        delay_block();
        if (i % 10 == 0){
                	cont_LR++;
                	if (cont_LR % 2 == 0){
                		led_off_red();
                	}
                	else{
                		led_on_red();
                	}
                }

        adc_sensor_de_luz=sensordeluzobtenerdatoADC();
        printf("ADC sensor de luz %u\r\n",adc_sensor_de_luz);

    }
    return 0 ;
}
