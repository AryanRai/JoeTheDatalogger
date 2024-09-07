#include "mcp3204.h"
#include <stdint.h>
#include <stdio.h>
/*
 * Start the AD conversion process and read the digital value
 * of the analog signal from MCP3204.
 */
int MCP3204_convert(SPI_HandleTypeDef *hspi, GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, inputChannelMode channelMode, inputChannel channel, MCP3204 *ad,char *msg)
{
	// Cycle ADC (recommended in datasheet)
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

	unsigned char tx[3] = "";
	unsigned char rx[3] = "";

	/* set the start bit */
	tx[0] |= START_BIT;

	/* define the channel input mode */
	if (channelMode==singleEnded)
		tx[0] |= SINGLE_ENDED;
	if (channelMode==differential)
		tx[0] &= DIFFERENTIAL;

	/* set the input channel/pair */
	// Remains unchanged from original library, may require changing
	switch(channel)
	{
		case CH0:
		case CH01:
			tx[1] |= CH_0;
			break;
		case CH1:
		case CH10:
			tx[1] |= CH_1;
			break;
		case CH2:
		case CH23:
			tx[1] |= CH_2;
			break;
		case CH3:
		case CH32:
			tx[1] |= CH_3;
			break;
	}

	// transmit and receive messages tx and rx respectively
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(hspi, tx, rx, 6, 100);
	HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

	// recorded bites of importance are 4 LSB of rx[1] and all of rx[2]
	// remove 4 msb from rx[1]
	rx[1] &= 0x0F;
	uint16_t data = rx[1];
	data <<= 8;
	data |= rx[2];

	// record to adc struct
	ad->digitalValue = data;

	// bugfixing message
	sprintf(msg, "tx: %X, rx: %hX \n\r", tx[0], ad->digitalValue);

	return 0;
}

/*
 * The function returns the result from the AD conversion.
 */
uint16_t MCP3204_getValue(MCP3204 ad)
{
	return ad.digitalValue;
}

/*
 * The function calculates the value of the analog input.
 */
float MCP3204_analogValue(MCP3204 ad)
{
	return (ad.digitalValue*ad.referenceVoltage)/4096;
}

void test_LED()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
}
