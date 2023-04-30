#include "RS485.h"
#include "CRC16.h"

CRC16 CRC;

void RS485::init(Stream &stream, int CTRLpin)
{
  _serial = &stream;
  CTRL = CTRLpin;
  pinMode(CTRL, OUTPUT);
  digitalWrite(CTRL, LOW);
}

void RS485::request(byte Address, unsigned short Register)
{
  byte data[] = {Address, 0x03, highByte(Register), lowByte(Register), (byte)0, 0x01};
  unsigned short checksum = CRC.Modbus(data, 0, 6);
  digitalWrite(CTRL, HIGH);
  _serial->write(data[0]);
  _serial->write(data[1]);
  _serial->write(data[2]);
  _serial->write(data[3]);
  _serial->write(data[4]);
  _serial->write(data[5]);
  //CRC-16/MODBUS
  _serial->write(lowByte(checksum));
  _serial->write(highByte(checksum));
  //wait until transmission ends
  _serial->flush();
  digitalWrite(CTRL, LOW);
}

void RS485::write(byte Address, unsigned short Register, byte value)
{
  byte data[] = {Address, 0x06, highByte(Register), lowByte(Register), (byte)0, value};
  unsigned short checksum = CRC.Modbus(data, 0, 6);
  digitalWrite(CTRL, HIGH);
  _serial->write(data[0]);
  _serial->write(data[1]);
  _serial->write(data[2]);
  _serial->write(data[3]);
  _serial->write(data[4]);
  _serial->write(data[5]);
  //CRC-16/MODBUS
  _serial->write(lowByte(checksum));
  _serial->write(highByte(checksum));
  //wait until transmission ends
  _serial->flush();
  digitalWrite(CTRL, LOW);
}

long RS485::read()
{
  if (_serial->available() < 7)
  {
    return -1;
  }
  for (int i = 0; i < sizeof(buff); i++)
  {
    buff[i] = _serial->read();
    delayMicroseconds(10);
  }
  dist = (buff[3] << 8) | buff[4];
  return dist;
}
