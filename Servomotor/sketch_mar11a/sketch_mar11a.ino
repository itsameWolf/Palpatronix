#define CurrentControlA 5
#define CurrentControlB 6

void setup() {
  // put your setup code here, to run once:
  pinMode(CurrentControlA, OUTPUT);
  pinMode(CurrentControlB, OUTPUT);
  
  analogWriteFrequency(CurrentControlA, 200000);
  analogWriteFrequency(CurrentControlB, 200000);
  analogWriteResolution(10);

  analogWrite(CurrentControlA, 300);
  analogWrite(CurrentControlB, 300);
}


void loop() {
  // put your main code here, to run repeatedly:

}
