volatile long Ticks = 0L;          //Global variable storing encoder ticks
volatile long lastTicks = 0L;

//int sine[32] =  {1,17,32,47,60,70,78,85,85,78,70,60,47,32,17,1,-1,-17,-32,-47,-60,-70,-78,-85,-85,-78,-70,-60,-47,-32,-17,-1};
//int cosine[32] =  {85,78,70,60,47,32,17,1,-1,-17,-32,-47,-60,-70,-78,-85,-85,-78,-70,-60,-47,-32,-17,-1,1,17,32,47,60,70,78,85};

//int sine[32] =  {0,8,16,24,30,35,39,42,42,39,35,30,24,16,8,0,0,-8,-16,-24,-30,-35,-39,-42,-42,-39,-35,-30,-24,-16,-8,0};
//int cosine[32] =  {42,39,35,30,24,16,8,0,0,-8,-16,-24,-30,-35,-39,-42,-42,-39,-35,-30,-24,-16,-8,0,0,8,16,24,30,35,39,42};
//int cosineR[32] =  {-42,-39,-35,-30,-24,-16,-8,0,0,8,16,24,30,35,39,42,42,39,35,30,24,16,8,0,0,-8,-16,-24,-30,-35,-39,-42};

float sine[16] = {0.0, 0.09, 0.19, 0.29, 0.38, 0.47, 0.55, 0.63, 0.70, 0.77, 0.83, 0.88, 0.92, 0.95, 0.98, 0.99};

volatile int quadrantFlag;
volatile int currentA = 40;
volatile int currentB = 0;
volatile int currentMultiplier = 10;
volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile double LastStepperSpeed = 0;
volatile double stepperSpeed = 0;
volatile double stepperAccel = 0;
volatile unsigned long steppingPeriod = 5 ;
float MaxSpeed = 10;
volatile long targetPOS = 100000000 ;

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

  moveForward();
  //moveBackward();
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

    //if (Serial.available() )
    //{
    //cmd = Serial.read();
    //}
    //MoveTo(targetPOS);
  }

  if (currentTime - previousStepTime >= steppingPeriod)  //execute the following whenever a step is needed
  {
    previousStepTime = currentTime;
    //int t0 = micros();
    //stepperRun();
    //microstep();
    //int t1 = micros();
    //int t = t1-t0;
    //Serial.printf("execution time: %d micros \n", t);
    //Serial.printf("State: %d \n", stepperState);
    Serial.printf("A: %d   B: %d  ss: %d \n", currentA, currentB, stepperState);
    //Serial.println();
  }

  if (currentTime > 7000)
  {
    moveBackward();
  }
}

// Code to check process executioon time
//    int st0 = micros();
//    int st1 = micros();
//    int tt = st1-st0;
//    Serial.print(currentTime);
//    Serial.println();



