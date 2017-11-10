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

#ifndef EspReadParcel_h
#define EspReadParcel_h

#include "Parcel.h"
#include <cstdint>

class String;
namespace esp8266 {
/**
 * Parcel for reading data from flash
 */
class ReadParcel : public Parcel
{
public:
  /**
   * ReadParcel
   * @param a_data parcel data
   * @param a_size parcel data size
   */
  ReadParcel(uint8_t* a_data, uint16_t a_size)
    : Parcel(a_data, a_size)
  {}

  /**
   * Reads data of provided type from flash
   * @param value result object reference
   * @return reading result
   */
  template<class T>
  bool read(T& value)
  {
    uint8_t* p = (uint8_t*)(void*)&value;
    return read_next(p, sizeof(value));
  }

  /**
   * Reads boolean value
   * @param value result object reference
   * @return reading result
   */
  bool read(bool& value);

  /**
   * Reads string of provided length from flash
   * @param str string result pointer
   * @param length length of string to be read
   * @return reading result
   */
  bool read(char* str, uint16_t length);

  /**
   * Reads string of provided length from flash
   * @param str string result pointer
   * @param length length of string to be read
   * @return reading result
   */
  bool read(String& str, uint16_t length);

private:
  bool read_next(uint8_t* value, uint16_t data_size);
};
} // namespace esp8266

#endif
