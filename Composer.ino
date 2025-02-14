// Plays a sequence of notes you enter
#define MAXNOTES 64
#define SILENCE 20

void composerGame() {
  uint8_t song[MAXNOTES];  // max notes/rests in song

  // Receive song from user
  // Select key is a silent note
  // Enter plays the song

  uint8_t curNote = 0;
  uint8_t keyIn = waitForKey();

  while (keyIn != ENTER_KEY) {

    if (keyIn == SELECT_KEY) song[curNote] = SILENCE;
    else song[curNote] = keyIn;

    curNote++;

    if (curNote == MAXNOTES) break;  // reached the end, play the song
    keyIn = waitForKey();
  }

  //Play the song
  keyIn = NO_KEY;
  while (keyIn != ENTER_KEY) {
    for (int i = 0; i < curNote; i++) {
      if (song[i] != SILENCE) {
        tone(BUZZ_PIN, note[song[i]], 450);
        lightLed(song[i], LED_GREEN);
      }
      delay(500);
      lightLed(song[i], LED_OFF);
    }
    ledClear();
    keyIn = waitForKey();
  }
}