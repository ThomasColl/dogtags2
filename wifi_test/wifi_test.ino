/*
  SigFox First Configuration

  This sketch demonstrates the usage of MKRFox1200 SigFox module.
  Since the board is designed with low power in mind, it depends directly on ArduinoLowPower library

  This example code is in the public domain.
*/

#include <SigFox.h>
#include <ArduinoLowPower.h>

bool value_to_send = true;

#define DEBUG 1


void setup() {
  Serial.begin(9600);
  while (!Serial) {};

  
  // Uncomment this line and comment begin() if you are working with a custom board
  //if (!SigFox.begin(SPI1, 30, 31, 33, 28, LED_BUILTIN)) {
  if (!SigFox.begin()) {
    Serial.println("Shield error or not present!");
    return;
  }

  setupSigFox();
}

void loop()
{
//  loopSigFox();
//  delay(5000);
}

void setupSigFox() {
  if (DEBUG){
    Serial.begin(9600);
    while (!Serial) {};
  }

  // Initialize the SigFox module
  if (!SigFox.begin()) {
    if (DEBUG){
      Serial.println("Sigfox module unavailable !");
    }
    return;
  }

  // If we wanto to debug the application, print the device ID to easily find it in the backend
  if (DEBUG){
    SigFox.debug();
    Serial.println("ID  = " + SigFox.ID());
  }

  delay(100);

  // Compose a message as usual; the single bit transmission will be performed transparently
  // if the data we want to send is suitable
  SigFox.beginPacket();
  SigFox.write(value_to_send);
  int ret = SigFox.endPacket();

  if (DEBUG){
    Serial.print("Status : ");
    Serial.println(ret);
  }
}

void loopSigFox() {
  SigFox.beginPacket();
  SigFox.write(value_to_send);
  int ret = SigFox.endPacket();

  if (DEBUG){
    Serial.print("Status : ");
    Serial.println(ret);
  }
}
