/*========================================================
   Irene Alvarado
   Gadgets and Sensors

   Homework 1
   Build a simple device with your Arduino which flashes four LEDs. Turn the first LED on for
   2 seconds, then the second for 1 second, the third for a ½ second, and then the fourth for
   a ¼ second. Then flash the four in some pattern of your choosing. Wait ½ second, and
   then repeat.
   // Instructions: https://www.arduino.cc/en/Tutorial/RowColumnScanning
   // Resources:
   http://playground.arduino.cc/Code/Timer
   ========================================================*/

#include "Timer.h"

Timer t;
int letter = 0;

// 2-dimensional array of row pin numbers:
const int row[8] = {
  7, 4, 9, 3, 14, 10, 16, 11
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  18, 17, 13, 8, 12, 6, 5, 15
};

int O[8][8] = {
  {0, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 0, 0, 1, 1, 1},
  {1, 1, 0, 0, 0, 0, 1, 1},
  {1, 1, 0, 0, 0, 0, 1, 1},
  {1, 1, 0, 0, 0, 0, 1, 1},
  {1, 1, 0, 0, 0, 0, 1, 1},
  {1, 1, 1, 0, 0, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0}
};

int K[8][8] = {
  {0, 1, 1, 0, 0, 0, 1, 1},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 0, 0, 0},
  {0, 1, 1, 0, 1, 1, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 1, 1},
  {0, 1, 1, 0, 0, 0, 0, 1}
};


// 2-dimensional array of pixels:
int pixels[8][8] = {
  {1, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

// cursor position:
//int x = 5;
//int y = 5;

void setup() {
  Serial.begin(9600);

  // initialize the I/O pins as outputs
  // iterate over the pins:
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(col[thisPin], HIGH);
  }

  t.every(2000, flipLetter);
}

//  digitalWrite(3, LOW); // ROW4
//  digitalWrite(4, LOW); //  ROW 2
//  digitalWrite(5, LOW);  // COL 7
//  digitalWrite(6, LOW); //  COL 6
//  digitalWrite(7, LOW); // ROW1
//  digitalWrite(8, LOW); // COL 4
//  digitalWrite(9, LOW); //  ROW3
//  digitalWrite(10, LOW); //  ROW6
//  digitalWrite(11, LOW); //  ROW8
//  digitalWrite(12, LOW); // COL 5
//  digitalWrite(13, LOW); // COL 3
//  digitalWrite(A0, LOW); //  ROW5 // 14
//  digitalWrite(A1, LOW); // COL 8 // 15
//  digitalWrite(A2, HIGH); // ROW7 // 16
//  digitalWrite(A3, LOW); // COL 2 //17
//  digitalWrite(A4, HIGH); //  COL 1 // 18

void loop() {
  // Update the timer
  t.update();

  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;

    int thisPixel;
      if(letter) {
        thisPixel = O[thisRow][thisCol];
      }
      else {
         thisPixel = K[thisRow][thisCol];

      }
      
      thisPixel = !thisPixel; // EXTRA DELETE
      // when the row is HIGH and the col is LOW,
      // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
      // turn the pixel off:
      if (thisPixel == LOW) {
        //        Serial.println(LOW);
        digitalWrite(col[thisCol], HIGH);
      }
    }
    // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }


}

/*
  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
  // take the row pin (anode) high:
  digitalWrite(row[thisRow], HIGH);

  for (int thisCol = 0; thisCol < 8; thisCol++) {
  digitalWrite(col[thisCol], HIGH);

  //      Serial.print( "Col: ");
  //           Serial.println(thisCol);

  if (H[thisRow][thisCol] == 1) {
  //    Serial.print( "Row: ");
  //           Serial.print(thisRow);
  //
  //           Serial.print( "Col: ");
  //           Serial.println(thisCol);
     digitalWrite(col[thisCol], LOW);
     digitalWrite(row[thisRow], LOW);
  }

  }

  }
*/



//    digitalWrite(3, LOW); // ROW4
//  digitalWrite(4, LOW); //  ROW 2
//  digitalWrite(5, HIGH);  // COL 7
//  digitalWrite(6, HIGH); //  COL 6
//  digitalWrite(7, LOW); // ROW1
//  digitalWrite(8, HIGH); // COL 4
//  digitalWrite(9, HIGH); //  ROW3 // this is on HIGH
//  digitalWrite(10, LOW); //  ROW6
//  digitalWrite(11, LOW); //  ROW8
//  digitalWrite(12, HIGH); // COL 5
//  digitalWrite(13, HIGH); // COL 3
//  digitalWrite(A0, LOW); //  ROW5 // 14
//  digitalWrite(A1, LOW); // COL 8 // 15
//  digitalWrite(A2, HIGH); // ROW7 // 16 // this is on high
//  digitalWrite(A3, LOW); // COL 2 //17
//  digitalWrite(A4, LOW); //  COL 1 // 18

void flipLetter() {
//  Serial.println("Flipping letter");

  letter = !letter;
}

