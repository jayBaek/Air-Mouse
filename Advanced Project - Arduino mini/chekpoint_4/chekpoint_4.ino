#include <SoftwareSerial.h>
SoftwareSerial mySerial(6,5);

const int RED_SWITCH = 2;
const int GREEN_SWITCH = 3;
const int YELLOW_SWITCH = 4;
char LED_sequence[15]={};
int count=0;
char BUTTON_sequence[15]={};
int t_round=0;
int g_round=1;
int q;
bool done=false;
bool escape=true;
  int REDreading; 
  int YELLOWreading;
  int GREENreading;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(RED_SWITCH, INPUT_PULLUP);
  pinMode(GREEN_SWITCH, INPUT_PULLUP);
  pinMode(YELLOW_SWITCH, INPUT_PULLUP);
}

void loop() {
    // read the state of the switch into a local variable:
  if(mySerial.available())
  {
    for(int i=0;i<15;i++)
    {      
        LED_sequence[i] = mySerial.read();
        Serial.println(LED_sequence[i]);
        delay(100);   
    }
    done = true;
 //   delay(4000);
//    Serial.println(Wire.write('T'));
  }
//delay(3000);

  //0 -> HIGH
  //1 -> LOW
//  Serial.println(REDreading);
  //delay(100);
if(escape)
{
 if(done)
 {
  t_round = 0;
    while(t_round < g_round)
 {   
  if (digitalRead(RED_SWITCH) == 0)
  {
    //turn RIGHT on
    BUTTON_sequence[t_round]='R';
    delay(300);
    Serial.println("R is pressed");
    t_round++;
  }
  else if (digitalRead(YELLOW_SWITCH) == 0 )
  {
    //turn RIGHT on
    BUTTON_sequence[t_round]='Y';
    delay(300);
    Serial.println("Y is pressed");
    t_round++;

  }
  else if (digitalRead(GREEN_SWITCH) == 0 )
  {
    //turn RIGHT on
    BUTTON_sequence[t_round]='G';
    delay(300);
    Serial.println("G is pressed");
    t_round++;
  }
 }

if(t_round == g_round)
    {
      q=g_round;
      for(;q!=0;q--)
      {
        Serial.println(BUTTON_sequence[g_round-q]);
        Serial.println(LED_sequence[t_round-q]);
       if(BUTTON_sequence[g_round-q]!=LED_sequence[t_round-q])
      {
        Serial.println("Here 1");
    Serial.println("WE failed");
    Serial.println(mySerial.write('F'));
    Serial.println(mySerial.write('F'));
    Serial.println(mySerial.write('F'));
    t_round=20;
    escape = false;
    }
      }
      if(escape)
      {
    
    Serial.println("Here 2");
        
    Serial.print("Round  ");
    Serial.print(g_round);
    Serial.println(" is over!");
    Serial.println(mySerial.write('T'));      
    g_round++;
      }
    }
    }
    }
}
  



void initialize()
{
int count = 0;
if(count=0)
{
  Serial.end();
  Serial.begin(9600);
}
count++;
}


