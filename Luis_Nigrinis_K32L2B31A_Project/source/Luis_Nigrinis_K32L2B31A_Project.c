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
#include "botones.h"
#include "sensor_temperatura.h"

#include "irq_lptmr0.h"
#include "irq_lpuart0.h"

#define MENSAJE1_DEFINE "AT+CPIN\r\n"
#define COMANDOS_DISPONIBLES 2
#define SIZE_BUFFER_COMANDOS  50


char mensaje_ram[]="AT+CPIN\r\n";
const char mensaje_flash[]="AT+CPIN\r\n";
char mensaje1[]="AT+CPIN\r\n";

enum _ec25_lista_comandos_at {
	kAT= 0,
	kATI,
	kAT_CPIN,
	kAT_CREG,
	kAT_CMGF_1,
	kAT_CMGS,
	kAT_TEXT_MSG_END,
};

enum _lista_comandos_controll{
	led_verde_on = 0,
	led_verde_off,

};


const char *ec25_comandos_at[]={
		"AT",  //COMPRUEBA DISPONIBILIDAD DEL SIPOSITIVO
		"ATI",  //CONSULTA INFORMACION EL MODEN
		"AT+CPIN?",   //CONSULTA ESTADO DE LA SIMCARD
		"AT+CREG?",   //CONSULTA ESTADO DE LA RED CELULAR Y TECNOLOGIA Y TECNOLOGIA USADA EN RED CELULAR
		"AT+CMGF-1",  //SIGNA MODO TEXTO PARA ENVIAR MENSAJES
		"AT+CMGS=\"300XXXXXX\"", //ENVIA MENSAJES DE TEXTO A NUMERO DEFINIDO
		"MENSAJE", //MENSAJE & CTRL+Z
};

const char *comandos_control[] ={
		"led_verde_on",  //encender led rojo
		"led_verde_off",  //apagar led rojo

};

char buffer_nuevo_comando_recibido[50];
uint32_t index_buffer_nuevo_comando_recibido=0;

uint8_t i=0;
void LIMPIAR_BUFFER(){
	for(i=0;i<50;i++){
		buffer_nuevo_comando_recibido[i]=0x00;
	}
	index_buffer_nuevo_comando_recibido=0;
}

int main(void) {


	uint8_t nuevo_byte_lpuart0;
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif



    PRINTF(" FRDM-K32L2B3 iniciando...\r\n");


    printf("flash--- %s \r\n",mensaje_flash);
    printf("ram----%s \r\n",mensaje_ram);
    printf("define---%s \r\n",MENSAJE1_DEFINE);

    printf("define---%s \r\n",MENSAJE1_DEFINE);

    for(int i=0; i<=6 ; i++){

    	printf("%s \r\n",ec25_comandos_at[i]);
    }





    LPTMR_StartTimer(LPTMR0);




    bool boton1,boton2;
    float adc_sensor_de_luz;
    float adc_sensor_de_temperatura;
    /* Enter an infinite loop, just incrementing a counter. */



    while(1) {



    	if(NumeroDeByteDisponiblesEnBufferRx()!=0){
    		nuevo_byte_lpuart0=pullBytedesdeBuefferCircular();

    		buffer_nuevo_comando_recibido[index_buffer_nuevo_comando_recibido]=nuevo_byte_lpuart0;
    		index_buffer_nuevo_comando_recibido++;

    		char *puntero_ok;


    		if(nuevo_byte_lpuart0=='\n'){

    			for(int i=0;i<COMANDOS_DISPONIBLES;i++){

    				puntero_ok=(char*)(strstr((char*)(&buffer_nuevo_comando_recibido[0]),(char*)(comandos_control[i])));
    				if(puntero_ok!=0){
    					switch(i){
    					case led_verde_on:
    					led_on_green();
    					break;

    					case led_verde_off:
    					led_off_green();
    				    break;
    					}
    				}
    			}

    			LIMPIAR_BUFFER();

    		}
    		//printf("dato: %c, 0x%x\r\n\r\n", nuevo_byte_lpuart0);
    	}
    if (lptmr0_irq_counter !=0){

    			if (lptmr0_irq_counter==10){
    				    led_on_red();


    	        }
    			if (lptmr0_irq_counter==19){
    				printf("Temperatura en grados centigrados  :%.4f\r\n",adc_sensor_de_temperatura);
    			}
    	        if (lptmr0_irq_counter==20){
    	            	led_off_red();

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
    	if (boton2){
    	    boton2_presionado=1;
    	    adc_sensor_de_temperatura=SensorDetemperaturaObtenerDatosADC();

    	}



    		if (!boton2){

    			boton2_presionado=0;

    		}

    }


    }
   return 0 ;
}
