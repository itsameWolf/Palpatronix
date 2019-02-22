volatile long Ticks = 0L;          //Global variable storing encoder ticks
volatile long lastTicks = 0L;

volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile double LastStepperSpeed = 0;
volatile double stepperSpeed = 0;
volatile double stepperAccel = 0;
volatile unsigned long steppingPeriod = 1000;
float MaxSpeed = 20;
volatile long targetPOS = 0;

unsigned int pollingRatio = 2;              //Refresh time of the main loop expressed in millinseconds

char cmd;


volatile unsigned long previousTime;
volatile unsigned long previousStepTime;

void setup()
{
  noInterrupts();

  initialiseEncoder();
  initialiseStepperDriver();
  initialiseForceTransducer();
  initialiseGcodeIntrerpreter();
  
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
    //    Serial.printf("steps = %lu",steps);
    //    Serial.println();
    //    Serial.printf("targetPOS = %lu",targetPOS);
    //    Serial.println();

    if (Serial.available() )
    {
      cmd = Serial.read();
    }
    MoveTo(targetPOS);
  }

  if (currentTime - previousStepTime >= steppingPeriod)  //execute the following whenever a step is needed
  {
    previousStepTime = currentTime;
    stepperRun();
  }
}

// Code to check process executioon time
//    int st0 = micros();
//    int st1 = micros();
//    int tt = st1-st0;
//    Serial.print(currentTime);
//    Serial.println();



