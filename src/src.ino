#include "RS485.h"

RS485 Sensor;

SerialPIO mySerial(10, 11);//TX, RX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(2000);
  Serial.println("Modbus sample code");
  Sensor.init(mySerial, 7);
  //Sensor.write(ULTRASONIC, BAUDRATECONFIG, 0x03); //9600bps(Default)
}

void loop() {
  Sensor.request(ULTRASONIC, CALCULATED);
  while (1)
  {
    if (Sensor.read() != -1)
    {
      Serial.print(Sensor.dist); Serial.println("mm");
      Sensor.request(ULTRASONIC, CALCULATED);
      Serial.println("requested");
    }
    delay(100);//CALCULATEDモードの場合、ここが10msだとフリーズします。
  }
}
