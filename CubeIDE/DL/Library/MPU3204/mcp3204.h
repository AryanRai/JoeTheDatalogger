/*
 * This header file contains the functions necessary to communicate with external ADC model mcp3204 through the use of SPI functionality.
 * These functions use HAL functionality and assume a correct wiring and settup of a SPI bus already exists.
 *
 * CREDIT: This headerfile and associated source files were based off of library libmcp3204 by positronic57 on GitHub. https://github.com/positronic57/libmcp3204.git
 */

#ifndef MCP3204_H
#define MCP3204_H

// include
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h> //for va_list var arg functions

/** \defgroup confBits Configuration bits for the MCP3204 */
/* @{ */
#define START_BIT 0x04
#define SINGLE_ENDED 0x02
#define DIFFERENTIAL 0xFB
#define CH_0 0x00
#define CH_1 0x40
#define CH_2 0x80
#define CH_3 0xC0
/* @} */

/** \defgroup inChannels Input channels definitions */
/* @{ */
/**
 * @brief Defines the input channel mode.
 */
typedef enum inputchannelmode
{
	singleEnded = 0, /**< Defines the input channel as single ended. */
	differential     /**< Defines the input channel as differential. */
} inputChannelMode;

/**
 * @brief Defines the input channel.
 */
typedef enum inputchannel
{
	CH0 = 0, /**< Input channel 0 of ADC. */
	CH1,     /**< Input channel 1 of ADC. */
	CH2,     /**< Input channel 2 of ADC. */
	CH3,     /**< Input channel 3 of ADC. */
	CH01,    /**< Differential input CH0 = IN+, CH1 = IN- */
	CH10,    /**< Differential input CH0 = IN-, CH1 = IN+ */
	CH23,    /**< Differential input CH2 = IN+, CH3 = IN- */
	CH32     /**< Differential input CH2 = IN-, CH3 = IN+ */
} inputChannel;
/* @} */

/**
 * @brief MCP3204 is represented by this structure.
 */
typedef struct mcp3204
{
	uint16_t digitalValue;	/**< Output from the analog to digital conversion.*/
	float referenceVoltage; /**< Reference voltage applied on the ADC.*/
} MCP3204;


/**
 * @brief Starts the AD conversion process and read the digital value
 * of the analog signal from MCP3204.
 *
 * @param[in] SPI handle used for communication.
 * @param[in] GPIOx is the GPIOx used for the ADC_CS pin.
 * @param[in] GPIO_Pin is the pin number used for the ADC_CS
 * @param[in] channelMode defines the mode of the selected ADC input channel.
 * @param[in] channel selects the ACD input channel.
 * @param[in,out] ad is a pointer to the structure that represents MCP3204.
 * @param[in] errorMessage is a pointer for the buffer that contains error messages.
 *
 * @return int 0 for successfull conversion 1 in case of failure.
 */
int MCP3204_convert(SPI_HandleTypeDef *hspi, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, inputChannelMode channelMode, inputChannel channel, MCP3204 *ad,char *msg);

/**
 * @brief The function returns the result from the AD conversion.
 *
 * @param[in] ad structure that represents MCP3204.
 *
 * @return uint16_t output from the AD conversion.
 */
uint16_t MCP3204_getValue(MCP3204 ad);

/**
 * @brief The function calculates the value of the analog input.
 *
 * @param[in] ad structure that represents MCP3204.
 *
 * @return float value of the analog input.
 */
float MCP3204_analogValue(MCP3204 ad);
/* @} */

void test_LED();


#endif /* MCP3204_H */
