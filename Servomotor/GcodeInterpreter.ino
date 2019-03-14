/*#define max_buffer_length 10

char Buffer[max_buffer_length];
int bufferIndex = 0;
*/
void initialiseGcodeIntrerpreter()
{
  Serial.begin(9600);
}
/*
void readGcode()
{
  if (Serial.available())
  {
    c = Serial.read();
    if (bufferIndex < max_buffer_length)
    {
      Buffer[bufferIndex++] = c;
    }
    if (c == "/n")
    {
      Buffer[bufferIndex] = 0;
    }
  }
}
*/
