#include "Button.h"
Button::Button(int pin){
int state;
this->pin=pin;
this->state=state;
}
void Button::beging(){
pinMode(pin, INPUT_PULLUP);
}
int Button::read(){
state=digitalRead(pin);
return state;
}