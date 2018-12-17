IntervalTimer steppingFrequency;

//Define pins for the incremental encoder
#define EncoderA 1
#define EncoderB 2

//Define pins for the motor driver
#define EnableA 3
#define EnableB 4
#define CurrentControlA 5
#define CurrentControlB 6
#define StepperA1 7
#define StepperA2 8
#define StepperB1 9
#define StepperB2 10

//Define pi for the hall effect sensor
#define HallIn 11

volatile long Ticks = 0;
volatile long steps = 0;
volatile int stepperState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(EncoderA,INPUT);
  pinMode(EncoderB,INPUT);

  attachInterrupt(digitalPinToInterrupt(EncoderA),Arising,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderA),Afalling,FALLING);

  attachInterrupt(digitalPinToInterrupt(EncoderB),Brising,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB),Bfalling,FALLING);
  
  //attachInterrupt(digitalPinToInterrupt(EncoderA),ChannelA,CHANGE);
  //attachInterrupt(digitalPinToInterrupt(EncoderB),ChannelB,CHANGE);
  
  pinMode(EnableA,OUTPUT);
  pinMode(EnableB,OUTPUT);
  pinMode(CurrentControlA,OUTPUT);
  pinMode(CurrentControlB,OUTPUT); 
  pinMode(StepperA1,OUTPUT);
  pinMode(StepperA2,OUTPUT);
  pinMode(StepperB1,OUTPUT);
  pinMode(StepperB2,OUTPUT);

  steppingFrequency.begin(steppingISR,1000000);

  pinMode(HallIn,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}
/////////////////////////////////Stepper Functions/////////////////////////////////

void setStepperSpeed(int Speed)
{
  steppingFrequency.update(1000000/Speed);
}

void stopStepper()
{
  stepperState = 0;
}

void moveForward()
{
  stepperState = 1;
}

void moveBackward()
{
  stepperState = 2;
}

void steppingISR()
{
  switch (stepperState)
  {
    case 0:
      break;
    case 1:
      stepCycle(steps & 0x3);
      steps++;
      break;
    case 2:
      stepCycle(steps & 0x3);
      steps--;
  }
}

void stepCycle(int Step)
{
  switch(Step)
  {
    case 0:
      digitalWrite(StepperA1,HIGH);
      digitalWrite(StepperA2,LOW);
      digitalWrite(StepperB1,HIGH);
      digitalWrite(StepperB2,LOW);
      break;
    case 1:
      digitalWrite(StepperA1,LOW);
      digitalWrite(StepperA2,HIGH);
      digitalWrite(StepperB1,HIGH);
      digitalWrite(StepperB2,LOW);
      break;
    case 2:
      digitalWrite(StepperA1,LOW);
      digitalWrite(StepperA2,HIGH);
      digitalWrite(StepperB1,LOW);
      digitalWrite(StepperB2,HIGH);
      break;
    case 3:
      digitalWrite(StepperA1,HIGH);
      digitalWrite(StepperA2,LOW);
      digitalWrite(StepperB1,LOW);
      digitalWrite(StepperB2,HIGH);
      break;
  }
}

////////////////////////////////////Encoder ISR////////////////////////////////////
void Arising()
{
  if (digitalRead(EncoderB))
  {
    Ticks++;
  }else{
    Ticks--;
  }
}

void Afalling()
{
  if (digitalRead(EncoderB))
  {
    Ticks--;
  }else{
    Ticks++;
  }
}

void Brising()
{
  if (digitalRead(EncoderA))
  {
    Ticks--;
  }else{
    Ticks++;
  }
}

void Bfalling()
{
  if (digitalRead(EncoderA))
  {
    Ticks++;
  }else{
    Ticks--;
  }
}

/*
void ChannelA()
{
  if (digitalRead(EncoderA)
  {
    if (digitalRead(EncoderB)
    {
      Ticks--  
    } else 
    {
      Ticks++
    }
  }else
  {
    if (digitalRead(EncoderB)
    {
      Ticks++  
    } else 
    {
      Ticks--
    }
  }
}

void ChannelB()
{
  if (digitalRead(EncoderB)
  {
    if (digitalRead(EncoderA)
    {
      Ticks--  
    } else 
    {
      Ticks++
    }
  }else
  {
    if (digitalRead(EncoderA)
    {
      Ticks++  
    } else 
    {
      Ticks--
    }
  }
}
*/

