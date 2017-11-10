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

#include "Flash.h"
#include "NativeFlash.h"
#include "Parcelable.h"
#include "ReadParcel.h"
#include "WriteParcel.h"
#include <cstring>

namespace esp8266 {
bool
Flash::read(Parcelable& parcelable)
{
  uint16_t length = fix_size(parcelable.get_capacity());
  if ((parcelable.get_address() > length) > NativeFlash::size()) {
    return false;
  }

  uint8_t data[length];
  if (!NativeFlash::read_flash(data, parcelable.get_address(), length)) {
    return false;
  }

  ReadParcel parcel(data, length);
  parcelable.read(parcel);
  return true;
}

bool
Flash::write(const Parcelable& parcelable)
{
  uint16_t length = fix_size(parcelable.get_capacity());
  if ((parcelable.get_address() > length) > NativeFlash::size()) {
    return false;
  }

  uint8_t data[length];
  if (!NativeFlash::read_flash(data, parcelable.get_address(), length)) {
    return false;
  }

  WriteParcel parcel(data, length);
  parcelable.write(parcel);
  if (parcel.is_dirty() &&
      !NativeFlash::write_flash(data, parcelable.get_address(), length)) {
    return false;
  }
  return true;
}

bool
Flash::clear(const Parcelable& parcelable)
{
  return clear(parcelable.get_address(), parcelable.get_capacity());
}

bool
Flash::clear(uint16_t start, uint16_t length)
{
  if (start >= total_size()) {
    return false;
  }

  NativeFlash::Sector sector;
  NativeFlash::get_sector(start, length, sector);
  uint8_t data[sector.length];

  if (sector.data_offset != 0 || sector.length != sector.data_length) {
    NativeFlash::read_flash(data, sector.start, sector.length);
  }
  
  std::memset(data + sector.data_offset, 0, sector.data_length);
  return NativeFlash::write_flash(data, sector.start, sector.length);
}

uint16_t
Flash::total_size()
{
  return NativeFlash::size();
}

uint16_t
Flash::fix_size(uint16_t buffer_size)
{
  return (buffer_size + 3) & (~3);
}
}
