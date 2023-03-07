#include "motor.h"

motor::motor(int Pin, int MotorA, int PWMA, int MotorB, int PWMB){
this->Pin=Pin;
this->MotorA=MotorA;
this->PWMA=PWMA;
this->MotorB=MotorB;
this->PWMB=PWMB;
}

void motor::begin(){
pinMode(MotorA, OUTPUT); // Pin Motor A set as output.
pinMode(MotorB, OUTPUT); // Pin Motor B set as output.
pinMode(PWMA, OUTPUT); // Pin PWMA set as output.
pinMode(PWMB, OUTPUT); // Pin PWMB set as output.
pinMode(Pin, OUTPUT); // Pin 3 set as output.  
}

void motor::forward(int x){ // Function to called "forward".
  /* The function "fordward" makes the car go forward by using this methode:
      1. The Motor A has to go forward, so we give high voltage (1) to its pin 
      2. The Motor B also has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */  
  digitalWrite(Pin, 255);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, x);
}

void motor::backward(int x){ // Function called "backward".
  /* The function "backward" makes the car go backwards by using this methode:
      1. The Motor A has to go backward, so we give low voltage (0) to its pin 
      2. The Motor B also has to go backward, so we give low voltage (0) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(Pin, 255);
  digitalWrite(MotorA,0);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 0);
  analogWrite(PWMB, x);
}

void motor::left(int x){ // Function called "left".
  /* The function "left" makes the car turn to the left by using this methode:
      1. The Motor A has to go forward, so we give high voltage (1) to its pin 
      2. The Motor B has to go backwards, so we give low voltage (0) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(Pin, 255);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 0);
  analogWrite(PWMB, x);
}

void motor::right(int x){ // Function called "right".
  /* The function "right" makes the car turn to the right by using this methode:
      1. The Motor A has to go backward, so we give low voltage (0) to its pin 
      2. The Motor B has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will be the speed of the car we assign.
  */
  digitalWrite(Pin, 255);
  digitalWrite(MotorA,0);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, x);
}

void motor::Stop(){ // Function called "stop".
  /* The function "stop" stops the car by using this methode:
      1. The Motor A has to go fordward, so we give high voltage (1) to its pin 
      2. The Motor B also has to go forward, so we give high voltage (1) to its pin. 
      3. The pin 3 will always have high voltage (1).
      4. The pins for PWMA and PWMB will have no speed as we want the car to stop.
  */
  digitalWrite(Pin, 255);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, 0);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, 0);
}
void motor::forward_left(int x){
  digitalWrite(Pin, 255);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, x);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, x/2);
}
void motor::forward_right(int x){
  digitalWrite(Pin, 255);
  digitalWrite(MotorA,1);
  analogWrite(PWMA, x/2);
  digitalWrite(MotorB, 1);
  analogWrite(PWMB, x);
}