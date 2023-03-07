#include "motor.h"

#include <Servo.h> // Includes the library Servo motor to program the servo motor.

Servo myservo; // Creates servo object to control a servo.

#define IR 9 //Pin al que va conectado nuestro receptor de infrarrojos. En mi caso CHQ1838

long duracion[32]; 
int x=0; 
byte bits[32]; 
int pulso_comienzo; 
int codigo_tecla=0; 
int Pin=A0;
int MotorA=7; // Motor A of the car connected to pin 7.
int MotorB=8;  // Motor B of the car connected to pin 8.
int PWMA=5; // PWMA (Pulse With Modulation A) connected to pin 5 .
int PWMB=6; // PWMB (Pulse With Modulation B) connected to pin 6.
int Speed=127; // Stores the values of the speed, inicially it is 255 (Max speed).
int Low_Speed=50; // The car will run in a low speed (100) to give time to the program to work properly.
int Medium_Speed=100; // The car will run in a medium speed (100) to give time to the program to work properly.
 //4 7segment:
 int clearPin = A1; //Arduino pin 5 connected to Pin 10, SRCLR(Clear/Reset) of 74HC595
int serialData = 3;  //Arduino pin 6 connected to Pin 14, SER(serial input) of 74HC595
int shiftClock = 4;  //Arduino pin 7 connected to Pin 11, SRCLK(shift clock) of 74HC595
int latchClock = 2;  //Arduino pin 8 connected to Pin 12, RCLK(storage/latch clock) of 74HC595 ]
int D1=A4; //Digit 1 to pin 13
int D2=12; //Digit 2 to pin 12
int D3=11; //Digit 3 to pin 11
int D4=10; //Digit 4 to pin 10

int zero=63;
int one=6;
int two=91;
int three=79;
int four=102;
int five=109;
int six=125;
int seven=7;
int eight=127;
int nine=111;

int zerodp=63+128;
int onedp=6+128;
int twodp=91+128;
int threedp=79+128;
int fourdp=102+128;
int fivedp=109+128;
int sixdp=125+128;
int sevendp=7+128;
int eightdp=127+128;
int ninedp=111+128;

int none=0;

motor Motor(Pin, MotorA, PWMA, MotorB, PWMB);

void setup() {
  // put your setup code here, to run once:
Motor.begin();

pinMode(clearPin, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(serialData, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(clearPin, 0); //Pin is active-low, this clears the shift register
  digitalWrite(clearPin, 255); //Clear pin is inactive
  myservo.attach(13); // Sets the pin of the servo motor.
Serial.begin(9600); // Initialize the serial monitor.
}

void loop() {
  // put your main code here, to run repeatedly:

  Number_to_display(two, zero, two, three);

  if(digitalRead(IR)==0) //Esperamos que se pulse una tecla
  {  
    lecturaCodigoIr(); //Funcion que lee la tecla pulsada y la almacena en la variable (codigo_tecla)
    //Accion a realizar segun la tecla pulsada. 
    switch(codigo_tecla) 
    {
      case 25:
        Serial.println("Adelante");
        Motor.forward(Speed);
        myservo.write(30);
        break;
      case 9:
        Serial.println("Izquierda");
        Motor.left(Speed);
        myservo.write(150);
        break;
      case 1:
        Serial.println("Stop");
        Motor.Stop();
        myservo.write(90); 
        break;
      case 49:
        Serial.println("Derecha");
        Motor.right(Speed);
        myservo.write(30);
        break;
      case 42:
        Serial.println("Atras");
        Motor.backward(Speed);
        myservo.write(150);
        break;
      case 12:
        Serial.println("UNO");
        Speed=127; 
        break;
      case 6:
        Serial.println("DOS");
        Speed=255;
        break;
    }
  }
}
void lecturaCodigoIr() 
{
  //PASO 1: DETECCION DEL PULSO DE INICIO DE SECUENCIA (4,5mS)
  pulso_comienzo=pulseIn(IR, HIGH);
  if(pulso_comienzo>4000 && pulso_comienzo<5000) //...comprobamos si es el pulso de comienzo de 4,5mS (inicio de secuencia)
  {
    //PASO 2: CRONOMETRAJE DE TIEMPOS DE CADA PULSO(uS)
    for(x=1; x<=32; x++) 
    {
      duracion[x]=pulseIn(IR, HIGH); //Duracion de cada pulso (uS)
    }
    //PASO 3: SEGUN EL TIEMPO DE CADA PULSO, DETERMINAMOS SI ES UN 0 O UN 1 LOGICO (Ver protocolo NEC)
    for(x=1; x<=32; x++) 
    {
      if(duracion[x]>500 && duracion[x]<700) //Si el pulso dura entre 500 y 700uS...
      {  
        bits[x]=0; //... es un 0 logico
      }
      if(duracion[x]>1500 && duracion[x]<1750) //Si el pulso dura entre 1500 y 1750uS
      {
        bits[x]=1; //... es un 1 logico
      }
    }      
    //PASO 4: CONVERSION DEL ARRAY BINARIO A VARIABLE DECIMAL. 
    //Puesto que muchos de los bits se repiten en todas las teclas, omitimos dichos bits y 
    //nos quedamos con los bits 17 al 21 y el 23 (6 bits). Suficientes para distinguir todas las teclas.
    //Estos 6 bits los convertimos a decimal con el metodo de Potencias de 2. Y el resultado lo almacenamos
    //en la variable codigo_tecla.
    codigo_tecla=0; //Reseteamos la ultima tecla pulsada
    if(bits[17]==1)
    {
      codigo_tecla=codigo_tecla+32; //2^6
    }
    if(bits[18]==1)
    {
      codigo_tecla=codigo_tecla+16; //2^5
    }
    if(bits[19]==1)
    {
      codigo_tecla=codigo_tecla+8; //2^4
    }
    if(bits[20]==1)
    {
      codigo_tecla=codigo_tecla+4; //2^3
    }
    if(bits[21]==1)
    {
      codigo_tecla=codigo_tecla+2; //2^2
    }
    if(bits[23]==1)
    {
      codigo_tecla=codigo_tecla+1; //2^1
    }
  }
  delay(180); //retardo para que no se produzcan "rebotes" y no lea dos pulsaciones de la misma tecla
}
void Number_to_display(int c, int b, int d, int a) {
 First_digit(c);
 delay(5);
 Second_digit(b);
 delay(5);
 Third_digit(d);
 delay(5);
 Fourth_digit(a);
 delay(5);
}
void First_digit(int x) {
  digitalWrite(latchClock, 0);    
     digitalWrite(D1, 0); 
     digitalWrite(D2, 1); 
     digitalWrite(D3, 1); 
     digitalWrite(D4, 1); 
          // take the latchClock low so 
          // the LEDs don't change while you're sending in bits:
   shiftOut(serialData, shiftClock, MSBFIRST, x);      // shift out the bits
   digitalWrite(latchClock, 1); 
}
void Second_digit(int x) {
  digitalWrite(latchClock, 0);    
     digitalWrite(D1, 255); 
     digitalWrite(D2, 0); 
     digitalWrite(D3, 1); 
     digitalWrite(D4, 1); 
          // take the latchClock low so 
          // the LEDs don't change while you're sending in bits:
   shiftOut(serialData, shiftClock, MSBFIRST, x);      // shift out the bits
   digitalWrite(latchClock, 1);    
}
void Third_digit(int x) {
  digitalWrite(latchClock, 0);    
     digitalWrite(D1, 255); 
     digitalWrite(D2, 1); 
     digitalWrite(D3, 0); 
     digitalWrite(D4, 1); 
          // take the latchClock low so 
          // the LEDs don't change while you're sending in bits:
   shiftOut(serialData, shiftClock, MSBFIRST, x);      // shift out the bits
   digitalWrite(latchClock, 255); 
}
void Fourth_digit(int x) {
  digitalWrite(latchClock, 0);    
     digitalWrite(D1, 255); 
     digitalWrite(D2, 1); 
     digitalWrite(D3, 1); 
     digitalWrite(D4, 0); 
          // take the latchClock low so 
          // the LEDs don't change while you're sending in bits:
   shiftOut(serialData, shiftClock, MSBFIRST, x);      // shift out the bits
   digitalWrite(latchClock, 1);    
}
