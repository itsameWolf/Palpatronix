volatile long Ticks = 0L;          //Global variable storing encoder ticks
volatile long lastTicks = 0L;

int sine[32] =  {1,17,32,47,60,70,78,85,85,78,70,60,47,32,17,1,-1,-17,-32,-47,-60,-70,-78,-85,-85,-78,-70,-60,-47,-32,-17,-1};
int cosine[32] =  {85,78,70,60,47,32,17,1,-1,-17,-32,-47,-60,-70,-78,-85,-85,-78,-70,-60,-47,-32,-17,-1,1,17,32,47,60,70,78,85};

//int sine[32] =  {1,8,16,24,30,35,39,42,42,39,35,30,24,16,8,1,-1,-8,-16,-24,-30,-35,-39,-42,-42,-39,-35,-30,-24,-16,-8,-1};
//int cosine[32] =  {42,39,35,30,24,16,8,1,-1,-8,-16,-24,-30,-35,-39,-42,-42,-39,-35,-30,-24,-16,-8,-1,1,8,16,24,30,35,39,42};

volatile int quadrantFlag;
volatile int currentA = 40;
volatile int currentB = 0;
volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile double LastStepperSpeed = 0;
volatile double stepperSpeed = 0;
volatile double stepperAccel = 0;
volatile unsigned long steppingPeriod = 2 ;
float MaxSpeed = 10; 
volatile long targetPOS = 100000000 ;

unsigned int pollingRatio = 2;              //Refresh time of the main loop expressed in millinseconds

char cmd;


volatile unsigned long previousTime;
volatile unsigned long previousStepTime;

void setup()
{
  noInterrupts();

  initialiseStepperDriver();
  Serial.begin(9600);
  
  previousStepTime = millis();
  interrupts();

  moveForward();
  //moveBackward();
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
    Serial.printf("A: %d   B: %d \n", currentA, currentB);
    //Serial.println();
  }
}

// Code to check process executioon time
//    int st0 = micros();
//    int st1 = micros();
//    int tt = st1-st0;
//    Serial.print(currentTime);
//    Serial.println();



