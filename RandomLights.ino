// Randomly show lights in dofferent colors
void randomLights() {
  while (1) {
    for (int i = 0; i < NUMPIXELS; i++) array.setPixelColor(i, array.Color(random(256), random(256), random(256)));
    array.show();
    delay(1000);
  }
}