/*========================================================
   Irene Alvarado
   Gadgets and Sensors
   Project 2: Make 4 LEDs light up in opposite directions when 1 button is pressed.
  ========================================================*/

/*------- Hardware configuration -------*/
const int  switchPin = 6;        // pin with switch attached
const int  firstPin = 2;           // pin for first light, 2000 s
const int  secondPin = 3;         // pin for second light 1000 s
const int  thirdPin = 4;          // pin for third light 500 s
const int  fourthPin = 5;          // pin for third light 250 s
const byte debugPin = 13;        // pin that we put debug output on (set to 255 to disable)
// (most Arduino's have a built in LED on pin 13...)

//corresponding to firstPin, secondPin, thirdPin, fourthPin. Loop uses led array for lookup of what LED to turn on
int leds[4] = {2, 3, 4, 5};

/*------- Data structures for system state -------*/

// Structure to track and debounce the state of a push button switch
// Written by Scott Hudson
typedef struct switchTracker {
  int lastReading;       // last raw value read
  long lastChangeTime;   // last time the raw value changed
  byte pin;              // the pin this is tracking changes on
  byte switchState;      // debounced state of the switch
} switchTrack;

/*------- Global system state -------*/
switchTrack switchInput; // debounce information for our switch
int direction = 0; // direction of LED lighting
int currentLoop = 0; // To track from 0-3 in loop (aka. for 4 LED lights)


/*-------------------------------------------*/
/* Initializization code (run once via call from Arduino framework) */
void setup() {
  Serial.begin(9600);

  // Set up debounce tracker on our switch input pin (sets mode to INPUT)
  initSwitchTrack(switchInput, switchPin);

  // Establish direction of pins we are using to drive LEDs
  pinMode(firstPin, OUTPUT);
  pinMode(secondPin, OUTPUT);
  pinMode(thirdPin, OUTPUT);
  pinMode(fourthPin, OUTPUT);
  pinMode(debugPin, OUTPUT);
}

// Should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0; // will store last time LED was updated
const long interval = 1000; // interval at which to blink (milliseconds)
int laston = 0; // Last LED to be on

void loop() {
  int currentDirection = run_switch();

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

/* Called on every loop to see if the switch has been pressed
 */
int run_switch(void) {
  if (switchChange(switchInput) && switchInput.switchState == 1 /* pressed */) {
    direction = !direction;
    //    Serial.print(direction);
    //    Serial.println("pressed");
    return direction;
  }

  return direction;
}

/* Fill in a switchTrack structure to start tracking/debouncing a switch
   on the given pin.
   Written by Scott Hudson
*/
void initSwitchTrack(struct switchTracker &sw, int swPin) {
  pinMode(swPin, INPUT);
  sw.lastReading = digitalRead(swPin);
  sw.lastChangeTime = millis();
  sw.pin = swPin;
  sw.switchState = sw.lastReading;
}

/* Using a time based debounce, test whether a switch should be considered to have
   changed state since the last call to this routine for the switch, and track the
   current state of the switch in the given switch tracking structure (sw).  The switch
   will be consided to be in a new state only after it has held that state for debounceTime msec
   or longer.  sw.switchState will be set to 1 when the switch should be considered pressed
   and 0 when it should be considered released.  This routine will return true when the
   switch is in a new state compared to the last call to this routine, false otherwise.

   Note: this routine must be called frequently to operate correctly.
   Note: this code is here to make the demo a little more stand alone (nothing to import),
         but in other cases you might want to consider using the code from Bounce.h instead.
   Written by Scott Hudson
*/
boolean switchChange(struct switchTracker &sw) {
  // switch must stay stable this long (in msec) to register
  const long debounceTime = 100;

  // default to no change until we find out otherwise
  boolean result = false;

  // get the current raw reading from the switch
  int reading = digitalRead(sw.pin);
  // Serial.println(reading);

  // if the raw reading has changed (by noise or actual press/release) reset change time to now
  if (reading != sw.lastReading) sw.lastChangeTime = millis();
  sw.lastReading = reading;

  // if time since the last change is longer than the required dwell
  if ((millis() - sw.lastChangeTime) > debounceTime) {
    // note whether we are changing
    result = (reading != sw.switchState);
    // in any case the value has been stable and so the reported state
    // should now match the current raw reading
    sw.switchState = reading;
  }
  return result;
}


