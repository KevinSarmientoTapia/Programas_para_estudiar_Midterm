#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

class Button{

private:
int pin;
int state;

public:
Button(){};//default constructor
Button(int pin);//constructor 
void beging();//inizialize the pin
int read();//reads pin value
};
#endif