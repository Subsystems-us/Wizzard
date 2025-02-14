// Lights out game

void lightsOut() {
  // Initialize Game with solvable board
  for (int i = 0; i < 20; i++) updateBoard(random(9));

  ledsOut();

  while (!checkForWin()) {
    uint8_t keyIn = waitForNumKey();
    updateBoard(keyIn);
    ledsOut();
  }
  // You are here because you won
  if (soundON) funSound();
  ledChase(2);
}

uint8_t updateBoard(uint8_t choice) {
  switch (choice) {
    case 0:
      leds[0] = (leds[0] == 1 ? 0 : 1);
      leds[1] = (leds[1] == 1 ? 0 : 1);
      leds[3] = (leds[3] == 1 ? 0 : 1);
      break;
    case 1:
      leds[1] = (leds[1] == 1 ? 0 : 1);
      leds[0] = (leds[0] == 1 ? 0 : 1);
      leds[2] = (leds[2] == 1 ? 0 : 1);
      leds[4] = (leds[4] == 1 ? 0 : 1);
      break;
    case 2:
      leds[2] = (leds[2] == 1 ? 0 : 1);
      leds[1] = (leds[1] == 1 ? 0 : 1);
      leds[5] = (leds[5] == 1 ? 0 : 1);
      break;
    case 3:
      leds[3] = (leds[3] == 1 ? 0 : 1);
      leds[0] = (leds[0] == 1 ? 0 : 1);
      leds[6] = (leds[6] == 1 ? 0 : 1);
      leds[4] = (leds[4] == 1 ? 0 : 1);
      break;
    case 4:
      leds[4] = (leds[4] == 1 ? 0 : 1);
      leds[5] = (leds[5] == 1 ? 0 : 1);
      leds[1] = (leds[1] == 1 ? 0 : 1);
      leds[3] = (leds[3] == 1 ? 0 : 1);
      leds[7] = (leds[7] == 1 ? 0 : 1);
      break;
    case 5:
      leds[5] = (leds[5] == 1 ? 0 : 1);
      leds[8] = (leds[8] == 1 ? 0 : 1);
      leds[2] = (leds[2] == 1 ? 0 : 1);
      leds[4] = (leds[4] == 1 ? 0 : 1);
      break;
    case 6:
      leds[6] = (leds[6] == 1 ? 0 : 1);
      leds[3] = (leds[3] == 1 ? 0 : 1);
      leds[7] = (leds[7] == 1 ? 0 : 1);
      break;
    case 7:
      leds[7] = (leds[7] == 1 ? 0 : 1);
      leds[4] = (leds[4] == 1 ? 0 : 1);
      leds[6] = (leds[6] == 1 ? 0 : 1);
      leds[8] = (leds[8] == 1 ? 0 : 1);
      break;
    case 8:
      leds[5] = (leds[5] == 1 ? 0 : 1);
      leds[8] = (leds[8] == 1 ? 0 : 1);
      leds[7] = (leds[7] == 1 ? 0 : 1);
      break;
  }
}

bool checkForWin() {
  for (int i = 0; i < 9; i++)
    if (leds[i] == 1) return false;
  return true;
}