/*! @file : K32L2B31A_Project.c
 * @author  Luis Carlos Nigrinis Alvarez
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
#include "irq_lptmr0.h"
#include "botones.h"
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


/*
 * @brief interrupcion por LPTMRO cada un segundo
 */



int main(void) {

	uint32_t adc_sensor_de_luz;
	bool boton1,boton2;

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
    //unsigned char cont_LR = 0;
    /* Enter an infinite loop, just incrementing a counter. */

    /* Start counting */
    LPTMR_StartTimer(LPTMR0);

    while(1) {



        if (lptmr0_irq_counter==1){
        	led_off_red();
        	//led_on_green();
          	i++ ;

        }
        if (lptmr0_irq_counter==2){
        	//led_on_red();
        	led_off_green();
        	lptmr0_irq_counter=0;
         	i++ ;
         	boton1=boton1leerestado();
         	boton2=boton2leerestado();

         	printf("Boton1 = %u\r\n",boton1);
         	printf("Boton2 = %u\r\n",boton2);

          	adc_sensor_de_luz=sensordeluzobtenerdatoADC();
          	printf("ADC sensor de luz %u\r\n",adc_sensor_de_luz);

        }



    }
    return 0 ;
}
