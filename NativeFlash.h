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

#ifndef NativeFlash_h
#define NativeFlash_h

#include <cstdint>

namespace esp8266 {

/**
 * Interface for storing data directly to flash
 */
class NativeFlash
{
public:
  /**
   * Reads data from flash
   * @param data data to be read
   * @param offset address offset from the beggining of user flash
   * @param length length of data
   * @return operation result
   */
  static bool read_flash(uint8_t* data, uint16_t offset, uint16_t length);

  /**
   * Writes data to flash
   * @param data data to be stored
   * @param offset address offset from the beggining of user flash
   * @param length length of data
   * @return operation result
   */
  static bool write_flash(uint8_t* data, uint16_t offset, uint16_t length);

  /**
   * Returns size of the flash that can be used by the app
   * @return size of the flash that can be used by the app
   */
  static uint16_t size();
private:
  NativeFlash(){}
};
}
#endif // NativeFlash_h
