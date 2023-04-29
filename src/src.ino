#include "RS485.h"

RS485 Sensor;

SerialPIO mySerial(10, 11);//TX, RX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(2000);
  Serial.println("begin");
  Sensor.init(mySerial, 7);
}

void loop() {
  Sensor.request(ULTRASONIC, REALTIME);
  Serial.println("requested");
  //Sensor.request(ULTRASONIC, REALTIME);
  //Sensor.write(ULTRASONIC, BAUDRATECONFIG, 0x03); //9600bps(Default)
  while (mySerial.available() < 7);
  delay(100);
  Serial.print("imcoming byte:"); Serial.println(mySerial.available());
  mySerial.read();
  mySerial.read();
  mySerial.read();
  long a = (mySerial.read() << 8) | mySerial.read();
  Serial.print(a); Serial.println("mm");
  mySerial.read();
  mySerial.read();
  mySerial.read();
  mySerial.read();
  mySerial.read();
  mySerial.read();
  mySerial.read();
  mySerial.read();
  delay(500);

}
