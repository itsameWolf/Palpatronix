IntervalTimer steppingFrequency;

//Define pins for the incremental encoder
#define EncoderA
#define EncoderB

//Define pins for the motor driver
#define EnableA
#define EnableB
#define CurrentControlA
#define CurrentControlb
#define StepperA1
#define StepperA2
#define StepperB1
#define StepperB2

//Define pi for the hall effect sensor
#define HallIn

volatile long Ticks = 0;

volatile long steps = 0;

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
  pinMode(CurrentCOntrolA,OUTPUT);
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

setStepperSpeed(int Speed)
{
  steppingFrequency.update(1000000/Speed);
}

stepCycle(int Step)
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
    case 0:
      digitalWrite(StepperA1,HIGH);
      digitalWrite(StepperA2,LOW);
      digitalWrite(StepperB1,LOW);
      digitalWrite(StepperB2,HIGH);
      break;
  }
}

void steppingISR()
{
  switch (stepperSate)
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
////////////////////////////////////Encoder ISR////////////////////////////////////
void Arising()
{
  if (digitalRead(ChannelB)
  {
    Ticks++;
  }else{
    Ticks--;
  }
}

void Afalling()
{
  if (digitalRead(ChannelB))
  {
    Ticks--;
  }else{
    ticks++;
  }
}

void Brising()
{
  if (digitalRead(ChannelA))
  {
    Ticks--;
  }else{
    Ticks++;
  }
}

void Bfalling()
{
  if (digitalRead(ChannelA)
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

