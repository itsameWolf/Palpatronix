//Define pi for the hall effect sensor
#define HallIn 14

volatile long Ticks = 0L;          //Global variable storing encoder ticks
volatile long lastTicks = 0L;

volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile double LastStepperSpeed = 0;
volatile double stepperSpeed = 0;
volatile double stepperAccel = 0;
volatile unsigned long steppingPeriod = 1000;
float MaxSpeed = 20;
volatile long targetPOS = 200;

unsigned int pollingRatio = 2;              //Refresh time of the main loop expressed in millinseconds


volatile unsigned long previousTime;
volatile unsigned long previousStepTime;

void setup()
{
  noInterrupts();
  
  initialiseEncoder();
  initialiseStepperDriver();
  
  Serial.begin(9600);
  
  //steppingPeriod.begin(steppingISR, 1000000);

  pinMode(HallIn, INPUT);

  previousTime = millis();
  previousStepTime = millis();
  interrupts();
  delay(3000);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= pollingRatio)  //execute the following code every every 2 milliseconds
  {
    previousTime = currentTime;
    
//    Serial.printf("steppingPeriod = %lu",steppingPeriod);
//    Serial.println();
//    Serial.printf("stepperState = %lu",stepperState);
//    Serial.println();
    Serial.printf("steps = %lu",steps);
    Serial.println();
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
    previousStepTime = currentTime;
  }
}




