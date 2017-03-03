/*========================================================
   Irene Alvarado
   Gadgets and Sensors

   Project 1
   A simple game of Pong using na 8x8 LED matrix and an Arduino nano. 
   A ball bounces between two players. Each player is associated to 1 button.
   One button click moves a player to the right, double-clicks move a player to the left. 

   Resources used:
     Tips on how to wire an 8x8 LED matrix: https://www.arduino.cc/en/Tutorial/RowColumnScanning
     A Timer library: http://playground.arduino.cc/Code/Timer
     A Double Click button library:  https://github.com/mathertel/OneButton
   ========================================================*/

#include "Timer.h" // External library
#include <OneButton.h> // External library

// HARDWARE SETUP
// 2-dimensional array of row pin numbers:
const int row[8] = {
  7, 4, 9, 3, 14, 10, 16, 11
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  18, 17, 13, 8, 12, 6, 5, 15
};

// GAME SETUP

Timer t;
Timer tover;

int gameover = 0; // Indicates whether a game is over
int showOverScreen = 0; // Indicates whether we've shown a game over screen

// PLAYER BUTTONS
const int  p1PIN = 2;        // pin with switch attached
const int p2PIN = 19;     // the second pin with switch attached
OneButton p1button(p1PIN, 0);
OneButton p2button(p2PIN, 0);

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

// Screen to show once game is over
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

void setup() {
  Serial.begin(9600);

  // initialize the pins for the buttons/switches
  pinMode(p1PIN, INPUT);
  pinMode(p2PIN, INPUT);
  p1button.attachDoubleClick(doubleclick1);
  p1button.attachClick(oneClick1);
  p2button.attachDoubleClick(doubleclick2);
  p2button.attachClick(oneClick2);

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

  t.every(1000, moveBall); // Move the ball every second
}

// Player 1 click methods
void doubleclick1() {
  moveLeft(1);
}

void oneClick1() {
  moveRight(1);
}

// Player 2 click methods
void doubleclick2() {
  moveLeft(2);
}

void oneClick2() {
  moveRight(2);
}

void loop() {
  // Update the timers
  p1button.tick();
  p2button.tick();
  t.update();

  // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
    // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
    // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
      // get the state of the current pixel;

      int thisPixel;
      thisPixel = pixels[thisRow][thisCol];

      if (showOverScreen) {
        thisPixel = O[thisRow][thisCol];
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

  // CHECK IF GAME IS OVER
  // If game is over and we haven't showed that yet
  if (gameover && showOverScreen == 0) {
    tover.after(4000, gameReset);
    showOverScreen = 1;
  }
  // If we're showing the gameover screen we let the timer for that screen run
  if (gameover && showOverScreen == 1) {
    tover.update();
  }
}

/*
 * Resets the game logic
 */
void gameReset() {
  //  Serial.println("Game reset");
  showOverScreen = 0;
  gameover = 0;
  // Reset the player positions
  position1 = 2;
  position2 = 1;

  // Reset the ball position and direction
  ball[0] = 4 ;
  ball[1] = 0;
  directionX = 1;
  directionY = 1;
}

int prevRow = ball[0] - 1;
int player1[8] = {};
int player2[8] = {};

/*
 * Moves a ball in the Y direction and X direction. 
 */
void moveBall() {
  if (gameover == 0) {

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
      int game = checkIfGameOver(6, col);
      if (game) {
        gameover = 1 ;
        return;
      }

      directionY = 0;
    }
    // If we reach top of 8x8 where player 2 is, turn around
    if (row == 1) {
      int game = checkIfGameOver(1, col);
      if (game) {
        gameover = 1 ;
        return;
      }

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
  }
}

/*
 * Checks if the ball has not bounced off a player given the player's position
 */
int checkIfGameOver(int row, int col) {
  // Check if player 1 lost
  if (row == 6) {
    if (directionX) {
      col = col + 1;
    }
    else {
      col = col - 1;
    }

    if (col < position1 || col > (position1 + 3)) {
      return 1;
    }
    else {
      return 0;
    }
  }

  // Check if player 2 lost
  if (row == 1) {
    if (directionX) {
      col = col + 1;
    }
    else {
      col = col - 1;
    }

    if (col < position2 || col > (position2 + 3)) {
      return 1;
    }
    else {
      return 0;
    }
  }

}

/*
 * Moves a player one step to the right
 */
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

/*
 * Moves a player one step to the left
 */
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
