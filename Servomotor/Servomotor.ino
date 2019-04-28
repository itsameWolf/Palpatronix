#include <stdio.h>
#include <math.h>

#define DC1 19
#define DC2 18
#define CurrentControlDC 4

//Define pins for the motor driver L7207N
#define CurrentControlA 5
#define CurrentControlB 6
#define StepperA1 23
#define StepperA2 22
#define StepperB1 21
#define StepperB2 20

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
volatile int cycleSteps = steps;
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
float motorTorqueConstant = 0.00531*810;

int pollingRatio = 20;              //Refresh time of the main loop expressed in millinseconds

char cmd;

volatile unsigned long previousTime;
volatile unsigned long previousStepTime;

float km = 1;
float ks = 40;
float bm = 1;
float bs = 4;
float ROMratio = 5.33;
float masterForce;
float slaveForce;
float scale = 1;
float targetSpeed;
int kp = 200;
float lastPositionDifference = 0;

void setup()
{
  noInterrupts();

  initialiseDCDriver();
  initialiseStepperDriver();
  initialiseEncoder1();
  initialiseEncoder2();
  initialiseForceTransducer();
  initialiseGcodeIntrerpreter();

  Ticks2 = 0;
  previousTime = millis();
  previousStepTime = millis();
  interrupts();

  moveForward();
  //moveBackward();
  MaxCurrent = 100;
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= pollingRatio)  //execute the following code every every 2 milliseconds
  {
    
    /*previousTime = currentTime;
    updateSpeed1();
    updateAcceleration1();
    updateSpeed2();
    updateAcceleration2();
    
    float positionDifference = float(Ticks2-ROMratio*Ticks1)*PI/512;
    float speedDifference = (positionDifference-lastPositionDifference)/pollingRatio;
    lastPositionDifference = positionDifference;
    masterForce = -(km*(positionDifference)+bm*(speedDifference));
    slaveForce = (ks*(positionDifference)+bs*(speedDifference));
    if (slaveForce>0){
      ForwardDC();
    }
    else{
      BackwardDC();
    }
    if (masterForce>0){
      moveForward();
    }
    else{
      moveBackward();
    }
    float currentTarget = slaveForce/motorTorqueConstant;
    float controlSignal = abs(currentTarget/0.003);
    setCurrentDC(static_cast<int>(controlSignal));
    MaxCurrent = 1024 * int(round(masterForce)) / 0.9;
    Serial.printf("%d , %f \n",MaxCurrent, positionDifference);*/
    //Serial.printf("%d, %f, %f, %f, %f, %f, %f\n",Ticks2 , Ticks1*ROMratio, positionDifference , speedDifference , slaveForce , currentTarget ,   controlSignal );
    microstep();
    //Serial.printf("%d, %d\n",Ticks2, steps );
    
    /*ForwardDC();
    setCurrentDC(300);
    Serial.printf("%d, %d \n",Ticks1);*/
    
    /*int voltageRead = analogRead(A14);
    ForwardDC();
    setCurrentDC(500);
    Serial.printf("%d, %d, %f \n",Ticks1, voltageRead, stepperSpeed1);*/
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



