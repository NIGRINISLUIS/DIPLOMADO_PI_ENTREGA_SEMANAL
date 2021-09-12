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
#include "irq_lptmr0.h"
#include "botones.h"
#include "sensor_temperatura.h"




int main(void) {

    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    //PRINTF("Hello World\r\n");
   // PRINTF("test_global_var: %d\r\n",test_global_var);
    //PRINTF("dato_float: %g\r\n",dato_float);

    LPTMR_StartTimer(LPTMR0);

    /*trabajo para entregar*/
     /*
      * 1. leer sensor de temperatura (puede ser el interno o el lm35) y hacer un printf(temperatura)
      * 2. medida de sensor de luz en unidades de lux
      * 3. la medida de temperatura y lux se imprina  temperatura solo cuando se pulsa el boton 1 y lux con el boton 2(debe imprimir en tiempo real)
      */

    /* Force the counter to be placed into memory. */
//   volatile static int i = 0 ;
    bool boton1,boton2;
   float adc_sensor_de_luz;
    float adc_sensor_de_temperatura;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    if (lptmr0_irq_counter !=0){

    			if (lptmr0_irq_counter==10){
    	            	led_off_red();
    	            	led_on_green();

    	        }
    	        if (lptmr0_irq_counter==20){
    	        		led_on_red();
    	            	led_off_green();
    	            	lptmr0_irq_counter=0;

    	        }

       //i++ ;
        //printf("i:%u\r\n",i);
    	boton1=boton1leerestado();
    	boton2=boton2leerestado();
    	if (boton1 && !boton1_presionado){
    		boton1_presionado=1;
    		adc_sensor_de_luz=sensorDeLuzObtenerDatosADC();
    		printf("sensor de luz en unidades  lux :%.4f\r\n",adc_sensor_de_luz);
    	}

    	if (!boton1){
    		boton1_presionado=0;
    	}
    	if (boton2 && !boton2_presionado){
    	    boton2_presionado=1;
    	    adc_sensor_de_temperatura=SensorDetemperaturaObtenerDatosADC();
    	    printf("Temperatura en grados centigrados  :%.4f\r\n",adc_sensor_de_temperatura);
    	}

    	if (!boton2){

    	    boton2_presionado=0;
        }
    }


    }
   return 0 ;
}
