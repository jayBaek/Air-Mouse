#include <printf.h>
#include "RF24.h"
#include <Wire.h>

double Vout;
double Vin;
double analogReadValue;
double ResistorDivision=.8213;//0.8116; // R2/(R1+R2) R2 = 
int RightButton;
int LeftButton;
double Voltage;
const int RS = 3; // Right Switch
const int LS = 8; // Left Switch
const int V = A3;
double sosu;


const int MPU_addr = 0x68;
uint8_t quantity = 0x00;
bool Stop = true;
bool enable = true;
uint16_t ax = 0x00; uint16_t ay = 0x00; uint16_t az = 0x00;
uint16_t gx = 0x00; uint16_t gy = 0x00; uint16_t gz = 0x00;
int count=1;


typedef enum : uint8_t
{
  GYRO_PREC_250 = 0,
  GYRO_PREC_500,
  GYRO_PREC_1000,
  GYRO_PREC_2000
} gyro_precision_e;
typedef enum : uint8_t
{
  ACCEL_PREC_2 = 0,
  ACCEL_PREC_4,
  ACCEL_PREC_8,
  ACCEL_PREC_16
} accel_precision_e;

struct myData
{
  uint8_t RightButton;
  uint8_t LeftButton;
  uint8_t Voltage;
  uint8_t Decimal;
} data;

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
  radio.printDetails();
  pinMode(RS,INPUT_PULLUP); // Right Button
  pinMode(LS,INPUT_PULLUP); // Left Button
  pinMode(V,INPUT); // Voltage Measurer

  Wire.begin();  
}

void loop() 
{
  while(count==1)
  {
  setSleep(enable);
  setGyroPrec(GYRO_PREC_250);
  setAccelPrec(ACCEL_PREC_2);
  printMessage();
  count = 0;
  }
  
  getAccelData_x(ax);
  getAccelData_x(ay);
  getAccelData_x(az);
  
  getGyroData(gx, gy, gz);

  printMessage();

  delay(500);

//  Serial.println("Start loop");
//  radio.stopListening();  
//  analogReadValue = analogRead(V);
//  RightButton = digitalRead(RS);
//  LeftButton = digitalRead(LS);
//  Serial.print("//////digital value :");
//  Serial.println(analogReadValue);
//  Vout = analogReadValue*3.295/1023.00;
//  Vin = Vout * (1/ResistorDivision);
//  Serial.print("Vout : ");
//  Serial.println(Vout);
//  Serial.print("Vin : ");
//  Serial.println(Vin);
//  Serial.print("Right Button : ");
//  Serial.println(RightButton);
//  Serial.print("Left Button : ");
//  Serial.println(LeftButton);
//  data.Voltage = Vin;
//  data.RightButton = RightButton;
//  data.LeftButton = LeftButton;
//  sosu = Vin - (int)Vin;
//  data.Decimal = 100*sosu;
//  Serial.print("Decimal is 0.");
//  Serial.println(data.Decimal);
//  sendMessage();
//  delay(200);
}

void sendMessage()
{
  Serial.println("Sending Data");
  radio.write(&data, sizeof(data));
  Serial.print("data.RightButton : ");
  Serial.println(data.RightButton);
  Serial.println("Sending is completed");
}

void setGyroPrec(uint8_t scale)
{
  Serial.println("Start setGyroScale");
scale &= 0b11;
scale = scale<<3;
Wire.beginTransmission(MPU_addr);
Wire.write(0x1B);  
Wire.write(scale);
Wire.endTransmission(true);
  Serial.println("setGyroScale is Completed");
}

void setAccelPrec(uint8_t scale)
{
  Serial.println("Start setAccelPrec");
scale &= 0b11;
scale = scale<<3;
Wire.beginTransmission(MPU_addr);
Wire.write(0x1C);  
Wire.write(scale);
Wire.endTransmission(true);
  Serial.println("setAccelPrec is Completed");
}

void getAccelData_x(int16_t* ax)
{
 //x-axis
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x3B);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr, 2, true);
 *ax = Wire.read() << 8 | Wire.read();
 Serial.println("getAccelData_x is Completed"); 
}
void getAccelData_y(int16_t* ay)
{
 //y-axis
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x3D);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr, 2, true);
 *ay = Wire.read() << 8 | Wire.read();
 Serial.println("getAccelData_y is Completed"); 


}
void getAccelData_z(int16_t* az)
{
 //z-axis
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x3F);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr, 2, true);
 *az = Wire.read() << 8 | Wire.read();
 Serial.println("getAccelData_z is Completed"); 
}

void getGyroData(int16_t* gx,int16_t* gy, int16_t* gz)
{
 Serial.println("Start getGyroData");

 //x-axis
 Wire.beginTransmission(MPU_addr);
 Wire.write(0x43);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr, 2, true);
 gx = Wire.read() << 8 | Wire.read();
 //Wire.endTransmission(true);

 //y-axis
 //Wire.beginTransmission(MPU_addr);
 Wire.write(0x45);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr, 2, true);
 gy = Wire.read() << 8 | Wire.read();
 //Wire.endTransmission(true);
 
 //z-axis
 //Wire.beginTransmission(MPU_addr);
 Wire.write(0x47);
 Wire.endTransmission(false);
 Wire.requestFrom(MPU_addr, 2, true);
 gz = Wire.read() << 8 | Wire.read();
 //Wire.endTransmission(true);
 
 Serial.println("getAccelData is completed");
}


void setSleep(bool enable)
{
  Serial.println("Start setSleep");  
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.requestFrom(MPU_addr, 1, true);
  uint8_t power = Wire.read();
  power &= 0b10111111;
  power |= enable<<6;

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(power);
  Wire.endTransmission(true);
  Serial.println("setSleep is Completed");
}

void printMessage()
{
  Serial.print("Accel) a_x:");
  Serial.print(ax);
  Serial.print("  |  ");
  Serial.print(" a_y:");
  Serial.print(ay);
  Serial.print("  |  ");
  Serial.print(" a_z:");
  Serial.println(az);

  Serial.print("Gyro) g_x:");
  Serial.print(gx);
  Serial.print("  |  ");
  Serial.print(" g_y:");
  Serial.print(gy);
  Serial.print("  |  ");
  Serial.print(" g_z:");
  Serial.print(gz);
  Serial.println(MPU_addr);  
}

