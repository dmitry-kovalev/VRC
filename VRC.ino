#include "AVRPort23.h"
#include "UnoJoy.h"

#define CHAN1 D,2
#define _INT1 0
#define CHAN2 D,3
#define _INT2 1

dataForController_t controllerData;

void setup()
{
  portMode(CHAN1, INPUT, HIGH);
  portMode(CHAN2, INPUT, HIGH);
    
  attachInterrupt(_INT1, isr1, CHANGE);
  attachInterrupt(_INT2, isr2, CHANGE);

  setupUnoJoy();
  controllerData = getControllerData();
}

volatile unsigned long Time[4];
volatile unsigned int Value[4];
volatile bool ValChanged[4];
unsigned int NewValue[4];


void loop()
{   
  if (ValChanged[0])
  {
    NewValue[0] = (NewValue[0]+Value[0])/2;
    controllerData.leftStickY = map(NewValue[0], 1000, 2000, 0, 255);
    ValChanged[0] = false;
  }

  if (ValChanged[1])
  {
    NewValue[1] = (NewValue[1]+Value[1])/2;
    controllerData.leftStickX = 255 - map(NewValue[1], 1000, 2000, 0, 255);
    ValChanged[1] = false;
  }  
  setControllerData(controllerData);
  delay(8);
}

dataForController_t getControllerData(void){
  // Set up a place for our controller data
  dataForController_t controllerData;
  // Since our buttons are all held high and
  //  pulled low when pressed, we use the "!"
  //  operator to invert the readings from the pins
  controllerData.triangleOn = 0;//!digitalRead(2);
  controllerData.circleOn = 0;//!digitalRead(3);
  controllerData.squareOn = 0;//!digitalRead(4);
  controllerData.crossOn = 0;//!digitalRead(5);
  controllerData.dpadUpOn = 0;//!digitalRead(6);
  controllerData.dpadDownOn = 0;//!digitalRead(7);
  controllerData.dpadLeftOn = 0;//!digitalRead(8);
  controllerData.dpadRightOn = 0;//!digitalRead(9);
  controllerData.r2On = 0;//!digitalRead(10);
  controllerData.r3On = 0;//!digitalRead(11);
  controllerData.selectOn = 0;//!digitalRead(12);
  controllerData.startOn = 0;//!digitalRead(A4);
  
  // Fill up the other buttons with zeroes - otherwise they
  //  tend to be filled with random memory junk.
  // And we take the analog stick data from
  //  the analog pins.
  controllerData.l1On = 0;
  controllerData.l2On = 0;
  controllerData.l3On = 0;
  controllerData.r1On = 0;
  controllerData.homeOn = 0;//!digitalRead(A5);
 // controllerData.dpadLeftOn = 0;
  //controllerData.dpadUpOn = 0;
  //controllerData.dpadRightOn = 0;
  //controllerData.dpadDownOn = 0;
  
  controllerData.leftStickX = 128;
  controllerData.leftStickY = 128;
  controllerData.rightStickX = 128;
  controllerData.rightStickY = 128;
  // And return the data!
  return controllerData;
}

void isr1()
{
  if (portRead(CHAN1)) Time[0] = micros();
  else if (micros() > Time[0])
  {
    Value[0] = (Value[0]+(micros()-Time[0]))/2;
    ValChanged[0] = true;
  }
}

void isr2()
{
  if (portRead(CHAN2)) Time[1] = micros();
  else if (micros() > Time[1])
  {
    Value[1] = (Value[1]+(micros()-Time[1]))/2;
    ValChanged[1] = true;
  }
}
