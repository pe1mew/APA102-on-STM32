/*
 * \file myspi.h
 *
 * \author Remko Welling, 541858
 *          remko@rfsee.nl
 *
 *  This driver is initially configured for using SPI1 on a STM32F429I-Discovery
 *  SPI		GPIO
 *  ======================
 *  SCK		PE2
 *  MOSI	PE6
 *
 *	\version 0.8	Initial release for the HACOX project team for code review
 *	                This version is using the following hardware configuration:
 *	                SPI interface: SPI1
 *	                SCK: 	GPIOE, GPIO_Pin_2
 *	                MOSI: 	GPIOE, GPIO_Pin_6
 *
 *
 *
 */

#ifndef MYSPI_H_
#define MYSPI_H_

#include <stdint.h>


class myspi
{
public:
	/// \brief initialize SPI interface.
	myspi();
	virtual ~myspi();

	/// \brief send rawm8 bit data over SPI interface.
	/// \param 8 bit uint8_t raw data
	void 	sendRaw(uint8_t data);

};

#endif /* MYSPI_H_ */
