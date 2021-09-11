/*! @file : sensor_de_luz.c
 * @author  Luis Carlos Nigrinis Alvarez
 * @version 1.0.0
 * @date    10/09/2021
 * @brief   Driver para 
 * @details
 *
*/
/*******************************************************************************
 * Includes
 ******************************************************************************/
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


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/
/*
 * @brief iniciar sensor de luz
 */

void sensordeluziniciarcaptura(void);

/*
 * @brief esperar resultados
 */
void sensordeluzesperarresultado(void);

/*
 * @brief obtener resultado.
 */

/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 
void sensordeluziniciarcaptura(void){
	ADC16_SetChannelConfig(SENSOR_DE_LUZ_ADC16_BASE, SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP, &ADC0_channelsConfig[0]);
}

void sensordeluzesperarresultado(void){
	while (0U == (kADC16_ChannelConversionDoneFlag &
	                      ADC16_GetChannelStatusFlags(SENSOR_DE_LUZ_ADC16_BASE, SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP)))
	        {
	        }

}


uint32_t sensordeluzobtenerdatoADC(void){
	uint32_t resultadoADC;

	sensordeluziniciarcaptura();
	sensordeluzesperarresultado();
	resultadoADC = ADC16_GetChannelConversionValue(SENSOR_DE_LUZ_ADC16_BASE, SENSOR_DE_LUZ_ADC16_CHANNEL_GROUP);

	return(resultadoADC);
}
