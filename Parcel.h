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

#ifndef EspParcel_h
#define EspParcel_h

#include <cstdint>

namespace esp8266 {
/**
 * Base class for flash parcels
 */
class Parcel
{
public:
  /**
   * Parcel
   * @param a_data parcel data
   * @param a_size parcel data size
   */
  Parcel(uint8_t* a_data, uint16_t a_size)
    : data(a_data)
    , size(a_size)
  {}

  /**
   * Returns parcel data size
   * @return parcel data size
   */
  uint16_t get_size() { return carret; }

protected:
  int16_t alloc(uint16_t alloc_size)
  {
    const int16_t address = carret;
    if ((carret + alloc_size) > size) {
      return -1;
    }

    carret += alloc_size;
    return address;
  }

  uint16_t carret = 0;
  uint8_t* data;
  uint16_t size;
};
} // namespace esp8266

#endif
