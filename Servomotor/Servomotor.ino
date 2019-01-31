//IntervalTimer steppingPeriod;    //Timer regulating the speed of the motor

//Define pins for the incremental encoder
#define EncoderA 11
#define EncoderB 12

//Define pins for the motor driver L7207N
#define EnableA 3
#define EnableB 4
#define CurrentControlA 5
#define CurrentControlB 6
#define StepperA1 23
#define StepperA2 22
#define StepperB1 21
#define StepperB2 20

//Define pi for the hall effect sensor
#define HallIn 14

volatile long lastTicks = 0L;
volatile long Ticks = 0L;          //Global variable storing encoder ticks
volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile double LastStepperSpeed = 0;
volatile double stepperSpeed = 0;
volatile double stepperAccel = 0;
unsigned int pollingRatio = 2;              //Refresh time of the main loop expressed in millinseconds
volatile unsigned long steppingPeriod = 1000;
float MaxSpeed = 2;

volatile long targetPOS = 1000000;

volatile unsigned long previousTime;
volatile unsigned long previousStepTime;

void setup()
{
  noInterrupts();
  //Set the pins connected to the encoder as inputs
  pinMode(EncoderA, INPUT);
  pinMode(EncoderB, INPUT);

  //Enable interrupts for the pins connected to channel A of the encoder for both rising and falling edge
  attachInterrupt(digitalPinToInterrupt(EncoderA), Arising, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderA), Afalling, FALLING);
  //Enable interrupts for the pins connected to channel B of the encoder for both rising and falling edge
  attachInterrupt(digitalPinToInterrupt(EncoderB), Brising, RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderB), Bfalling, FALLING);

  //Set the pins connected to the motor driver as outputs
  pinMode(EnableA, OUTPUT);
  pinMode(EnableB, OUTPUT);
  pinMode(CurrentControlA, OUTPUT);
  pinMode(CurrentControlB, OUTPUT);
  pinMode(StepperA1, OUTPUT);
  pinMode(StepperA2, OUTPUT);
  pinMode(StepperB1, OUTPUT);
  pinMode(StepperB2, OUTPUT);

  digitalWrite(EnableA, HIGH);
  digitalWrite(EnableB, HIGH);

  analogWrite(CurrentControlA, 125);
  analogWrite(CurrentControlB, 125);

  Serial.begin(9600);
  
  //steppingPeriod.begin(steppingISR, 1000000);

  pinMode(HallIn, INPUT);

  previousTime = millis();
  previousStepTime = millis();
  interrupts();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= pollingRatio)  //execute the following code every every 2 milliseconds
  {
    previousTime = currentTime;
    
    Serial.printf("steppingPeriod = %lu",steppingPeriod);
    Serial.println();
//    Serial.printf("stepperState = %lu",stepperState);
//    Serial.println();
//    Serial.printf("steps = %lu",steps);
//    Serial.println();
//    Serial.printf("targetPOS = %lu",targetPOS);
//    Serial.println();
     
    if (Serial.available() )
    {
      if (Serial.parseInt()>0) {
        targetPOS = Serial.parseInt();
      }
    }
    MoveTo(targetPOS);
  }
  
  if (currentTime - previousStepTime >= steppingPeriod)  //execute the following whenever a step is needed
  {
//    int st0 = micros();
    stepperRun();
//    int st1 = micros();
//    int tt = st1-st0;
//    Serial.print(currentTime);
//    Serial.println();
//    previousStepTime = currentTime;
  }
}

//////////////////////////////////Motion Functions//////////////////////////////////

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

void setStepperSpeed(float Speed)
{
  if (Speed == 0)
  {
    stopStepper();
  } else {
    if (Speed > MaxSpeed)
    {
      Speed = MaxSpeed;
    }
    steppingPeriod = 1000 / Speed;
  }
}

void stopStepper()
{
  stepperState = 0;
}

void moveForward()
{
  stepperState = 1;
}

void moveBackward()
{
  stepperState = 2;
}

void MoveTo(long Target)
{
  setStepperSpeed(abs(Target - steps)); //Speed decreases as the motor moves closer to the desired position
  if (Target - steps > 0)
  {
    moveForward();
  } 
  else if (Target - steps < 0) 
  {
    moveBackward();
  } else {
    stopStepper();
  }
}
/////////////////////////////////Stepper Functions/////////////////////////////////
void enableStepper()
{
  digitalWrite(EnableA, HIGH);
  digitalWrite(EnableB, HIGH);
}

void disableStepper()
{
  digitalWrite(EnableA, LOW);
  digitalWrite(EnableB, LOW);
}

void setCurrent(int I)
{
  analogWrite(CurrentControlA, I);
  analogWrite(CurrentControlB, I);
}

void stepperRun()
{
  switch (stepperState)
  {
    case 0:
      break;
    case 1:
      stepCycle(steps & 0x3);
      steps++;
      break;
    case 2:
      stepCycle(steps & 0x3);
      steps--;
  }
}

void stepCycle(int Step)
{
  switch (Step)
  {
    case 0:   //1010
      digitalWrite(StepperA1, HIGH);
      digitalWrite(StepperA2, LOW);
      digitalWrite(StepperB1, HIGH);
      digitalWrite(StepperB2, LOW);
      break;
    case 1:   //0110
      digitalWrite(StepperA1, LOW);
      digitalWrite(StepperA2, HIGH);
      digitalWrite(StepperB1, HIGH);
      digitalWrite(StepperB2, LOW);
      break;
    case 2:   //0101
      digitalWrite(StepperA1, LOW);
      digitalWrite(StepperA2, HIGH);
      digitalWrite(StepperB1, LOW);
      digitalWrite(StepperB2, HIGH);
      break;
    case 3:  //1001
      digitalWrite(StepperA1, HIGH);
      digitalWrite(StepperA2, LOW);
      digitalWrite(StepperB1, LOW);
      digitalWrite(StepperB2, HIGH);
      break;
  }
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

