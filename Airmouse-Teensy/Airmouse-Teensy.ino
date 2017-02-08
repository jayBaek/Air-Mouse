#include <printf.h>
#include "RF24.h"

const int RED_SWITCH = 23;
const int GREEN_SWITCH = 22;
const int YELLOW_SWITCH = 21;
double Vout;
double Vin;
double analogReadValue;
uint8_t RecRButton;
uint8_t RecLButton;
double RecVoltage;
double printVoltage;
int percentage;

struct myData
{
  uint8_t RightButton;
  uint8_t LeftButton;
  uint8_t Voltage;
  uint8_t Decimal;
} data;

// R==1, G==2, Y==3

RF24 radio(9,10); //CEpin and CSpin
const uint64_t pipes[2] = {0xF0F0F0F0AA, 0xF0F0F0F066}; //address1, address2

void setup() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(3); //team number
  radio.setAutoAck(0);
  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.setPayloadSize(32); //12 bytes up to 32 bytes
  radio.setCRCLength(RF24_CRC_8);
  Serial.begin(9600);
  printf_begin();
  radio.startListening();
  pinMode(RED_SWITCH, OUTPUT);
  pinMode(GREEN_SWITCH, OUTPUT);
  pinMode(YELLOW_SWITCH, OUTPUT);
}

void loop() 
{
  
  //delay(1000);
  //radio.printDetails();
  while(!radio.available());
  
  if(radio.available())
  {
    getInfo();
    
    if((RecRButton == 0 || RecRButton == 1) && (RecLButton  == 0 || RecLButton == 1))
    {
      printDisplay();
      if ((printVoltage >= 0 || printVoltage <= 4.2))
      {   
        printVoltageColor();   
      }
    }
  }
}

void getInfo()
{
  radio.read(&data,sizeof(data));
  RecRButton = data.RightButton;
  RecLButton = data.LeftButton;
  RecVoltage = data.Voltage;
  printVoltage = data.Decimal;
  
  //convert voltage value into decimal
  printVoltage = RecVoltage+printVoltage/100;
  percentage = printVoltage*100/4.09; //4.11 is max. voltage
}

void printDisplay()
{
  Serial.print("----------------------------");
  Serial.println("----------------------------");
  Serial.print("Received Left Button : ");
  Serial.print(RecLButton);
  Serial.print("  |   ");
  Serial.print("Received Right Button : ");
  Serial.println(RecRButton);
  Serial.print("Received Vin : ");
  Serial.println(printVoltage);
  //Serial.print("   (");
  //Serial.print(percentage);
  //Serial.println(" %)");
}

void printVoltageColor()
{
  if(printVoltage >= 3.9 && printVoltage <= 4.2) // Green
  {
    digitalWrite(RED_SWITCH,LOW);
    digitalWrite(GREEN_SWITCH,HIGH);
    digitalWrite(YELLOW_SWITCH,LOW);
  }

  if(printVoltage >= 3.7 && printVoltage < 3.9) // Yellow
  {
    digitalWrite(RED_SWITCH,LOW);
    digitalWrite(GREEN_SWITCH,LOW);
    digitalWrite(YELLOW_SWITCH,HIGH);
  }

  if(printVoltage >= 0 && printVoltage < 3.7) // Red
  {
    digitalWrite(RED_SWITCH,HIGH);
    digitalWrite(GREEN_SWITCH,LOW);
    digitalWrite(YELLOW_SWITCH,LOW);
  }
  //delay(100);
}

