//Define pins for the incremental encoder
#define EncoderA 11
#define EncoderB 12

void initialiseEncoder() 
{
  //Set the pins connected to the encoder as inputs
  pinMode(EncoderA, INPUT);
  pinMode(EncoderB, INPUT);

  //Enable interrupts for the pins connected to channel A of the encoder for both rising and falling edge
  attachInterrupt(digitalPinToInterrupt(EncoderA), Arising, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderA), Afalling, FALLING);
  //Enable interrupts for the pins connected to channel B of the encoder for both rising and falling edge
  attachInterrupt(digitalPinToInterrupt(EncoderB), Brising, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB), Bfalling, FALLING);
}

////////////////////////////////////Dynamic Readings////////////////////////////////////
void updateSpeed()
{
  stepperSpeed = (Ticks - lastTicks) / pollingRatio;
  lastTicks = Ticks;
}

void updateAcceleration()
{
  stepperAccel = (stepperSpeed - LastStepperSpeed) / pollingRatio;
  LastStepperSpeed = stepperSpeed;
}

////////////////////////////////////Encoder ISR////////////////////////////////////
void Arising()
{
  if (digitalRead(EncoderB))
  {
    Ticks++;
  } else {
    Ticks--;
  }
}

void Afalling()
{
  if (digitalRead(EncoderB))
  {
    Ticks--;
  } else {
    Ticks++;
  }
}

void Brising()
{
  if (digitalRead(EncoderA))
  {
    Ticks--;
  } else {
    Ticks++;
  }
}

void Bfalling()
{
  if (digitalRead(EncoderA))
  {
    Ticks++;
  } else {
    Ticks--;
  }
}
