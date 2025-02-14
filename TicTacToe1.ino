// Classic 1 player game
void ticTacToe1() {
  uint8_t moveNum = 0;
  ledClear();
  ledsOut();
  uint8_t move = 0;

  while (!aWinner() && moveNum < 9) {
    bool isValid = false;

    while (!isValid) {
      // User Move
      move = waitForNumKey();
      if (leds[move] == 0) isValid = true;
      leds[move] = 1;
      ledsOut();
      moveNum++;
    }
    if (isWinner()) break;
    if (moveNum < 9) leds[makeMove()] = 2;
    ledsOut();
  }

  ledClear();
  ledsOut();
}


uint8_t aWinner() {
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

int makeMove() {

  // All possible winning combinations
  int winningCombinations[8][3] = {
    { 0, 1, 2 },  // Top row
    { 3, 4, 5 },  // Middle row
    { 6, 7, 8 },  // Bottom row
    { 0, 3, 6 },  // Left column
    { 1, 4, 7 },  // Middle column
    { 2, 5, 8 },  // Right column
    { 0, 4, 8 },  // Diagonal
    { 2, 4, 6 }   // Diagonal
  };

  // Try to find a winning move
  for (int i = 0; i < 8; i++) {
    int countPlayer = 0;
    int emptyIndex = -1;
    for (int j = 0; j < 3; j++) {
      int index = winningCombinations[i][j];
      if (leds[index] == 2) {
        countPlayer++;
      } else if (leds[index] == 0) {
        emptyIndex = index;
      }
    }
    if (countPlayer == 2 && emptyIndex != -1) {
      return emptyIndex;
    }
  }

  // Try to block the opponent from winning
  for (int i = 0; i < 8; i++) {
    int countOpponent = 0;
    int emptyIndex = -1;
    for (int j = 0; j < 3; j++) {
      int index = winningCombinations[i][j];
      if (leds[index] == 1) {
        countOpponent++;
      } else if (leds[index] == 0) {
        emptyIndex = index;
      }
    }
    if (countOpponent == 2 && emptyIndex != -1) {
      return emptyIndex;
    }
  }

  // Otherwise, pick the first available position
  for (int i = 0; i < 9; i++) {
    if (leds[i] == 0) {
      return i;
    }
  }
  // No valid move (should not happen in a valid game)
  return -1;
}