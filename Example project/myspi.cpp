/*
 * \file myspi.cpp
 *
 *  Created on: Apr 27, 2016
 *      Author: Remko welling
 *      		remko@rfsee.nl
 *
 *	\version 0.8	Initial release for the HACOX project team for code review
 *
 */

#include <stdint.h>
#include "stm32f4xx_spi.h"
#include "../libraries/myspi.h"

myspi::myspi()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);

	SPI_InitTypeDef SPI_InitTypeDefStruct;

	SPI_InitTypeDefStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitTypeDefStruct.SPI_Direction = SPI_Direction_Tx; //SPI_Direction_2Lines_FullDuplex;
	SPI_InitTypeDefStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitTypeDefStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitTypeDefStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitTypeDefStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitTypeDefStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	SPI_InitTypeDefStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	//SPI_InitTypeDefStruct.SPI_CRCPolynomial = 10;

	SPI_Init(SPI4, &SPI_InitTypeDefStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);

	/*-------- Configuring SCK, MISO, MOSI --------*/

	GPIO_InitTypeDef GPIO_InitTypeDefStruct;

	GPIO_InitTypeDefStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_6;
	GPIO_InitTypeDefStruct.GPIO_Mode = GPIO_Mode_AF;;
	GPIO_InitTypeDefStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitTypeDefStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; //GPIO_PuPd_UP;
	GPIO_InitTypeDefStruct.GPIO_OType = GPIO_OType_PP;

	GPIO_Init(GPIOE, &GPIO_InitTypeDefStruct);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource2, GPIO_AF_SPI4);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_SPI4);

	SPI_Cmd(SPI4, ENABLE);
}

myspi::~myspi()
{
	// TODO Auto-generated destructor stub
}

void myspi::sendRaw(uint8_t data)
{
	while(!SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_TXE));  //transmit buffer empty?
	SPI_I2S_SendData(SPI4, data); // send 8 bits of data
	while(SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_BSY));  	//transmission ready?
}

