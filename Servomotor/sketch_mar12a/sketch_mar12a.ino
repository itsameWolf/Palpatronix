#define CurrentControlA 5
#define CurrentControlB 6

void setup() {
  // put your setup code here, to run once:
    pinMode(CurrentControlA, OUTPUT);
    pinMode(CurrentControlB, OUTPUT);

  analogWriteFrequency(CurrentControlA, 750000);
  analogWriteFrequency(CurrentControlB, 750000);
  analogWriteResolution(6);

  analogWrite(CurrentControlA, 20);
  analogWrite(CurrentControlB, 20);

}

void loop() {
  // put your main code here, to run repeatedly:
  while (1){
    int i = 0;
    while (i < 64) {
      analogWrite(CurrentControlA, i);
      analogWrite(CurrentControlB, i);
      delay(500);
      i += 4;
    }
  }
}
