/*! @file : botones.c
 * @author  Luis Carlos Nigrinis Alvarez
 * @version 1.0.0
 * @date    11/09/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
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


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 bool boton1leerestado(){
	 uint32_t valor_pin;
	 bool resultado;

	 valor_pin=GPIO_PinRead(GPIOC, 3);
	 if(valor_pin!=0)
		 resultado=true;
	 else
		 resultado=false;

	 return(resultado);
 }

 bool boton2leerestado(){
	 uint32_t valor_pin;
		 bool resultado;

		 valor_pin=GPIO_PinRead(GPIOA, 4);
		 if(valor_pin!=0)
			 resultado=true;
		 else
			 resultado=false;

		 return(resultado);

  }
