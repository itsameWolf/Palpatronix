//Define pins for the incremental encoder
#define EncoderA
#define EncoderB

//Define pins for the motor driver
#define EnableA
#define EnableB
#define CurrentControlA
#define CurrentControlb
#define StepperA1
#define StepperA2
#define StepperB1
#define StepperB2

//Define pi for the hall effect sensor
#define HallIn



void setup() {
  // put your setup code here, to run once:
  pinMode(EncoderA,INPUT);
  pinMode(EncoderB,INPUT);

  pinMode(EnableA,OUTPUT);
  pinMode(EnableB,OUTPUT);
  pinMode(CurrentCOntrolA,OUTPUT);
  pinMode(CurrentControlB,OUTPUT); 
  pinMode(StepperA1,OUTPUT);
  pinMode(StepperA2,OUTPUT);
  pinMode(StepperB1,OUTPUT);
  pinMode(StepperB2,OUTPUT);

  pinMode(HallIn,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

}
