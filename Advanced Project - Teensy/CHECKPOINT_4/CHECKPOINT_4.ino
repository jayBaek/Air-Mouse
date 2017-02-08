const int RED = 2;
const int GREEN = 3;
const int YELLOW = 4;
int randNum;
int round_count = 1;
const int numRound = 15;
const int max_round = numRound;
int count = 0;
int blink_count = 1;
char randColor[16] = {};

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);

  Serial.begin(9600);
  Serial1.begin(9600);
  randomSeed(analogRead(A0)); //make it more random
}


void loop()
{
  Serial.println("WAITING...");
  
  delay(1000);
  if (count == 0)
  {
    randLED(); //to generate Random 20 LED flashes
    count++;
  }
  if (round_count == blink_count)
  {
    blinkLED(); //to light up LED flashes for game
    blink_count++;
  }

  //for output 
  if (Serial1.available())
    isCorrect();

  if (round_count == max_round)
  {
    Serial.println("PLAYER WON!! GAME OVER");
    exit(0);
  }

}

//to generate rnadom LED flashes
void randLED()
{
   for (int i=1; i<=numRound; i++)
  {
    randNum = random(1,10); //generate Random # from 1 to 9
    if (randNum == 1 || randNum ==4 || randNum ==7)
    {
      randColor[i] = 'R';
      delay(100);
    }
    if (randNum == 2 || randNum ==5 || randNum ==8)
    {
      randColor[i] = 'G';
      delay(100);
    }
    if (randNum == 3 || randNum ==6 || randNum ==9)
    {
      randColor[i] = 'Y';
      delay(100);
    }

    //for check
    /*
    char x = randColor[i];
    Serial.print(i);
    Serial.print(" value: ");
    Serial.println(x);
    */
    
  }

  for (int i=1; i<=numRound; i++)
  {
    //sending Random LED sequence to Arduino pro mini
    char x = randColor[i];
    Serial.println(Serial1.write(x));
    delay(100);
  }
  
//  Serial.end();
//  Serial1.end();
//  Serial.begin(9600);
//  Serial1.begin(9600);

  //to check my array  
  Serial.println("Checking Array");
  for (int i=1; i<=numRound; i++)
  {
    Serial.print(randColor[i]);
    Serial.print(", ");
  }
  Serial.println(" ");
}


//to blunk LED sequences
void blinkLED()
{
  Serial.println("BLINK LEDs begin");
  delay(500);
  Serial.print("Round: ");
  Serial.println(round_count);
  Serial.println(randColor);
  for (int i=1; i<=round_count; i++)
  {
    if (randColor[i] == 'R')
    {
      digitalWrite(RED, HIGH);
      delay(500);
      digitalWrite(RED, LOW);
      delay(500);
    }
    if (randColor[i] == 'G')
    {
      digitalWrite(GREEN, HIGH);
      delay(500);
      digitalWrite(GREEN, LOW);
      delay(500);
    }
    if (randColor[i] == 'Y')
    {
      digitalWrite(YELLOW, HIGH);
      delay(500);
      digitalWrite(YELLOW, LOW);
      delay(500);
    }
  }
  Serial.println("LEDs done");
}

void isCorrect()
{
  Serial.println("Avaiable");
    Serial.println("READING NOW");
    char x = Serial1.read();
    if (x == 'T')
    {
      Serial.println("Player won");
      digitalWrite(GREEN, HIGH);
      delay(2000);
      digitalWrite(GREEN, LOW);
      delay(500);
      round_count++;
    }

    if (x == 'F')
    {
      Serial.println("GAME OVER");
      digitalWrite(RED, HIGH);
      delay(200);
      digitalWrite(RED, LOW);
      delay(200);
      digitalWrite(RED, HIGH);
      delay(200);
      digitalWrite(RED, LOW);
      delay(200);
      digitalWrite(RED, HIGH);
      delay(200);
      digitalWrite(RED, LOW);
      exit(1);
    }
}

