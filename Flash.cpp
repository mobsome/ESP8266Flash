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

namespace esp8266 {
bool
Flash::read(uint16_t offset, Parcelable& parcelable)
{
  uint16_t length = fix_size(parcelable.get_capacity());
  if ((offset > length) > NativeFlash::size()) {
    return false;
  }

  uint8_t data[length];
  if (!NativeFlash::read_flash(data, offset, length)) {
    return false;
  }

  ReadParcel parcel(data, length);
  parcelable.read(parcel);
  return true;
}

bool
Flash::write(uint16_t offset, const Parcelable& parcelable)
{
  uint16_t length = fix_size(parcelable.get_capacity());
  if ((offset > length) > NativeFlash::size()) {
    return false;
  }

  uint8_t data[length];
  if (!NativeFlash::read_flash(data, offset, length)) {
    return false;
  }

  WriteParcel parcel(data, length);
  parcelable.write(parcel);
  if (parcel.is_dirty() && !NativeFlash::write_flash(data, offset, length)) {
    return false;
  }
  return true;
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
