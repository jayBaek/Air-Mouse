const int RED = 5;
const int GREEN = 6;
const int YELLOW = 7;
void setup() {
 // pinMode(RED, OUTPUT);
 Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//
//      if(Serial.available()>0 || HWSERIAL.available()>0)
//      {
//        Serial.println("Receiving");
//        Serial.println(Serial.read());
//        HWSERIAL.println(HWSERIAL.read());
//        delay(1000);
//        
//      }
//      Serial.print("not available\n");
//      delay(2000);
      //Serial.write(message);
      //mySerial.write('R');
      Serial.println(Serial1.write('R'));
      delay(1000);
//      Serial.println(mySerial.write('G'));
//      delay(1000);
//      Serial.println(mySerial.write('Y'));
//      delay(1000);

      //Serial.println(mySerial.write('B'));
      //Serial.println(mySerial.write(message));
      //HWSERIAL.write(88);
      //HWSERIAL.println(HWSERIAL.write(88));
      delay(1000);
    
   
    
    //digitalWrite(RED, HIGH);
    //delay(1000);
    //digitalWrite(RED, LOW);
    //delay(1000);
    
}
