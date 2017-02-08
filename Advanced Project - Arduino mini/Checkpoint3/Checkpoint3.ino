#include <SoftwareSerial.h>
SoftwareSerial mySerial(6,5);
const int RED_SWITCH = 2;
const int GREEN_SWITCH = 3;
const int YELLOW_SWITCH = 4;
void setup() {
 // pinMode(RED, OUTPUT);
 Serial.begin(9600);
 mySerial.begin(9600);
  pinMode(RED_SWITCH, INPUT_PULLUP);
  pinMode(GREEN_SWITCH, INPUT_PULLUP);
  pinMode(YELLOW_SWITCH, INPUT_PULLUP);
}

void loop() {

  int REDreading = digitalRead(RED_SWITCH);
  int YELLOWreading = digitalRead(YELLOW_SWITCH);
  int GREENreading = digitalRead(GREEN_SWITCH);
  if (REDreading == 0)
  {
    //turn RIGHT on
    Serial.println(mySerial.write('R'));
    delay(200);
  }
  if (YELLOWreading == 0 )
  {
    //turn RIGHT on
    Serial.println(mySerial.write('Y'));
    delay(200);

  }
  if (GREENreading == 0 )
  {
    //turn RIGHT on
    Serial.println(mySerial.write('G'));
    delay(200);
  }    
}
