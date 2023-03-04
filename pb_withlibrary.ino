#include "Button.h"
Button PB(2);
void setup() { // void setup is the section of the program that runs once.
  
  PB.beging();
  Serial.begin(9600); // to display values in the serial monitor.

}

void loop() { // Void loop is the section of the program that runs forever.
  Serial.println(PB.read()); // displays the value off the button in the serial monitor.

}