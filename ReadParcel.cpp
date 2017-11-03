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

#include "ReadParcel.h"
#include <Arduino.h>
#include <cstring>

namespace esp8266 {
bool
ReadParcel::read_next(uint8_t* value, uint16_t data_size)
{
  int16_t address = alloc(data_size);
  if (address < 0) {
    return false;
  }

  memcpy(value, data + address, data_size);
  return true;
}

bool
ReadParcel::read(char* str, uint16_t length)
{
  uint8_t* p = (uint8_t*)(void*)str;
  return read_next(p, length);
}

bool
ReadParcel::read(String& str, uint16_t length)
{
  char tmp_str[length + 1];
  read(tmp_str, length + 1);
  str = String(tmp_str);
}
}
