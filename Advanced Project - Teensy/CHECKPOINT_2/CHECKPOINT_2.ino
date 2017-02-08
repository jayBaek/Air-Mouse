int RED = 2;
int GREEN = 3;
int YELLOW = 4;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(RED, OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW, OUTPUT);


  
}
void loop() {
  // put your main code here, to run repeatedly:
  char a = Serial1.read();
  if (a=='R')
  {
    Serial.println("READING");
    digitalWrite(RED, HIGH);
    delay(500);
    digitalWrite(RED, LOW);
  }
  if (a=='G')
  {
    Serial.println("READING");
    digitalWrite(GREEN, HIGH);
    delay(500);
    digitalWrite(GREEN, LOW);
  }
  if (a=='Y')
  {
    Serial.println("READING");
    digitalWrite(YELLOW, HIGH);
    delay(500);
    digitalWrite(YELLOW, LOW);
  }
  delay(1000);
}
