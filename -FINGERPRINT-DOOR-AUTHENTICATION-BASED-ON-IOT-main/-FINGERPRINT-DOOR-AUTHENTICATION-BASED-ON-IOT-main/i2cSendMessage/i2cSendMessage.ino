//upload this code to nodemcu8266 with proper connection
#include <Wire.h>
//D1 to SDA(A4)
//D2 to SCL(A5)
//gnd to gnd
//5v to input
void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  // Transmit to Arduino with address 0x10
  Wire.beginTransmission(0x10);//give same address on that you are sending
  Wire.write("Hello from NodeMCU ");
  Serial.println(".");
  Wire.endTransmission();
  delay(500);
}
