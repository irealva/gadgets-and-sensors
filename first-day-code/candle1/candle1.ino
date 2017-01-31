/*========================================================*/
/*
  LED Candle Demo v0.2b (Non-Interactive Version)
  by Scott Hudson, HCI Institute, CMU 1/10
  
  This program provides a demo of basic techniques (push button input and
  driving some LEDs) in the form of a simulated candle created with an RGB
  LED.  
  
  Hardware
  This code assumes a push button (normally open) switch [not used here] and three LEDs or
  a combined RBG LED.  The switch and each of the LEDs should be attached to
  a separate digital I/O pin (as indicated in the constants below).  The LEDs 
  are assumed to be connected as common cathode attached to ground and should should
  each have a current limiting resistor (probably in the 200-500 ohm range for 5v 
  hardware).  The switch is assumed to have a pull-down resistor (so is high when 
  depressed and low when released).  
  
  Operation
  [This simplified version of the program does not yet use the switch, see the full 
  interactive version for that.]  After an RGB startup signal, the candle flickers in 
  a fixed yellow-white color until reset or power off.
  
  Revisions
  1/10  Initial version v0.1a
  1/10  Split into 3 progressively more complete versions v0.2a 
  1/17  Change pin constants for new part pinout v0.2b
*/
/*========================================================*/

/*------- Hardware configuration -------*/
const int  switchPin = 5;        // pin with switch attached [IGNORED HERE]
const int  redPin = 4;           // pin red LED is attached to
const int  greenPin = 2;         // pin for green LED
const int  bluePin = 3;          // pin for blue LED
const byte debugPin = 13;        // pin that we put debug output on (set to 255 to disable)
                                 // (most Arduino's have a built in LED on pin 13...)

/*-------------------------------------------*/
/* Flash the debug LED for the given time in msec.  The LED is on for flashMSec then held
   off for the same amount of time (so this routine takes 2*flashMSec total).
 */
void dbgFlash(int flashMSec) {
  if (debugPin != 255) {
    digitalWrite(debugPin,HIGH); delay(flashMSec); 
    digitalWrite(debugPin,LOW); delay(flashMSec);
  }
}
  
/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  // establish direction of pins we are using for LEDs 
  pinMode(redPin, OUTPUT); 
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT);
  
  // drive the RGB LEDs in sequence so we know they are alive and hooked up right
  if (debugPin != 255) {
    pinMode(debugPin, OUTPUT);
    digitalWrite(debugPin,HIGH); delay(250); digitalWrite(debugPin,LOW);
    digitalWrite(redPin,HIGH); delay(250); digitalWrite(redPin,LOW);
    digitalWrite(greenPin,HIGH); delay(250); digitalWrite(greenPin,LOW);
    digitalWrite(bluePin,HIGH); delay(250); digitalWrite(bluePin,LOW);
  }
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  // do a flicker segment...
 
  // Pick a random color with equal red and green values (red+green = yellow) and smaller random 
  // amount of blue.  That will give a color somewhere between yellow and white in hue.
  byte redV, greenV, blueV;
  redV = greenV = (byte)random(127,255);  
  blueV = (byte)random(0,64); 
 
  // Pick a random duration for the flicker segment (in msec)
  int flickDur = (int)random(50,100); 
  
 // loop to continue lighting for the selected duration
  unsigned long startTime = millis();  
  while (millis() - startTime < flickDur) {
    
    // turn all the non-zero LEDs on
    if (redV != 0) digitalWrite(redPin, HIGH);
    if (greenV != 0) digitalWrite(greenPin, HIGH);
    if (blueV != 0) digitalWrite(bluePin, HIGH);
    
    // count out 255 units of LED intensity.  We will leave each LED on for 
    // some percentage of those as specified by its 0..255 intensity value.
    for (int cnt = 0; cnt < 255; cnt++) {
      // if we are at the setting for a particular color, turn it off
      if (cnt >= redV) digitalWrite(redPin, LOW);
      if (cnt >= greenV) digitalWrite(greenPin, LOW);
      if (cnt >= blueV) digitalWrite(bluePin, LOW);
    } // end for
  } // end while
  
  // turn off all LEDs
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,LOW);
  
}  // end loop()
