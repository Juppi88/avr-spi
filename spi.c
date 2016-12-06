#include <avr/io.h>
#include "spi.h"

void spi_initialize(volatile uint8_t *spi_ddr, uint8_t spi_miso, uint8_t spi_mosi, uint8_t spi_ss, uint8_t spi_sck, bool master)
{
	uint8_t master_bit = (master ? 1 : 0);
	uint8_t slave_bit = (master ? 0 : 1);

	// Disable all SPI pins.
	*spi_ddr &= ~((1 << spi_miso) | (1 << spi_mosi) | (1 << spi_ss) | (1 << spi_sck));

	// Enable pins for output. Activate MOSI for the master, MISO for the slave.
	*spi_ddr |= ((master_bit << spi_mosi) | (slave_bit << spi_miso) | (master_bit << spi_ss) | (master_bit << spi_sck));

	SPCR = ((1 << SPE) |	// Enable SPI
  			(0 << SPIE) |	// Disable SPI interrupts
  			(0 << DORD) |	// Set data order to MSB first
  			(master_bit << MSTR) |		// Enable/disable master mode
  			(0 << SPR1) | (1 << SPR0) |	// Set SPI clock rate
  			(0 << CPOL) |	// Clock polarity (SCK low when idle)
  			(0 << CPHA));	// Clock phase (leading edge sampling)

	SPSR = (1 << SPI2X);	// Double clock rate
}

uint8_t spi_sync(uint8_t data)
{
	// Load data into the buffer.
	SPDR = data;

	// Wait until the transaction is completed.
	loop_until_bit_is_set(SPSR, SPIF);

	// Return the received data.
	return SPDR;
}

void spi_write_data(const void *data, uint8_t len)
{
	const uint8_t *p = (const uint8_t *)data;

	while (len-- > 0) {
		spi_sync(*p++);
	}

}

void spi_read_data(void *buffer, uint8_t len)
{
	uint8_t *p = (uint8_t *)buffer;

	while (len-- > 0) {
		*p++ = spi_sync(SPI_ACK);
	}
}
