#include <stdio.h>
#include <math.h>

#define DC1 19
#define DC2 18
#define CurrentControlDC 4

volatile long Ticks1 = 0L;          //Global variable storing encoder ticks
volatile long lastTicks1 = 0L;

volatile long Ticks2 = 0L;          //Global variable storing encoder ticks
volatile long lastTicks2 = 0L;

//int sine[32] =  {1,17,32,47,60,70,78,85,85,78,70,60,47,32,17,1,-1,-17,-32,-47,-60,-70,-78,-85,-85,-78,-70,-60,-47,-32,-17,-1};
//int cosine[32] =  {85,78,70,60,47,32,17,1,-1,-17,-32,-47,-60,-70,-78,-85,-85,-78,-70,-60,-47,-32,-17,-1,1,17,32,47,60,70,78,85};

//int sine[32] =  {0,8,16,24,30,35,39,42,42,39,35,30,24,16,8,0,0,-8,-16,-24,-30,-35,-39,-42,-42,-39,-35,-30,-24,-16,-8,0};
//int cosine[32] =  {42,39,35,30,24,16,8,0,0,-8,-16,-24,-30,-35,-39,-42,-42,-39,-35,-30,-24,-16,-8,0,0,8,16,24,30,35,39,42};
//int cosineR[32] =  {-42,-39,-35,-30,-24,-16,-8,0,0,8,16,24,30,35,39,42,42,39,35,30,24,16,8,0,0,-8,-16,-24,-30,-35,-39,-42};

//float sine[16] = {0.0, 0.09, 0.19, 0.29, 0.38, 0.47, 0.55, 0.63, 0.70, 0.77, 0.83, 0.88, 0.92, 0.95, 0.98, 0.99};

float sine[5] = {0.0, 0.38, 0.71, 0.92, 1.0};

volatile float currentA;
volatile float currentB;
volatile float currentDC;
volatile int IA;
volatile int IB;
volatile int MaxCurrent = 1000;
volatile long steps = 0L;          //Global variable storing motor Steps
volatile int stepperState = 0;     //Flag defining the stepper motor behaviour 0 = still, 1 = moving forward, 2 = moving backward
volatile float LastStepperSpeed1 = 0;
volatile float LastStepperSpeed2 = 0;
volatile float stepperSpeed1 = 0;
volatile float stepperAccel1 = 0;
volatile float stepperSpeed2 = 0;
volatile float stepperAccel2 = 0;
volatile long steppingPeriod = 5 ;
float MaxSpeed = 10;
volatile long targetPOS = 100000000 ;

unsigned int pollingRatio = 20;              //Refresh time of the main loop expressed in millinseconds

char cmd;

volatile unsigned long previousTime;
volatile unsigned long previousStepTime;

float km = 1;
float ks = 2;
float bm = 1;
float bs = 2;
float ROMratio = 6;
float masterForce;
float slaveForce;
float scale = 1;
float targetSpeed;
int kp = 200;


void setup()
{
  noInterrupts();

  initialiseDCDriver();
  initialiseStepperDriver();
  initialiseEncoder1();
  initialiseEncoder2();
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
    updateSpeed1();
    updateAcceleration1();
    updateSpeed2();
    updateAcceleration2();
    if(abs(Ticks2)<200){
      targetSpeed = 0;
    }
    else{
      targetSpeed = 100.0;
    }
    float speedError = targetSpeed - float(ROMratio)*float(stepperSpeed1);
    float controlSignal = kp*speedError;
    
    /*
    float positionDifference = ROMratio*Ticks1-Ticks2;
    float speedDifference = ROMratio*stepperSpeed1-stepperSpeed2;
    masterForce = -(km*(positionDifference)+bm(speedDifference));
    slaveForce = ks*(positionDifference)+bs(speedDifference);
    Serial.printf("%f , %f \n", masterForce, slaveForce));
    */
    ForwardDC();
    setCurrentDC(static_cast<int>(controlSignal));
    int voltageRead = analogRead(A14);
    Serial.printf("%d , %f , %d,  %f , %f , %f , %d \n",Ticks2 , targetSpeed, Ticks1, stepperSpeed1 , speedError, controlSignal , voltageRead);
  }

  /*if (currentTime - previousStepTime >= steppingPeriod)  //execute the following whenever a step is needed
  {
    previousStepTime = currentTime;
    microstep();
  }*/
}

// Code to check process executioon time
//    int st0 = micros();
//    int st1 = micros();
//    int tt = st1-st0;
//    Serial.print(currentTime);
//    Serial.println();



