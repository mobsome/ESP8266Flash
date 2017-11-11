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

#ifndef EspFlash_h
#define EspFlash_h

#include <cstdint>

namespace espflash {
class Parcelable;

/**
 * Flash memory manager
 */
class Flash
{
public:
  /**
   * Reades data from flash to provided Parcelable
   * @param parcelable parcelable to be filled
   *                   with flash data
   * @return reading result
   */
  static bool read(Parcelable& parcelable);

  /**
   * Stores data from provided Parcelable to flash
   * @param parcelable parcelable to be stored
   * @return storing result
   */
  static bool write(const Parcelable& parcelable);

  /**
   * Clears flash for specified parcelable
   * @param parcelable parcelable for which flash should be cleared
   * @return clearing result
   */
  static bool clear(const Parcelable& parcelable);

  /**
   * Clears specified sector of flash
   * @param start flash offset
   * @param length sector length
   * @return clearing result
   */
  static bool clear(uint16_t start, uint16_t length);

  /**
   * Returns total flash memory size
   * @return total flash memory size
   */
  static uint16_t total_size();

private:
  Flash() {}
  static uint16_t fix_size(uint16_t buffer_size);
};
}

#endif
