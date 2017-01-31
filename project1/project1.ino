/*========================================================
   Irene Alvarado
   Gadgets and Sensors
   
   Project 1:
   Build a simple device with your Arduino which flashes four LEDs. Turn the first LED on for
   2 seconds, then the second for 1 second, the third for a ½ second, and then the fourth for
   a ¼ second. Then flash the four in some pattern of your choosing. Wait ½ second, and
   then repeat.
   ========================================================*/

/*------- Hardware configuration -------*/
const int  firstPin = 2;           // pin for first light, 2000 s
const int  secondPin = 3;         // pin for second light 1000 s
const int  thirdPin = 4;          // pin for third light 500 s
const int  fourthPin = 5;          // pin for third light 250 s
const byte debugPin = 13;        // pin that we put debug output on (set to 255 to disable)
// (most Arduino's have a built in LED on pin 13...)

/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  Serial.begin(9600);
  // establish direction of pins we are using to drive LEDs
  pinMode(firstPin, OUTPUT);
  pinMode(secondPin, OUTPUT);
  pinMode(thirdPin, OUTPUT);
  pinMode(fourthPin, OUTPUT);
  pinMode(debugPin, OUTPUT);
}

/* Main routine (called repeated by from the Arduino framework) */
void loop() {
  // For this version we just flash the LEDs one after the other...

  // Turn LED on by setting corresponding pin voltage high
  digitalWrite(debugPin, HIGH);
  // Delay here (leaving the LED on) for 250msec (1/4 sec)
  delay(250);
  // Turn it off
  digitalWrite(debugPin, LOW);

  // Do that again for the red, green and blue ones in sequence
  digitalWrite(firstPin, HIGH); delay(2000); digitalWrite(firstPin, LOW);
  digitalWrite(secondPin, HIGH); delay(1000); digitalWrite(secondPin, LOW);
  digitalWrite(thirdPin, HIGH); delay(500); digitalWrite(thirdPin, LOW);
  digitalWrite(fourthPin, HIGH); delay(250); digitalWrite(fourthPin, LOW);


  for (int i = 0; i < 10; i++) {
    if (random(2)) {
      digitalWrite(firstPin, HIGH); delay(random(250, 1000)); digitalWrite(firstPin, LOW);
    }
    if (random(2)) {
      digitalWrite(secondPin, HIGH); delay(random(250, 1000)); digitalWrite(secondPin, LOW);
    }
    if (random(2)) {
      digitalWrite(thirdPin, HIGH); delay(random(250, 1000)); digitalWrite(thirdPin, LOW);
    }
    if (random(2)) {
      digitalWrite(fourthPin, HIGH); delay(random(250, 1000)); digitalWrite(fourthPin, LOW);
    }
  }

  // All LEDs are now off, stay dark for 1/2 sec
  delay(500);
}  // end loop()
