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
#include "FlashLog.h"
#include <cstring>

using namespace ardulogger;

namespace espflash {
bool
Flash::read(Parcelable& parcelable)
{
  NativeFlash::Sector sector;
  NativeFlash::get_sector(parcelable.get_address(), parcelable.get_capacity(), sector);

  Log::d(LOG_TAG) << F("Reading flash for parcel, address=") << sector.start
                 << F(", length=") << sector.length << F("\n");
  if (!sector.length) {
    Log::e(LOG_TAG) << F("Parcel capacity exceeds flash size\n");
    return false;
  }

  uint8_t data[sector.length];
  if (!NativeFlash::read_flash(data, sector.start, sector.length)) {
    Log::e(LOG_TAG) << F("Flash reading failed\n");
    return false;
  }

  ReadParcel parcel(data + sector.data_offset, sector.data_length);
  parcelable.read(parcel);
  return true;
}

bool
Flash::write(const Parcelable& parcelable)
{
  NativeFlash::Sector sector;
  NativeFlash::get_sector(parcelable.get_address(), parcelable.get_capacity(), sector);

  Log::d(LOG_TAG) << F("Writing flash for parcel, address=") << sector.start
                 << F(", length=") << sector.length << F("\n");
  if (!sector.length) {
    Log::e(LOG_TAG) << F("Parcel capacity exceeds flash size\n");
    return false;
  }

  uint8_t data[sector.length];
  if (!NativeFlash::read_flash(data, sector.start, sector.length)) {
    Log::e(LOG_TAG) << F("Flash reading failed\n");
    return false;
  }

  WriteParcel parcel(data + sector.data_offset, sector.data_length);
  parcelable.write(parcel);
  if (parcel.is_dirty() &&
      !NativeFlash::write_flash(data, sector.start, sector.length)) {
    Log::e(LOG_TAG) << F("Flash writing failed\n");
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
  Log::d(LOG_TAG) << F("Flash clearing, address=") << start 
                 << F(", length=") << length << F("\n");
  if (start >= total_size()) {
    Log::e(LOG_TAG) << F("Clearing boundries exceeds flash size\n");
    return false;
  }

  NativeFlash::Sector sector;
  NativeFlash::get_sector(start, length, sector);
  uint8_t data[sector.length];

  if (sector.data_offset != 0 || sector.length != sector.data_length) {
    Log::d(LOG_TAG) << F("Clearing boundries fixed, reading needed\n");
    NativeFlash::read_flash(data, sector.start, sector.length);
  }

  Log::d(LOG_TAG) << F("Sector address=") << sector.start << F(", length=")
                 << sector.length << F(", offset=") << sector.data_offset
                 << F(", data_length=") << sector.data_length << F("\n");
  
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
