#include "Flash.h"
#include "Parcelable.h"
#include "ReadParcel.h"
#include "WriteParcel.h"

using namespace esp8266;

class SomeData : public Parcelable
{
public:
    SomeData(const String& str, bool b, uint32_t i)
    : some_str(str)
    , some_bool(b)
    , some_int(i)
    {}
    SomeData()
    : some_str("")
    , some_bool(false)
    , some_int(0)
    {}
    
    virtual ~SomeData(){}
    
    uint16_t get_capacity() const
    {
        return 64;
    }

    uint16_t get_address() const
    {
        return 0;
    }

    void read(ReadParcel& parcel)
    {
        uint8_t length;
        parcel.read(length);
        parcel.read(some_str, length);
        parcel.read(some_bool);
        parcel.read(some_int);
    }

    void write(WriteParcel& parcel) const
    {
        const uint8_t length = some_str.length();
        parcel.write(length);
        parcel.write(some_str);
        parcel.write(some_bool);
        parcel.write(some_int);
    }

    String& get_str(){ return some_str;}
    bool get_bool(){ return some_bool;}
    uint32_t get_int(){ return some_int;}
private:
    String some_str;
    bool some_bool;
    uint32_t some_int;
};

void setup() {
  Serial.begin(9600);
  String str("Quite dummy text");
  SomeData sd(str, true, 23456);  
  // write data to flash
  Flash::write(sd);
  
  SomeData sd1;
  // Read data from flash
  Flash::read(sd1);
  
  Serial.print("String:");
  Serial.print(sd1.get_str());
  Serial.print(", Bool:");
  Serial.print(sd1.get_bool());
  Serial.print(", Int:");
  Serial.println(sd1.get_int());
}

void loop() {
  // put your main code here, to run repeatedly:

}