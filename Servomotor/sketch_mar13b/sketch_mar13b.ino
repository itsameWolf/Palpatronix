#include <AccelStepper.h>
#include <MultiStepper.h>
#define CurrentControlA 5
#define CurrentControlB 6



int motorSpeed = 9600; //maximum steps per second (about 3rps / at 16 microsteps)
int motorAccel = 80000; //steps/second/second to accelerate

int motorPin1 = 23;
int motorPin2 = 22;
int motorPin3 = 21;
int motorPin4 = 20;

//set up the accelStepper intance
//the "1" tells it we are using a driver
AccelStepper stepper(4, motorPin1,motorPin2,motorPin3,motorPin4); 



void setup(){
 stepper.setMaxSpeed(motorSpeed);
 stepper.setSpeed(motorSpeed);
 stepper.setAcceleration(motorAccel);
 
 stepper.moveTo(32000); //move 32000 steps (should be 10 rev)
 pinMode(CurrentControlA, OUTPUT);
 pinMode(CurrentControlB, OUTPUT);

  analogWriteFrequency(CurrentControlA, 750000);
  analogWriteFrequency(CurrentControlB, 750000);
  analogWriteResolution(6);

  analogWrite(CurrentControlA, 10);
  analogWrite(CurrentControlB, 10);
}

void loop(){
 
 //if stepper is at desired location
 if (stepper.distanceToGo() == 0){
   //go the other way the same amount of steps  <= "go the other way" sounds like a direction change to me.
   //so if current position is 400 steps out, go position -400
   stepper.moveTo(stepper.currentPosition());  
 }
 

 
 //these must be called as often as possible to ensure smooth operation
 //any delay will cause jerky motion
 stepper.run();
}  
