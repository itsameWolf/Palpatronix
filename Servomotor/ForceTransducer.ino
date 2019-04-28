//Define pi for the hall effect sensor
#define HallIn A14

void initialiseForceTransducer()
{
  pinMode(HallIn, INPUT);
  analogReadRes(12);
}

