#include <Adafruit_Fingerprint.h>
const int redLed =10;
const int greenLed =7;

#include <LiquidCrystal.h>
#include<SoftwareSerial.h>
#include <Wire.h>
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 11, en = 12, d4 = 2, d5 = 3, d6 = 4, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
// uncomment this line:
// #define mySerial Serial1

// For UNO and others without hardware serial, we must use software serial...
// pin #2 is IN from sens+or (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
// comment these two lines if using hardware serial
SoftwareSerial myFinger(5,6);
//SoftwareSerial mySerial(7,10);

#include <Servo.h>
int x =0;

Servo myservo;
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&myFinger);

void setup(){
  lcd.begin(16, 2);
  pinMode(redLed,OUTPUT);
  pinMode(greenLed,OUTPUT);
 
  myservo.attach(9);
   Wire.begin(10);  // Join I2C bus with address 0x10
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  

  // mySerial.begin(9600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");

  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  Serial.println("Waiting for valid finger...");
  lcd.print("SMART ");
  
 
}




void loop()                     // run over and over again
{
  myservo.write(180);
  getFingerprintID();
}


uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
          Serial.println("No finger detected");
          digitalWrite(redLed,LOW);
          digitalWrite(greenLed,HIGH);
         
          lcd.clear();
          lcd.print("WELCOME Mr.Vivek");
          lcd.setCursor(0, 1);
          lcd.print("DOOR CLOSE...");
  
          delay(3000);
      return p;
    
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
     
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Finger Print");
     lcd.setCursor(0,1);
     lcd.print("Matched!....OOK");
    delay(3000);
     digitalWrite(redLed,HIGH);
 digitalWrite(greenLed,LOW);
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } 
  else {
    Serial.println("Unknown error");
         lcd.clear();
         lcd.setCursor(0,0);
      lcd.print("Finger Print");
     lcd.setCursor(0,1);
      lcd.print("Invalid!...");
      delay(3000);
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  String str="WELCOME Mr.Deepak";
  if(finger.fingerID==9)
  str="WELCOME Mr.DEEPAK"; 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
 myservo.write(90);
 digitalWrite(redLed,HIGH);
 digitalWrite(greenLed,LOW);

  lcd.clear();
  lcd.print(str);
  lcd.setCursor(0, 1);
  lcd.print("DOOR OPENING...");
  
  delay(3000);
  //lcd.clear();
  return finger.fingerID;
  
}


// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  if(finger.fingerID==1)
  {
    Serial.print("Hello");
  }
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
 myservo.write(180);
 digitalWrite(redLed,HIGH);
 digitalWrite(greenLed,LOW);
 
  delay(3000);
  return finger.fingerID;
}

//started communication using i2c
void receiveEvent() {
  if(Wire.available()) {
    Serial.print("Incoming:");
    char c = Wire.read();
    if(c=='1')
    fun();
    Serial.println(c);
     delay(3000);
  }
}

void fun(){
 myservo.write(90);
 digitalWrite(redLed,HIGH);
 digitalWrite(greenLed,LOW);
// digitalWrite(buzerPin,HIGH);
  lcd.clear();
 lcd.print("WELCOME MR. Vivek");
  lcd.setCursor(0, 1);
  lcd.print("DOOR OPENING...");

}
