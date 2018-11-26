#include <SigFox.h>
#include <ArduinoLowPower.h>
#include <RCSwitch.h>

RCSwitch theSwitch = RCSwitch();

void setup() {
  Serial.begin(9600);
  while (!Serial) {};

  setupSigFox();
  setupRadioWave();
}


void loop() {

  radioWave();

  delay(50000);
}

void setupSigFox() {
  // Uncomment this line and comment begin() if you are working with a custom board
  //if (!SigFox.begin(SPI1, 30, 31, 33, 28, LED_BUILTIN)) {
  if (!SigFox.begin()) {
    Serial.println("Shield error or not present!");
    return;
  }
  // Enable debug led and disable automatic deep sleep
  // Comment this line when shipping your project :)
  SigFox.debug();

  String version = SigFox.SigVersion();
  String ID = SigFox.ID();
  String PAC = SigFox.PAC();
  delay(100);

  // Send the module to the deepest sleep
  SigFox.end();

  Serial.println("Type the message to be sent");
  while (!Serial.available());

  String message = "Collar:1";
  if (message.length() > 12) {
    Serial.println("Message too long, only first 12 bytes will be sent");
  }

  // Remove EOL
  message.trim();

  // Example of send and read response
  sendStringAndGetResponse(message);
}

void sigFox() {
  
}

void setupRadioWave() {
  //This is where the radio wave will be set up
  theSwitch.enableTransmit(10);
  mySwitch.setPulseLength(321);

 // set protocol (default is 1, will work for most outlets)
 // mySwitch.setProtocol(2);

 // Optional set number of transmission repetitions.
 // mySwitch.setRepeatTransmit(15);

 pinMode(13,OUTPUT);
}

void radioWave() {
  //Where the main radio bursts will occur

  mySwitch.send("100000101100100011001000");
 digitalWrite(13,HIGH);
 delay(500);
 digitalWrite(13,LOW);
 delay(10000); 
}
void sendString(String str) {
  // Start the module
  SigFox.begin();
  // Wait at least 30mS after first configuration (100mS before)
  delay(100);
  // Clears all pending interrupts
  SigFox.status();
  delay(1);

  SigFox.beginPacket();
  SigFox.print(str);

  int ret = SigFox.endPacket();  // send buffer to SIGFOX network
  if (ret > 0) {
    Serial.println("No transmission");
  } else {
    Serial.println("Transmission ok");
  }

  Serial.println(SigFox.status(SIGFOX));
  Serial.println(SigFox.status(ATMEL));
  SigFox.end();
}

void sendStringAndGetResponse(String str) {
  // Start the module
  SigFox.begin();
  // Wait at least 30mS after first configuration (100mS before)
  delay(100);
  // Clears all pending interrupts
  SigFox.status();
  delay(1);

  SigFox.beginPacket();
  SigFox.print(str);

  int ret = SigFox.endPacket(true);  // send buffer to SIGFOX network and wait for a response
  if (ret > 0) {
    Serial.println("No transmission");
  } else {
    Serial.println("Transmission ok");
  }

  Serial.println(SigFox.status(SIGFOX));
  Serial.println(SigFox.status(ATMEL));

  if (SigFox.parsePacket()) {
    Serial.println("Response from server:");
    while (SigFox.available()) {
      Serial.print("0x");
      Serial.println(SigFox.read(), HEX);
    }
  } else {
    Serial.println("Could not get any response from the server");
    Serial.println("Check the SigFox coverage in your area");
    Serial.println("If you are indoor, check the 20dB coverage or move near a window");
  }
  Serial.println();

  SigFox.end();
}
