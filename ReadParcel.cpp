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
#include "FlashLog.h"
#include <Arduino.h>
#include <cstring>

using namespace ardulogger;

namespace espflash {
bool
ReadParcel::read_next(uint8_t* value, uint16_t data_size)
{
  Log::d(LOG_TAG) << F("Reading next value of length=") << (int)data_size << F(" from parcel\n");
  int16_t address = alloc(data_size);
  if (address < 0) {
    Log::d(LOG_TAG) << F("Not enough space to read value\n");
    return false;
  }

  Log::d(LOG_TAG) << F("Data read\n");
  memcpy(value, data + address, data_size);
  return true;
}

bool
ReadParcel::read(bool& value)
{
  Log::d(LOG_TAG) << F("Reading bool value from parcel\n");
  uint8_t b_value = 0;
  if (read_next(&b_value, sizeof(uint8_t))) {
    value = b_value == 1;
    Log::d(LOG_TAG) << F("Value read from parcel='") << value << F("'\n");
  }
  return false;
}

bool
ReadParcel::read(char* str, uint16_t length)
{
  Log::d(LOG_TAG) << F("Reading char string of length") << length << F(" from parcel\n");
  uint8_t* p = (uint8_t*)(void*)str;
  const bool result = read_next(p, length);
  Log::d(LOG_TAG) << F("Read char string='") << str << F("'\n");
  return result;
}

bool
ReadParcel::read(String& str, uint16_t length)
{
  Log::d(LOG_TAG) << F("Reading string of length") << length << F("' from parcel\n");
  char tmp_str[length + 1];
  const bool result = read(tmp_str, length + 1);
  str = String(tmp_str);
  Log::d(LOG_TAG) << F("Read string='") << str << F("'\n");
  return result;
}
}
