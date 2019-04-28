//Define pi for the hall effect sensor
#define HallIn A14
#define BridgeSense A3

void initialiseForceTransducer()
{
  pinMode(HallIn, INPUT);
  pinMode(BridgeSense, INPUT);
  analogReadRes(12);
}

