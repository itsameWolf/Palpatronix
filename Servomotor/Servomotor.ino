#define CurrentControlDC 4
#define DC1 19
#define DC2 18

volatile long Ticks1 = 0L;          //Global variable storing encoder ticks
volatile long lastTicks1 = 0L;

volatile long Ticks2 = 0L;          //Global variable storing encoder ticks
volatile long lastTicks2 = 0L;

float sine[5] = {0.0, 0.38, 0.71, 0.92, 1.0};

volatile float currentA;
volatile float currentB;
volatile float currentDC;
volatile int IA;
volatile int IB;
volatile int MaxCurrent = 1000;
volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile double LastStepperSpeed1 = 0;
volatile double LastStepperSpeed2 = 0;
volatile double stepperSpeed1 = 0;
volatile double stepperAccel1 = 0;
volatile double stepperSpeed2 = 0;
volatile double stepperAccel2 = 0;
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

  initialiseStepperDriver();
  initialiseEncoder1();
  initialiseEncoder2();
  initialiseForceTransducer();
  initialiseGcodeIntrerpreter();

  previousTime = millis();
  previousStepTime = millis();

  Serial.begin(9600);
  
  interrupts();

  moveForward();
  //moveBackward();
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= pollingRatio)  //execute the following code every every 2 milliseconds
  {
    previousTime = currentTime;

    Serial.printf("ticks1: %d , ticks2: %d /n", Ticks1, Ticks2);
    /*updateSpeed1();
    updateAcceleration1();
    updateSpeed2();
    updateAcceleration2();
    masterForce = -(km*(Gm*Ticks1-Gs*Ticks2)+bm(Gm*stepperSpeed1-Gs*stepperSpeed2));
    slaveForce = ks*(Gm*Ticks1-Gs*Ticks2)+bm(Gm*stepperSpeed1-Gs*stepperSpeed2);*/
  }

  if (currentTime - previousStepTime >= steppingPeriod)  //execute the following whenever a step is needed
  {
    previousStepTime = currentTime;
    microstep();
  }
}

// Code to check process executioon time
//    int st0 = micros();
//    int st1 = micros();
//    int tt = st1-st0;
//    Serial.print(currentTime);
//    Serial.println();



