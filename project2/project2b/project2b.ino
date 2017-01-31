///*========================================================
//   Irene Alvarado
//   Gadgets and Sensors
//
//   Project 2:
//   Build a simple device which lights four LEDs one after the other and controls the direction
//   of lighting with two push button switches. When one button is pressed, the LEDs should
//   light in sequence left to right (and then repeat). When the other is pressed the LEDs
//   should switch directions and light in sequence right to left (and then repeat).
//  ========================================================*/
//
///*------- Hardware configuration -------*/
const int  switchPin1 = 6;        // pin with switch attached
const int switchPin2 = 7;     // the second pin with switch attached

const int  firstPin = 2;           // pin for first light, 2000 s
const int  secondPin = 3;         // pin for second light 1000 s
const int  thirdPin = 4;          // pin for third light 500 s
const int  fourthPin = 5;          // pin for third light 250 s
const byte debugPin = 13;        // pin that we put debug output on (set to 255 to disable)
// (most Arduino's have a built in LED on pin 13...)

//corresponding to firstPin, secondPin, thirdPin, fourthPin. Loop uses led array for lookup of what LED to turn on
int leds[4] = {2, 3, 4, 5};

/*------- Global system state -------*/
int currentDirection = 0; // direction of LED lighting
int currentLoop = 0; // To track from 0-3 in loop (aka. for 4 LED lights)

// Should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 1000; // interval at which to blink (milliseconds)
int laston = 0; // Last LED to be on

/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  Serial.begin(9600);

  // Establish direction of pins we are using to drive LEDs
  pinMode(firstPin, OUTPUT);
  pinMode(secondPin, OUTPUT);
  pinMode(thirdPin, OUTPUT);
  pinMode(fourthPin, OUTPUT);
  pinMode(debugPin, OUTPUT);

  // initialize the pins for the buttons/switches
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
}

void loop() {
  // read the state of the buttons
  int buttonState1 = digitalRead(switchPin1);
  int buttonState2 = digitalRead(switchPin2);

  if (buttonState1) {
    currentDirection = 0;
  }
  if (buttonState2) {
    currentDirection = 1;
  }

  // check to see if it's time to blink the LED; that is, if the
  // difference between the current time and last time you blinked
  // the LED is bigger than the interval at which you want to
  // blink the LED.
  unsigned long currentMillis = millis();

  // We go into if statement every 1 seconds
  if (currentMillis - previousMillis >= interval) {
    digitalWrite(laston, LOW); // Make sure we turn off the last LED that was on

    // save the last time you blinked the LED
    previousMillis = currentMillis;

    if (currentDirection) {
      // Figure out what our current and previous LEDs are
      int curLED = leds[currentLoop];
      int mod = (((currentLoop - 1) % 4) + 4) % 4;
      int prevLED = leds[mod];

      //Update the LEDs
      digitalWrite(curLED, HIGH);
      digitalWrite(prevLED, LOW);
      laston = curLED;
    }
    else {
      int curLED = leds[currentLoop];
      int prevLED = leds[((currentLoop + 1) % 4)];

      //Update the LEDs
      digitalWrite(curLED, HIGH);
      digitalWrite(prevLED, LOW);
      laston = curLED;
    }


    // Update where we are in this loop 0-3 or going from 3-0
    if (currentDirection) {
      currentLoop += 1;
    }
    else {
      currentLoop -= 1;
    }

    // Make sure we update currentLoop if it goes over 3 or under 0.
    if (currentLoop > 3) {
      currentLoop = 0;
    }
    if (currentLoop < 0) {
      currentLoop = 3;
    }
  }
}

