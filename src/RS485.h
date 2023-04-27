#ifndef RS485_h
#define RS485_h
#include "Arduino.h"

#define ULTRASONIC 0x01
#define CALIBRATED 0x0100
#define REALTIME 0x0101
#define ADDRESSCONFIG 0x0200
#define BAUDRATECONFIG 0x0201

class RS485
{
  public:
    void init(Stream &stream);
    void request(byte Address,unsigned short Register);
    void write(byte Address, unsigned short Register, byte value);
  private:
    Stream* _serial;
};

#endif
