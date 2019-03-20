//Define pins for the motor driver L7207N
#define EnableA 3
#define EnableB 4
#define CurrentControlA 5
#define CurrentControlB 6
#define StepperA1 23
#define StepperA2 22
#define StepperB1 21
#define StepperB2 20


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

  analogWriteFrequency(CurrentControlA, 46875);
  analogWriteFrequency(CurrentControlB, 46875);
  analogWriteResolution(10);

  analogWrite(CurrentControlA, 5);
  analogWrite(CurrentControlB, 5);
}

//////////////////////////////////Motion Functions//////////////////////////////////

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

/////////////////////////////////Stepper Functions/////////////////////////////////

void setCurrentA()
{
  int i = abs(IA);
  analogWrite(CurrentControlA, i);
}

void setCurrentB()
{
  int i = abs(IB);
  analogWrite(CurrentControlB, i);
}

void AForward()
{
  digitalWrite(StepperA1, HIGH);
  digitalWrite(StepperA2, LOW);
}

void ABackward()
{
  digitalWrite(StepperA1, LOW);
  digitalWrite(StepperA2, HIGH);
}

void BForward()
{
  digitalWrite(StepperB1, HIGH);
  digitalWrite(StepperB2, LOW);
}

void BBackward()
{
  digitalWrite(StepperB1, LOW);
  digitalWrite(StepperB2, HIGH);
}

void microstep()
{

  if (stepperState == 1)
  {
    if (steps < 16)
    {
      currentA = sine[(steps % 16)];
      currentB = sine[(15 - (steps % 16))];
    }
    else if (steps < 32)
    {
      currentA = sine[(15 - (steps % 16))];
      currentB = -(sine[(steps % 16)]);
    }
    else if (steps < 48)
    {
      currentA = -(sine[(steps % 16)]);
      currentB = -(sine[(15 - (steps % 16))]);
    }
    else
    {
      currentA = -(sine[(15 - (steps % 16))]);
      currentB = sine[(steps % 16)];
    }
  }
  else if (stepperState == 2)
  {
    {
      if (steps < 16)
      {
        currentA = sine[(steps % 16)];
        currentB = -(sine[(15 - (steps % 16))]);
      }
      else if (steps < 32)
      {
        currentA = sine[(15 - (steps % 16))];
        currentB = sine[(steps % 16)];
      }
      else if (steps < 48)
      {
        currentA = -(sine[(steps % 16)]);
        currentB = sine[(15 - (steps % 16))];
      }
      else
      {
        currentA = -(sine[(15 - (steps % 16))]);
        currentB = -(sine[(steps % 16)]);
      }
    }
  }
  bridgeState();
  currentA = currentA * MaxCurrent;
  currentB = currentB * MaxCurrent;
  IA = (int) currentA;
  IB = (int) currentB;
  setCurrentA();
  setCurrentB();
  if (steps >= 63)
  {
    steps = 0;
  }
  else
  {
    steps++;
  }
}

void bridgeState()
{
  if (currentA >= 0)
  {
    AForward();
  }
  else if (currentA < 0)
  {
    ABackward();
  }
  if (currentB >= 0)
  {
    BForward();
  }
  else if (currentB < 0)
  {
    BBackward();
  }
}
