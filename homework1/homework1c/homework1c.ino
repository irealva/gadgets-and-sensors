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


int size_pong = 3;
int position1 = 2;
int position2 = 1;

int ball[2] = { 4, 0 } ; // row, column
int directionX = 1;
int directionY = 1;

// 2-dimensional array of pixels:
int pixels[8][8] = {
  {0, 1, 1, 1, 0, 0, 0, 0}, //player2
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0, 0} // player1
};

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

  t.every(400, moveBall);
}

String readString;
int change = 0 ;

void loop() {

  if (Serial.available())
  {
    String serialData = Serial.readString();
    serialData.trim();

    if (serialData[0] == 's') {
      moveRight(1);
    }
    else if (serialData[0] == 'a') {
      moveLeft(1);
    }
    else if (serialData[0] == 'l') {
      moveRight(2);
    }
    else if (serialData[0] == 'k') {
      moveLeft(2);
    }

  }

  // Update the timer
  t.update();

  //  if (change) {
  //    getVirtualBoard();
  //    change = 0;
  //  }

  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;

      int thisPixel;
      thisPixel = pixels[thisRow][thisCol];

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

int prevRow = ball[0] - 1;
int player1[8] = {};
int player2[8] = {};

void moveBall() {
  Serial.println("move ball");

  int ballTemp[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

  //Clear previous row
  memcpy(pixels[prevRow], ballTemp, sizeof(ballTemp));

  int row = ball[0];
  int col = ball[1];

  // ROW DIRECTION
  if (directionY) { // Going towards player 1
    row = row + 1;
    prevRow = row;
  }
  else { // Going towards player2
    row = row - 1;
    prevRow = row;
  }

  // If we reach bottom of 8x8 where player 1 is, turn around
  if (row == 6) {
    directionY = 0;
  }
  // I fwe reach top of 8x8 where player 2 is, turn around
  if (row == 1) {
    directionY = 1;
  }

  // COLUMN DIRECTION
   if (directionX) {
    col = col + 1;
    ballTemp[col] = 1;
  }
  else {
    col = col - 1;
    ballTemp[col] = 1;
  }
  
  if (col == 7) {
    directionX = 0; // Go to the left
  }
  if (col == 0) {
    directionX = 1; // Go to the right
  }
 
  memcpy(pixels[row], ballTemp, sizeof(ballTemp));

  ball[0] = row;
  ball[1] = col;
  Serial.println("Row: " + (String) row + " col: " + (String) col + "\n");
}




void moveRight(int player) {
  if (player == 1) {
    if (position1 != 5) {
      position1 = position1 + 1;

      int playerTemp[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

      for (int i = position1; i < (position1 + size_pong) ; i++) {
        playerTemp[i] = 1;
      }
      memcpy(player1, playerTemp, sizeof(playerTemp));
      memcpy(pixels[7], playerTemp, sizeof(playerTemp));
    }
  }

  if (player == 2) {
    if (position2 != 5) {
      position2 = position2 + 1;

      int playerTemp[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

      for (int i = position2; i < (position2 + size_pong) ; i++) {
        playerTemp[i] = 1;
      }

      memcpy(player2, playerTemp, sizeof(playerTemp));
      memcpy(pixels[0], playerTemp, sizeof(playerTemp));
    }
  }
}


void moveLeft(int player) {
  if (player == 1) {
    if (position1 != 0) {
      position1 = position1 - 1;

      int playerTemp[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

      for (int i = position1; i < (position1 + size_pong) ; i++) {
        playerTemp[i] = 1;
      }

      memcpy(player1, playerTemp, sizeof(playerTemp));
      memcpy(pixels[7], playerTemp, sizeof(playerTemp));
    }
  }

  if (player == 2) {
    if (position2 != 0) {
      position2 = position2 - 1;

      int playerTemp[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

      for (int i = position2; i < (position2 + size_pong) ; i++) {
        playerTemp[i] = 1;
      }

      memcpy(player2, playerTemp, sizeof(playerTemp));
      memcpy(pixels[0], playerTemp, sizeof(playerTemp));
    }
  }
}

//void getVirtualBoard() {
//  memcpy(pixels[7], player1, sizeof(player1));
//}

void printPlayer(int temp[]) {
  String x = "";

  for (int i = 0 ; i < 8 ; i++) {
    x = x + temp[i] + ", " ;
  }

  Serial.println(x);
}
