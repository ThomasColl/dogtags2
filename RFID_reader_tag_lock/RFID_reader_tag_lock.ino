// Student numeber : c00202493
// Student name : Cathal Brady
// Purpose : Distributed and Concurrent Device Development arduino project.
// Project title : DogTags2.0
 
#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "99 A5 D9 D9" || content.substring(1) == "40 99 DE A4") //change here the UID of the card/cards that you want to give access
  {
    if (content.substring(1) == "99 A5 D9 D9" )
    {
      Serial.println("Authorized access");
      Serial.println("Authorized Dog tag");
      Serial.println("Owner Name: Pat McNamee");
      Serial.println("Dog Name: Fido");
      Serial.println();
      delay(3000);
    }
   else if ( content.substring(1) == "40 99 DE A4") 
    {
      Serial.println("Authorized access");
      Serial.println("Authorized Owner tag");
      Serial.println("Dog Name: Fido");
      Serial.println("Owner Name: Pat McNamee");
      Serial.println();
      delay(3000);
    }
  }
  else   {
    Serial.println(" Access denied");
    delay(3000);
  }
}
