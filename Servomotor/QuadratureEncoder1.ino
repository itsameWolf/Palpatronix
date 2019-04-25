  //Define pins for the incremental encoder
#define EncoderA1 11
#define EncoderB1 12

void initialiseEncoder1()
{
  //Set the pins connected to the encoder as inputs
  pinMode(EncoderA1, INPUT);
  pinMode(EncoderB1, INPUT);

  //Enable interrupts for the pins connected to channel A of the encoder for both rising and falling edge
  attachInterrupt(digitalPinToInterrupt(EncoderA1), Arising, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderA1), Afalling, FALLING);
  //Enable interrupts for the pins connected to channel B of the encoder for both rising and falling edge
  attachInterrupt(digitalPinToInterrupt(EncoderB1), Brising, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB1), Bfalling, FALLING);
}

////////////////////////////////////Dynamic Readings////////////////////////////////////
void updateSpeed1()
{
  stepperSpeed1 = (Ticks1 - lastTicks1) / pollingRatio;
  lastTicks1 = Ticks1;
}

void updateAcceleration1()
{
  stepperAccel1 = (stepperSpeed1 - LastStepperSpeed1) / pollingRatio;
  LastStepperSpeed1 = stepperSpeed1;
}

////////////////////////////////////Encoder ISR////////////////////////////////////
void Arising1()
{
  if (digitalRead(EncoderB1))
  {
    Ticks1++;
  } else {
    Ticks1--;
  }
}

void Afalling1()
{
  if (digitalRead(EncoderB1))
  {
    Ticks1--;
  } else {
    Ticks1++;
  }
}

void Brising1()
{
  if (digitalRead(EncoderA1))
  {
    Ticks1--;
  } else {
    Ticks1++;
  }
}

void Bfalling1()
{
  if (digitalRead(EncoderA1))
  {
    Ticks1++;
  } else {
    Ticks1--;
  }
}
