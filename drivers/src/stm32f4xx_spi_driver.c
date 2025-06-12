#include "stm32f407xx_spi_driver.h"



void SPI_PeriClockControl(SPI_RegDef_t *pSPIx,uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}
	else
	{

		if(pSPIx == SPI1)
		{
			SPI1_PCLK_DI();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_DI();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_DI();
		}
	}
}

void SPI_Init(SPI_Handle_t *pSPIHandle)
{
	uint32_t tempreg = 0;

	/* Config of CR1 reg*/

	/* 1. SPI_DeviceMode , 2nd bit of SPI-CR1 reg */

	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode<<2;

	/* 2.SPI_BusConfig ,15th bit of SPI-CR1reg */

	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD)
	{
		/* 15 th bit should be 0 ,ie;2 lines unidirectional mode */
		tempreg &= ~(1<<15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD)
	{
		/* 15 th bit should be 1 ,ie;one line bidirectional mode */
		tempreg |= (1<<15);
	}
	else if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
	{
		/* 15 th bit should be 0 and 10 th bit 1 */
		tempreg &= ~(1<<15);
		tempreg |= (1<<10);
	}
	/* Clock speed = fclk/16 */
	tempreg |= (pSPIHandle->SPIConfig.SPI_SclkSpeed<<3);

	/* Data frame format*/
	tempreg &= ~(pSPIHandle->SPIConfig.SPI_DFF<<11);

	/* SPI_CPOL */
	tempreg &= ~(pSPIHandle->SPIConfig.SPI_CPOL<<1);

	/* SPI_CPHASE */
	tempreg &= ~(pSPIHandle->SPIConfig.SPI_CPHA<<0);

	// /* SPI_SSM */
	// tempreg &= ~(pSPIHandle->SPIConfig.SPI_SSM<<9);

	/* Cpoy the bits in tempreg to CR1 reg */
	pSPIHandle->pSPIx->CR1 = tempreg;
}


