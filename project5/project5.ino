/*========================================================
   Irene Alvarado
   Gadgets and Sensors

   Project 5:
   Build a device which plays three or more tones on a speaker. If you wish to play a short
  tune, the frequency and period table on the back may be helpful.

    Implemented a small part of "High and Dry" by Radiohead

    Resources: Relying heavily (almost all of the codebase) on this code
    made by Tom Igoe
    https://www.arduino.cc/en/Tutorial/toneMelody
  ========================================================*/

#include "pitches.h"

const int speakerPin = 3;

// notes in the melody:
int melody3[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};



// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations3[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};


int melody[] = {
  NOTE_D5, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_A4,
  NOTE_D5, NOTE_B4, NOTE_B4, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_D4,
  0, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS5, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS5, NOTE_E5, NOTE_D5,
  0, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_FS5, 0, NOTE_FS4, NOTE_G4, NOTE_FS4, NOTE_D4
};

float noteDurations[] = {
  4, 4, 4 , 8, 3, 4, 4, 4,
  4, 4, 4 , 8, 3, 4, 4, 4, 4, 2, 1,
  2, 3, 6, 2.5, 0.75, 3, 6, 2.5, 0.65, 8, 4,
  4, 3, 6, 2.5, 0.5, 3, 3, 6, 2.5, 0.5
};

void setup() {

}

void loop() {
  playSong();
}

void playSong() {
  // Find the length of the melody
  int totalNotes = sizeof(melody) / sizeof(int);

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < totalNotes ; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    float noteDuration = 1000 / noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);

    // if we wanted to stop all tones from playing we'd use
    // noTone(speakerPin);
  }
  delay(1000);
}

