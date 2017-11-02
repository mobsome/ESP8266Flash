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

#ifndef EspWriteParcel_h
#define EspWriteParcel_h

#include "Parcel.h"
#include <cstdint>

namespace esp8266 {
/**
 * Parcel for storing data in flash
 */
class WriteParcel : public Parcel
{
public:
  /**
   * WriteParcel
   * @param a_data parcel data
   * @param a_size parcel data size
   */
  WriteParcel(uint8_t* a_data, uint16_t a_size)
    : Parcel(a_data, a_size)
  {}

  /**
   * Writes data of provided type to flash
   * @param value object to be stored
   * @return writing result
   */
  template<class T>
  bool write_any(const T& value)
  {
    const uint8_t* p = (const uint8_t*)(const void*)&value;
    return write_next(p, sizeof(value));
  }

  /**
   * Writes string of provided length to flash
   * @param str string to be stored
   * @param length length of string to be stored
   * @return writing result
   */
  bool write_str(const char* str, uint16_t length);

  /**
   * Returns whether data have been modified
   * @return whether data have been modified
   */
  bool is_dirty() { return dirty; }

private:
  bool write_next(const uint8_t* value, uint16_t data_size);
  bool dirty;
};
} // namespace esp8266

#endif
