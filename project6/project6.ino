/*========================================================
   Irene Alvarado
   Gadgets and Sensors

   Project 6:
   Build a device which moves a servo motor under the control of a potentiometer. When the
  potentiometer is turned fully clockwise the servo motor should be turned fully clockwise.
  As the potentiometer is turned counter-clockwise, the servo should track this movement,
  turning counter-clockwise, and when the potentiometer is turned fully counter-clockwise,
  the servo should be turned fully counter-clockwise.
  ========================================================*/

#include <Servo.h>

int potentiometerPin = 17;    // select the input pin for the potentiometer
int servoPin = 3; // Select the pin for the servo motor

int val = 0;       // variable to store the value coming from the sensor

Servo myservo;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);

  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  val = analogRead(potentiometerPin); // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 180, 0);     // scale it to use it with the servo (value between 0 and 180)
  Serial.println(val);
  myservo.write(val);                  // sets the servo position according to the scaled value
  delay(100);                           // waits for the servo to get there

}

