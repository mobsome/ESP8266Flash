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

namespace esp8266 {
class Parcelable;

/**
 * Flash memory manager
 */
class Flash
{
public:
  /**
   * Reades data from flash to provided Parcelable
   * @param offset flash memory offset where data are stored
   * @param parcelable parcelable to be filled
   *                   with flash data
   */
  static bool read(uint16_t offset, Parcelable& parcelable);

  /**
   * Stores data from provided Parcelable to flash
   * @param offset flash memory offset where data should be stored
   * @param parcelable parcelable to be stored
   */
  static bool write(uint16_t offset, const Parcelable& parcelable);

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
