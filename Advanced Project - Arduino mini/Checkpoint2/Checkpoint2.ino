#include <SoftwareSerial.h>
SoftwareSerial mySerial(6,5);
void setup() {
 // pinMode(RED, OUTPUT);
 Serial.begin(9600);
 mySerial.begin(9600);
}

void loop() {

      Serial.println(mySerial.write('R'));
      delay(1000);
      Serial.println(mySerial.write('G'));
      delay(1000);
      Serial.println(mySerial.write('Y'));
      delay(1000);
    
}
