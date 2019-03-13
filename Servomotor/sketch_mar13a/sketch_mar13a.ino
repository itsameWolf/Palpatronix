//Define pins for the motor driver L7207N
#define EnableA 3
#define EnableB 4
#define CurrentControlA 5
#define CurrentControlB 6
#define StepperA1 23
#define StepperA2 22
#define StepperB1 21
#define StepperB2 20

volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile double LastStepperSpeed = 0;
volatile double stepperSpeed = 0;
volatile double stepperAccel = 0;
volatile unsigned long steppingPeriod = 100 ;
float MaxSpeed = 100; 
volatile long targetPOS = 100000000 ;

volatile unsigned long previousStepTime;

void setup() {
  // put your setup code here, to run once:
  initialiseStepperDriver();
  setStepperSpeed(10);
  moveForward();
  previousStepTime = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  int currentTime = millis();
  if (currentTime - previousStepTime >= steppingPeriod)  //execute the following whenever a step is needed
  {
    previousStepTime = currentTime;
    stepperRun();
  }
}

void initialiseStepperDriver()
{
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

  analogWriteFrequency(CurrentControlA, 750000);
  analogWriteFrequency(CurrentControlB, 750000);
  analogWriteResolution(6);

  analogWrite(CurrentControlA,10);
  analogWrite(CurrentControlB,10);
}

//////////////////////////////////Motion Functions//////////////////////////////////
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

