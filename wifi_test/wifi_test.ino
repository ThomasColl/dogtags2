#include <Bridge.h>
#include <HttpClient.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
  setupRadioWave();
}


void loop() {

  radioWave();

  delay(50000);
}

void setupRadioWave() {
  //This is where the radio wave will be set up
}

void radioWave() {
  //Where the main radio bursts will occur
}
