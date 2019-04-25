  //Define pins for the incremental encoder
#define EncoderA2 9
#define EncoderB2 10

void initialiseEncoder2()
{
  //Set the pins connected to the encoder as inputs
  pinMode(EncoderA2, INPUT);
  pinMode(EncoderB2, INPUT);

  //Enable interrupts for the pins connected to channel A of the encoder for both rising and falling edge
  attachInterrupt(digitalPinToInterrupt(EncoderA2), Arising, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderA2), Afalling, FALLING);
  //Enable interrupts for the pins connected to channel B of the encoder for both rising and falling edge
  attachInterrupt(digitalPinToInterrupt(EncoderB2), Brising, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB2), Bfalling, FALLING);
}

////////////////////////////////////Dynamic Readings////////////////////////////////////
void updateSpeed2()
{
  stepperSpeed2 = (Ticks2 - lastTicks2) / pollingRatio;
  lastTicks2 = Ticks2;
}

void updateAcceleration2()
{
  stepperAccel2 = (stepperSpeed2 - LastStepperSpeed2) / pollingRatio2;
  LastStepperSpeed2 = stepperSpeed2;
}

////////////////////////////////////Encoder ISR////////////////////////////////////
void Arising2()
{
  if (digitalRead(EncoderB2))
  {
    Ticks2++;
  } else {
    Ticks2--;
  }
}

void Afalling2()
{
  if (digitalRead(EncoderB2))
  {
    Ticks2--;
  } else {
    Ticks2++;
  }
}

void Brising2()
{
  if (digitalRead(EncoderA2))
  {
    Ticks2--;
  } else {
    Ticks2++;
  }
}

void Bfalling2()
{
  if (digitalRead(EncoderA2))
  {
    Ticks2++;
  } else {
    Ticks2--;
  }
}
