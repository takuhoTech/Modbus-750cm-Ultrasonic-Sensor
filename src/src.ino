#include "RS485.h"

RS485 Sensor;

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200);
  while (!Serial1);
  Sensor.init(Serial1);
}

void loop() {
  Sensor.request(ULTRASONIC,CALIBRATED);
  Sensor.request(ULTRASONIC,REALTIME);
  Sensor.write(ULTRASONIC,BAUDRATECONFIG,0x03);//9600bps(Default)

}
