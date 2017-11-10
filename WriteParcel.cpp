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

#include "WriteParcel.h"
#include <Arduino.h>
#include <cstring>

namespace esp8266 {
bool
WriteParcel::write_next(const uint8_t* value, uint16_t data_size)
{
  int16_t address = alloc(data_size);
  if (address < 0) {
    return false;
  }

  if (memcmp(data + address, value, data_size)) {
    dirty = true;
    memcpy(data + address, value, data_size);
  }
  return true;
}

bool
WriteParcel::write(const char* str, uint16_t length)
{
  const uint8_t* p = (const uint8_t*)(const void*)str;
  return write_next(p, length);
}

bool
WriteParcel::write(const String& str)
{
  const uint8_t length = str.length() + 1;
  char tmp_str[length];
  str.toCharArray(tmp_str, length);
  return write(tmp_str, length);
}
}
