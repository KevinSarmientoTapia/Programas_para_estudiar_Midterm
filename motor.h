#ifndef MOTOR_H
#define MOTOR_H
#include <Arduino.h>

class motor{
private:
int Pin;
int MotorA; // Motor A of the car connected to pin 7.
int MotorB;  // Motor B of the car connected to pin 8.
int PWMA; // PWMA (Pulse With Modulation A) connected to pin 5 .
int PWMB; // PWMB (Pulse With Modulation B) connected to pin 6.

public:
motor(){};//default constructor
motor(int Pin, int MotorA, int PWMA, int MotorB, int PWMB);//constructor
void begin();//initialize pins for motors
void forward(int x);//go fordward
void backward(int x);//go backward
void left(int x);//turn left
void right(int x);//turn right
void Stop();//stop
void forward_left(int x);//keep going forward turning to the left
void forward_right(int x);//keep going forward turning to the right
};

#endif