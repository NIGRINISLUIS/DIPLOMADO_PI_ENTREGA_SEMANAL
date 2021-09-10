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
	for(i=0;i<0x800000;i++);
}

int main(void) {
    int i = 0 ;  /* Force the counter to be placed into memory. */


    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif
    printf("Hello World\r\n");
    printf("Valor a imprimir: %d\r\n",test_global_var);
    printf("Valor tipo float: %g\r\n",dato_float);



    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        printf("%u\r\n",i);
        led_on_green();
        delay_block();
        led_off_green();
        delay_block();

    }
    return 0 ;
}
