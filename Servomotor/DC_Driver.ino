void initialiseDCDriver()
{
  //Set the pins connected to the motor driver as outputs
  pinMode(CurrentControlDC, OUTPUT);
  pinMode(DC1, OUTPUT);
  pinMode(DC2, OUTPUT);


  analogWriteFrequency(CurrentControlDC, 46875);
  analogWriteResolution(10);

  analogWrite(CurrentControlDC, 0);
}

//////////////////////////////////Motion Functions//////////////////////////////////

void MoveTo(long Target)
{
  setCurrentDC(Target - Ticks2); //Speed decreases as the motor moves closer to the desired position
  if (Target - steps > 0)
  {
    ForwardDC();
  }
  else if (Target - Ticks2 < 0)
  {
    BackwardDC();
  }
}
/////////////////////////////////Stepper Functions/////////////////////////////////

void setCurrentDC(int I)
{
  int i = abs(I);
  analogWrite(CurrentControlDC, i);
}

void ForwardDC()
{
  digitalWrite(DC1, HIGH);
  digitalWrite(DC2, LOW);
}

void BackwardDC()
{
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, HIGH);
}

void BrakeDC()
{
  digitalWrite(DC1, LOW);
  digitalWrite(DC2, LOW);
}
