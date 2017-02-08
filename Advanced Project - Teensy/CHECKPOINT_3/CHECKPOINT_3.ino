const int RED = 2;
const int GREEN = 3;
const int YELLOW = 4;
void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {

//  digitalWrite(YELLOW, HIGH);
//  delay(300);
//  digitalWrite(YELLOW, LOW);
//  analogWrite(YELLOW, 50);
//  delay(1000);
//  analogWrite(YELLOW, 0);
//  
  if(Serial1.available())
  {
    char LED = Serial1.read();
    Serial.println(LED);
    if (LED == 'R')
    {
      digitalWrite(RED, HIGH);
      delay(200);
      //digitalWrite(RED, LOW);
      //continue;
    }

    else if (LED == 'G')
    {
      digitalWrite(GREEN, HIGH);
      delay(200);
      //digitalWrite(GREEN, LOW);
      //continue;
    }
    else if (LED == 'Y')
    {
      digitalWrite(YELLOW, HIGH);
      delay(200);
      //digitalWrite(YELLOW, LOW);
      //continue;
    }
    
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW); 
    }
  
 
//      Serial.println(mySerial.write('R'));
//      delay(1000);
//      Serial.println(mySerial.write('G'));
//      delay(1000);
//      Serial.println(mySerial.write('Y'));
//      delay(1000);
}
