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

  analogWriteFrequency(CurrentControlA, 187500 );
  analogWriteFrequency(CurrentControlB, 187500 );
  analogWriteResolution(8);

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
  switch (stepperState)
  {
    case 0:
      break;
    case 1:
      currentA = sine[(steps % 32)];
      currentB = cosine[(steps % 32)];
      bridgeState();
      setCurrentA(currentA);
      setCurrentB(currentB);
      steps++;
      break;
    case 2:
      currentA = cosine[(steps % 32)];
      currentB = sine[(steps % 32)];
      bridgeState();
      setCurrentA(currentA);
      setCurrentB(currentB);
      steps++;
      break;
  }
}

void bridgeState()
{
  if (currentA >= 0)
  {
    AForward();
    //Serial.printf("f");
  }
  else if (currentA < 0)
  {
    ABackward();
    //Serial.printf("b");
  }
  if (currentB >= 0)
  {
    BForward();
    //Serial.printf("f");
  }
  else if (currentB < 0)
  {
    BBackward();
    //Serial.printf("b \n");
  }
}
