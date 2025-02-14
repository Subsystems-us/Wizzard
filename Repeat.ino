// Memory repeat game
void repeatGame() {
  delay(2000);
  uint8_t noteNum = 0;       // Current amount of notes to play
  uint16_t interval = 1000;  // ms in between notes
  uint8_t song[45];
  bool gameOver = false;

  // initialize song
  for (int i = 0; i < 45; i++) song[i] = random(9);

  while (!gameOver) {
    // play the song up to noteNum
    for (int i = 0; i < noteNum + 1; i++) {
      lightLed(song[i], LED_GREEN);
      tone(BUZZ_PIN, note[song[i]], interval);
      delay(interval + 20);
      noTone(BUZZ_PIN);
      lightLed(song[i], LED_OFF);
    }

    // Take the user input and match to the current song. Exit if incorrect.
    uint8_t curGuess = 0;
    for (int i = 0; i < noteNum + 1; i++) {
      uint8_t keyIn = waitForNumKey();
      if (keyIn != song[curGuess]) {
        gameOver = true;
        break;
      }
      curGuess++;
    }
    if (!gameOver) delay(1000);  // Short delay before the next turn.

    // Add 1 note, lower the interval
    noteNum++;
    if (noteNum > 44) noteNum = 44;  // Don't go past max notes
    interval -= 20;
  }

  // You lost
  ledChase(LED_RED);
}