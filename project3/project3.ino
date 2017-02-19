///*========================================================
//   Irene Alvarado
//   Gadgets and Sensors
//
//   Project 3:
//   Build a simple device which lights four LEDs one after the other and controls the speed at
//  which the sequence displays with a potentiometer. When the potentiometer is turned fully
//  counter clockwise the LED sequence should proceed slowly. When the potentiometer is
//  turned in the clockwise direction it should proceed faster and faster.
//  ========================================================*/
//
///*------- Hardware configuration -------*/
const int  potenPin = 14;        //  Analog pin for potentiometer

const int  firstPin = 2;           // pin for first light, 2000 s
const int  secondPin = 3;         // pin for second light 1000 s
const int  thirdPin = 4;          // pin for third light 500 s
const int  fourthPin = 5;          // pin for third light 250 s
const byte debugPin = 13;        // pin that we put debug output on (set to 255 to disable)
// (most Arduino's have a built in LED on pin 13...)

//corresponding to firstPin, secondPin, thirdPin, fourthPin. Loop uses led array for lookup of what LED to turn on
int leds[4] = {2, 3, 4, 5};

/*------- Global system state -------*/
int currentDirection = 1; // direction of LED lighting
int currentLoop = 0; // To track from 0-3 in loop (aka. for 4 LED lights)

// Should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time LED was updated
long interval = 1000; // interval at which to blink (milliseconds)
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
  pinMode(potenPin, INPUT);
}

void loop() {
  // read the state of the potentiometer
  int potentiometer = analogRead(potenPin);

  int val = map(potentiometer, 0, 1023, 300, 3000);
  interval = val;
  Serial.println(val);

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

    // Figure out what our current and previous LEDs are
    int curLED = leds[currentLoop];
    int mod = (((currentLoop - 1) % 4) + 4) % 4;
    int prevLED = leds[mod];

    //Update the LEDs
    digitalWrite(curLED, HIGH);
    digitalWrite(prevLED, LOW);
    laston = curLED;

    // Update where we are in this loop 0-3 or going from 3-0
    currentLoop += 1;

    // Make sure we update currentLoop if it goes over 3 or under 0.
    if (currentLoop > 3) {
      currentLoop = 0;
    }

  }
}

