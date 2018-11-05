#include <Bridge.h>
#include <HttpClient.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);
}


void loop() {

  HttpClient client;
  client.get("149.153.1.40:5000");

  while (client.available()) {
    
    int c = client.read();
    Serial.print(c);
  }
  Serial.flush();

  delay(500000);
}
