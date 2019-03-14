//Define pins for the motor driver L7207N
#define EnableA 3
#define EnableB 4
#define CurrentControlA 5
#define CurrentControlB 6
#define StepperA1 23
#define StepperA2 22
#define StepperB1 21
#define StepperB2 20

#define MaxCurrent 40
#define CurrentIncrement 4

void initialiseStepperDriver()
{
  //Set the pins connected to the motor driver as outputs
  pinMode(EnableA, OUTPUT);
  pinMode(EnableB, OUTPUT);
  pinMode(CurrentControlA, OUTPUT);
  pinMode(CurrentControlB, OUTPUT);
  pinMode(StepperA1, OUTPUT);
  pinMode(StepperA2, OUTPUT);
  pinMode(StepperB1, OUTPUT);
  pinMode(StepperB2, OUTPUT);

  digitalWrite(EnableA, HIGH);
  digitalWrite(EnableB, HIGH);

  analogWriteFrequency(CurrentControlA, 187500 );
  analogWriteFrequency(CurrentControlB, 187500 );
  analogWriteResolution(8);

  analogWrite(CurrentControlA, 5);
  analogWrite(CurrentControlB, 5);
}

//////////////////////////////////Motion Functions//////////////////////////////////
void setStepperSpeed(float Speed)
{
  if (Speed == 0)
  {
    stopStepper();
  } else {
    if (Speed > MaxSpeed)
    {
      Speed = MaxSpeed;
    }
    steppingPeriod = 1000 / Speed;
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

void MoveTo(long Target)
{
  setStepperSpeed(abs(Target - steps)); //Speed decreases as the motor moves closer to the desired position
  if (Target - steps > 0)
  {
    moveForward();
  }
  else if (Target - steps < 0)
  {
    moveBackward();
  } else {
    stopStepper();
  }
}
/////////////////////////////////Stepper Functions/////////////////////////////////
void enableStepper()
{
  digitalWrite(EnableA, HIGH);
  digitalWrite(EnableB, HIGH);
}

void disableStepper()
{
  digitalWrite(EnableA, LOW);
  digitalWrite(EnableB, LOW);
}

void setCurrentA(int I)
{
  int i = abs(I);
  analogWrite(CurrentControlA, i);
}

void setCurrentB(int I)
{
  int i = abs(I);
  analogWrite(CurrentControlB, i);
}

void stepperRun()
{
  switch (stepperState)
  {
    case 0:
      break;
    case 1:
      microstepForward();
      setCurrentA(currentA);
      setCurrentB(currentB);
      break;
    case 2:
      microstepBackward();
      setCurrentA(currentA);
      setCurrentB(currentB);
      break;
  }
}

void stepCycle(int Step)
{
  switch (Step)
  {
    case 0:   //1010
      stateFF();
      break;
    case 1:   //0110
      stateFB();
      break;
    case 2:   //0101
      stateBB();
      break;
    case 3:  //1001
      stateBF();
      break;
  }
}

void microstepCycle()
{
  switch (stepperState)
  {
    case 1:
      microstepForward();
    case 2:
      microstepBackward();
  }
}

void microstepForward()
{
  if (currentA == 0 && currentB == MaxCurrent)
  {
    quadrantFlag = 0; 
  }
  else if (currentA == MaxCurrent && currentB == 0)
  {
    quadrantFlag = 1;
  }
  else if (currentA == 0 && currentB == -(MaxCurrent))
  {
    quadrantFlag = 2;
  }
  else if (currentA == -MaxCurrent && currentB == 0)
  {
    quadrantFlag = 3;
  }
  switch (quadrantFlag)
  {
    case 0:
      stateFF();
      currentA += CurrentIncrement;
      currentB -= CurrentIncrement;
      break;
    case 1:
      stateFB();
      currentA -= CurrentIncrement;
      currentB -= CurrentIncrement;
      break;
    case 2:
      stateBB();
      currentA -= CurrentIncrement;
      currentB += CurrentIncrement;
      break;
    case 3:
      stateBF();
      currentA += CurrentIncrement;
      currentB += CurrentIncrement;
      break;
  }
  steps ++;
}

void microstepBackward()
{
  if (currentA == 0 && currentB == MaxCurrent)
  {
    quadrantFlag = 3;
  }
  else if (currentA == MaxCurrent && currentB == 0)
  {
    quadrantFlag = 2;
  }
  else if (currentA == 0 && currentB == -MaxCurrent)
  {
    quadrantFlag = 1;
  }
  else if (currentA == -MaxCurrent && currentB == 0)
  {
    quadrantFlag = 0;
  }
  switch (quadrantFlag)
  {
    case 0:
      currentA ++;
      currentB --;
      break;
    case 1:
      currentA --;
      currentB --;
      break;
    case 2:
      currentA --;
      currentB ++;
      break;
    case 3:
      currentA --;
      currentB ++;
      break;
  }
  steps --;
}

void stateFF()
{
  digitalWrite(StepperA1, HIGH);
  digitalWrite(StepperA2, LOW);
  digitalWrite(StepperB1, HIGH);
  digitalWrite(StepperB2, LOW);
}

void stateFB()
{
  digitalWrite(StepperA1, LOW);
  digitalWrite(StepperA2, HIGH);
  digitalWrite(StepperB1, HIGH);
  digitalWrite(StepperB2, LOW);
}

void stateBB()
{
  digitalWrite(StepperA1, LOW);
  digitalWrite(StepperA2, HIGH);
  digitalWrite(StepperB1, LOW);
  digitalWrite(StepperB2, HIGH);
}

void stateBF()
{
  digitalWrite(StepperA1, HIGH);
  digitalWrite(StepperA2, LOW);
  digitalWrite(StepperB1, LOW);
  digitalWrite(StepperB2, HIGH);
}
