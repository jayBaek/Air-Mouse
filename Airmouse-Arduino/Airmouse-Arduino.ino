#include <printf.h>
#include "RF24.h"

double Vout;
double Vin;
double analogReadValue;
double ResistorDivision=0.8116; // R2/(R1+R2)
int RightButton;
int LeftButton;
double Voltage;
const int RS = A2; // Right Switch
const int LS = 3; // Left Switch

struct myData
{
  double Voltage;
  uint8_t RightButton;
  uint8_t LeftButton;
} data;

// R==1, G==2, Y==3

RF24 radio(9,10); //CEpin and CSpin
const uint64_t pipes[2] = {0xF0F0F0F0AA, 0xF0F0F0F066}; //address1, address2

void setup() { 
  //higher power means higer range
  //use the lowest power setting on the arduino size
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(3); //team number
  radio.setAutoAck(0);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1, pipes[0]);
  radio.setPayloadSize(32); //8 bytes (up to 32 bytes)
  radio.setCRCLength(RF24_CRC_8);
  radio.setRetries(0, 15);
  Serial.begin(9600);
  printf_begin();

  pinMode(RS,INPUT_PULLUP); // Right Button
  pinMode(LS,INPUT_PULLUP); // Left Button
  pinMode(A1,INPUT); // Voltage Measurer
}

void loop() 
{
  radio.stopListening();  
  analogReadValue = analogRead(A1);
  RightButton = digitalRead(RS);
  LeftButton = digitalRead(LS);
  Vout = analogReadValue*3.338/1023.00;
  Vin = Vout * (1/ResistorDivision);
  Serial.print("Vout : ");
  Serial.println(Vout);
  Serial.print("Vin : ");
  Serial.println(Vin);
  Serial.print("Right Button : ");
  Serial.println(RightButton);
  Serial.print("Left Button : ");
  Serial.println(LeftButton);
  data.Voltage = Vin;
  data.RightButton = RightButton;
  data.LeftButton = LeftButton;
  sendMessage();
  delay(50);
}

void sendMessage()
{
  Serial.println("Sending Data");
  radio.write(&data, sizeof(data));
  Serial.println("Sending complete");
}
