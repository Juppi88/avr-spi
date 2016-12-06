/*
 * AVR library for communicating over the serial peripheral interface (SPI).
 */

#ifndef __AVR_SPI_H
#define __AVR_SPI_H

#include <stdint.h>
#include <stdbool.h>

#define SPI_ACK 0x7E

// Initialize the serial peripheral interface as either master or slave.
void spi_initialize(volatile uint8_t *spi_ddr, uint8_t spi_miso, uint8_t spi_mosi, uint8_t spi_ss, uint8_t spi_sck, bool master);

// Send one byte to target device and receive another in return.
uint8_t spi_sync(uint8_t data);

// Write data to target device without reading anything.
void spi_write_data(const uint8_t *buffer, uint8_t len);

// Receive data from target device without sending anything.
void spi_read_data(uint8_t *buffer, uint8_t len);

#endif
