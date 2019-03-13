//Define pins for the motor driver L7207N
#define EnableA 3
#define EnableB 4
#define CurrentControlA 5
#define CurrentControlB 6
#define StepperA1 23
#define StepperA2 22
#define StepperB1 21
#define StepperB2 20

#define MaxCurrent 20

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

  analogWriteFrequency(CurrentControlA, 750000);
  analogWriteFrequency(CurrentControlB, 750000);
  analogWriteResolution(6);

  analogWrite(CurrentControlA,5);
  analogWrite(CurrentControlB,5);
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
  if (i > MaxCurrent)
  {
    analogWrite(CurrentControlA, MaxCurrent);
  }
}

void setCurrentB(int I)
{
  int i = abs(I);
  if (i > MaxCurrent)
  {
    analogWrite(CurrentControlB, MaxCurrent);
  }
}

void stepperRun()
{
  switch (stepperState)
  {
    case 0:
      break;
    case 1:
      stepCycle(steps%(4*stepDivider));
      steps++;
      break;
    case 2:
      stepCycle(steps%(4*stepDivider));
      steps--;
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
      stateBB()
      break;
    case 3:  //1001
      stateBF()
      break;
  }
}

void microstepCycle(int step)
{
  if (!risingA && !rising)
  {
    currentA --;
    currentB ++;
    if (currentA == MaxCurrent && currentB == 0 && !rising)
    {
      stateFB();
    }
  }


     else if (currentA == 0 && currentB == MaxCurrent)
    {
      stateBB();
      currentA ++;
      currentB --;
    } else if ((currentA == MaxCurrent && currentB == 0))
    {
      stateBF();
      currentA --;
      currentB ++;
    } else if (currentA == 0 && currentB == MaxCurrent)
    {
      stateFF();
      currentA ++;
      currentB --;
    }
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