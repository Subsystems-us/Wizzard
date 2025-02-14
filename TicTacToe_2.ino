// Classic 2 player game
void ticTacToe2() {
  uint8_t playerNum = 1;
  uint8_t moveNum = 0;
  ledClear();
  ledsOut();
  uint8_t move = 0;

  while (!isWinner() && moveNum < 9) {
    bool isValid = false;

    while (!isValid) {
      move = waitForNumKey();
      if (leds[move] == 0) isValid = true;
      leds[move] = playerNum;
      ledsOut();
      playerNum = (playerNum == 1 ? 2 : 1);
      moveNum++;
    }
  }
  ledClear();
  ledsOut();
}

uint8_t isWinner() {
  uint8_t theWinner = 0;

  for (int i = 0; i < 3; i++) {
    if (leds[i * 3] == 1 && leds[i * 3 + 1] == 1 && leds[i * 3 + 2] == 1) {
      theWinner = 1;
      break;
    }
    if (leds[i * 3] == 2 && leds[i * 3 + 1] == 2 && leds[i * 3 + 2] == 2) {
      theWinner = 2;
      break;
    }
    if (leds[i] == 1 && leds[i + 3] == 1 && leds[i + 6] == 1) {
      theWinner = 1;
      break;
    }
    if (leds[i] == 2 && leds[i + 3] == 2 && leds[i + 6] == 2) {
      theWinner = 2;
      break;
    }
  }
  if (leds[0] == 1 && leds[4] == 1 && leds[8] == 1) theWinner = 1;
  if (leds[0] == 2 && leds[4] == 2 && leds[8] == 2) theWinner = 2;
  if (leds[2] == 1 && leds[4] == 1 && leds[6] == 1) theWinner = 1;
  if (leds[2] == 2 && leds[4] == 2 && leds[6] == 2) theWinner = 2;

  if (theWinner > 0) {
    if (soundON) funSound();
    ledChase(theWinner);
  }
  return theWinner;
}