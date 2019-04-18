volatile long Ticks = 0L;          //Global variable storing encoder ticks
//volatile long lastTicks = 0L;

//int sine[32] =  {1,17,32,47,60,70,78,85,85,78,70,60,47,32,17,1,-1,-17,-32,-47,-60,-70,-78,-85,-85,-78,-70,-60,-47,-32,-17,-1};
//int cosine[32] =  {85,78,70,60,47,32,17,1,-1,-17,-32,-47,-60,-70,-78,-85,-85,-78,-70,-60,-47,-32,-17,-1,1,17,32,47,60,70,78,85};

//int sine[32] =  {1,8,16,24,30,35,39,42,42,39,35,30,24,16,8,1,-1,-8,-16,-24,-30,-35,-39,-42,-42,-39,-35,-30,-24,-16,-8,-1};
//int cosine[32] =  {42,39,35,30,24,16,8,1,-1,-8,-16,-24,-30,-35,-39,-42,-42,-39,-35,-30,-24,-16,-8,-1,1,8,16,24,30,35,39,42};

float sine[32] = {0.0, 0.09, 0.19, 0.29, 0.38, 0.47, 0.55, 0.63, 0.70, 0.77, 0.83, 0.88, 0.92, 0.95, 0.98, 0.99, 0.99, 0.98, 0.95, 0.92, 0.88, 0.83, 0.77, 0.70, 0.63, 0.55, 0.47, 0.38, 0.29, 0.19, 0.09, 0.0};

volatile float currentA;
volatile float currentB;
volatile int IA;
volatile int IB;
volatile int MaxCurrent = 1000;
volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile unsigned long steppingPeriod = 40 ;

unsigned int pollingRatio = 2;              //Refresh time of the main loop expressed in millinseconds

char cmd;

volatile unsigned long previousTime;
volatile unsigned long previousStepTime;

void setup()
{
  noInterrupts();

  initialiseStepperDriver();
  //initialiseEncoder();
  Serial.begin(9600);

  previousStepTime = millis();
  interrupts();

  //moveForward();
  moveBackward();
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousStepTime >= steppingPeriod)  //execute the following whenever a step is needed
  {
    previousStepTime = currentTime;
    //int t0 = micros();
    //stepperRun();
    microstep();
    //int t1 = micros();
    //int t = t1-t0;
    //Serial.printf("execution time: %d micros \n", t);
    //Serial.printf("State: %d \n", stepperState);
    //Serial.printf("A: %d   B: %d \n", IA, IB);
    //Serial.printf("A: %d \n", Ticks);
  }
}

// Code to check process executioon time
//    int st0 = micros();
//    int st1 = micros();
//    int tt = st1-st0;
//    Serial.print(currentTime);
//    Serial.println();



