int RED = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(RED, OUTPUT);


  
}
void loop() {
  // put your main code here, to run repeatedly:
  char a = Serial.read();
  if (a=='R')
  {
    Serial.println("READING");
    digitalWrite(RED, HIGH);
    delay(500);
    digitalWrite(RED, LOW);
  }

}
