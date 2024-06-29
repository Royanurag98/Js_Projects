//upload it on arduino

#include <Wire.h>

void setup() {
  Wire.begin(10);  // Join I2C bus with address 0x10
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

void receiveEvent() {
  if(Wire.available()) {
    Serial.print("Incoming:");
    char c = Wire.read();
    Serial.println(c);
  }
}
