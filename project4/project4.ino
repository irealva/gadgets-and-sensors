///*========================================================
//   Irene Alvarado
//   Gadgets and Sensors
//
//   Project 4:
//Build a simple device which uses four or more LEDs as a simple magnitude display
//indicating either light level (sensed by a photocell) or temperature (sensed by a
//thermistor). That is if the light (or temperature) is “low” no LEDs will be lit, and as the light
//(or temperature) increases more LEDs should be turned on. For the light sensor version,
//you should tune the response of your device to demo well in a typical classroom by
//shadowing/covering it with your hand. For the temperature sensor version, you should
//tune the response of your device to demo well in response to typical ambient room
//temperature vs. human skin temperature.
//  ========================================================*/
//
///*------- Hardware configuration -------*/
const int  sensorPin = 14;        //  Analog pin for potentiometer

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
  pinMode(sensorPin, INPUT);
}

void loop() {
  // read the state of the potentiometer
  int photocellReading = analogRead(sensorPin);

  // LED gets brighter the darker it is at the sensor
  // that means we have to -invert- the reading from 0-1023 back to 1023-0
  //  photocellReading = 1023 - photocellReading;

  //now we have to map 0-1023 to 0-255 since thats the range analogWrite uses
  int LEDbrightness = map(photocellReading, 0, 1023, 0, 255);

//Recalibrate for my specific room
 LEDbrightness = map(LEDbrightness, 140, 220, 0, 255);
 
  Serial.println(LEDbrightness);

  if (LEDbrightness < 50) {
    digitalWrite(firstPin, LOW);
    digitalWrite(secondPin, LOW);
    digitalWrite(thirdPin, LOW);
    digitalWrite(fourthPin, LOW);
  }
  else if (50 <= LEDbrightness && LEDbrightness < 100) {
    Serial.println("case 1");
    digitalWrite(firstPin, HIGH);
    digitalWrite(secondPin, LOW);
    digitalWrite(thirdPin, LOW);
    digitalWrite(fourthPin, LOW);
  }
  else if (100 <= LEDbrightness && LEDbrightness < 150) {
    digitalWrite(firstPin, HIGH);
    digitalWrite(secondPin, HIGH);
    digitalWrite(thirdPin, LOW);
    digitalWrite(fourthPin, LOW);
  }
  else if (150 <= LEDbrightness && LEDbrightness < 200) {
    digitalWrite(firstPin, HIGH);
    digitalWrite(secondPin, HIGH);
    digitalWrite(thirdPin, HIGH);
    digitalWrite(fourthPin, LOW);
  }
  else {
    digitalWrite(firstPin, HIGH);
    digitalWrite(secondPin, HIGH);
    digitalWrite(thirdPin, HIGH);
    digitalWrite(fourthPin, HIGH);
  }
}

