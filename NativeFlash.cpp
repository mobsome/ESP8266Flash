/**************************************************************
  Copyright (c) 2017 Mobsome

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
**************************************************************/

#include <Arduino.h>
#include <cstdint>
#include "NativeFlash.h"

extern "C"
{
#include "c_types.h"
#include "spi_flash.h"
}

extern "C" uint32_t _SPIFFS_end;

namespace espflash {
static const uint32_t SECTOR =
  (((uint32_t)&_SPIFFS_end - 0x40200000) / SPI_FLASH_SEC_SIZE);

bool
NativeFlash::read_flash(uint8_t* data, uint16_t offset, uint16_t length)
{
  noInterrupts();
  const SpiFlashOpResult result =
    spi_flash_read(SECTOR * SPI_FLASH_SEC_SIZE + offset * sizeof(uint8_t),
                   reinterpret_cast<uint32_t*>(data),
                   length);
  interrupts();
  return result == SPI_FLASH_RESULT_OK;
}

bool
NativeFlash::write_flash(uint8_t* data, uint16_t offset, uint16_t length)
{
  noInterrupts();
  SpiFlashOpResult result = spi_flash_erase_sector(SECTOR);
  if (result != SPI_FLASH_RESULT_OK) {
    return false;
  }

  result =
    spi_flash_write(SECTOR * SPI_FLASH_SEC_SIZE + offset * sizeof(uint8_t),
                    reinterpret_cast<uint32_t*>(data),
                    length);
  interrupts();
  return result == SPI_FLASH_RESULT_OK;
}

void
NativeFlash::get_sector(uint16_t address, uint16_t length, Sector& sector)
{
  if (address >= size()) {
    return;
  }
  if (length <= 0) {
    return;
  }

  sector.start = shift_down(address);
  sector.length = shift_up(length);
  sector.data_offset = address - sector.start;
  sector.data_length = length;

  if ((sector.start + sector.length) > size()) {
      sector.length = size() - sector.start;
  }
  if ((sector.data_offset + length) > sector.length) {
      sector.data_length = sector.length - sector.data_offset;
  }
}

uint16_t
NativeFlash::size()
{
  return SPI_FLASH_SEC_SIZE;
}

uint16_t
NativeFlash::shift_up(uint16_t buffer_size)
{
  return (buffer_size + 3) & (~3);
}

uint16_t
NativeFlash::shift_down(uint16_t buffer_size)
{
  return buffer_size & (~3);
}
}
