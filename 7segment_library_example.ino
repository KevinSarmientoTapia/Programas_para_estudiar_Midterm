#include <segment.h>
segment Segment(2, 3, 4, 5, 6, 7, 8);
void setup() {
  // put your setup code here, to run once:
Segment.beging();
}

void loop() {
  // put your main code here, to run repeatedly:
Segment.zero();
delay(500);
Segment.one();
delay(500);
Segment.two();
delay(500);
}