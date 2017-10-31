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

#ifndef EspParcelable_h
#define EspParcelable_h

namespace esp8266 {
class ReadParcel;
class WriteParcel;
/**
 * Interface for classes that will store its data to flash
 */
class Parcelable
{
public:
  /**
   * ~Parcelable
   */
  virtual ~Parcelable() = 0;

  /**
   * Unique identifier for this parcelable.
   * Must be constant and unique across all parcelables.
   *
   * @return unique identifier
   */
  virtual uint8_t get_id() = 0;

  /**
   * Reads data stored in provided parcel. Data must be read in the same
   * order as written in write() method
   */
  virtual void read(const ReadParcel& parcel) = 0;

  /**
   * Writes data to provided parcel
   */
  virtual void write(WriteParcel& parcel) = 0;
};
}

#endif
