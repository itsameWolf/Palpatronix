//Define pins for the motor driver L7207N
#define CurrentControl 5
#define DC1 23
#define DC2 22

#define MaxCurrent 40
#define CurrentIncrement 4

void initialiseStepperDriver()
{
  //Set the pins connected to the motor driver as outputs
  pinMode(EnableA, OUTPUT);
  pinMode(EnableB, OUTPUT);
  pinMode(CurrentControl, OUTPUT);
  pinMode(DC1, OUTPUT);
  pinMode(DC2, OUTPUT);


  analogWriteFrequency(CurrentControl, 187500 );
  analogWriteResolution(8);

  analogWrite(CurrentControl, 0);
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

void setCurrent(int I)
{
  int i = abs(I);
  analogWrite(CurrentControl, i);
}

void Forward()
{
  digitalWrite(DC1, HIGH);
  digitalWrite(DC2, LOW);
}

void Backward()
{
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, HIGH);
}

void Brake()
{
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, LOW);
}
