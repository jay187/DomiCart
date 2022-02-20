#ifndef RFIDReader_H

#define RFIDReader_H

#include <MFRC522.h>
#include <SPI.h>

class RFIDReader {
 public:
  RFIDReader(byte CS_PIN, byte PD_PIN) : mfrc522(CS_PIN, PD_PIN) {}

  void setup() {
    // SPI-Bus initialisieren
    SPI.begin();

    // MFRC522 initialisieren
    Serial.println("");
    Serial.println("Initializing MFRC522");
    this->mfrc522.PCD_Init();

    // Kurze Pause nach dem Initialisieren
    delay(10);
    Serial.println("");

    // Details vom MFRC522 RFID READER / WRITER ausgeben
    this->mfrc522.PCD_DumpVersionToSerial();
  }

  void loop() {
    // Sobald ein Chip aufgelegt wird startet diese Abfrage
    if (this->mfrc522.PICC_IsNewCardPresent()) {
      // CardID resetten
      chipID = 0;

      this->mfrc522.PICC_ReadCardSerial();

      // Hier wird die ID des Chips in die Variable chipID geladen
      for (byte i = 0; i < this->mfrc522.uid.size; i++) {
        chipID = ((chipID + this->mfrc522.uid.uidByte[i]) * 10);
      }

      Serial.print("New RFID: [");
      Serial.print(chipID);
      Serial.print("] @ ");
      Serial.println(millis());
    }
  }

 private:
  MFRC522 mfrc522;
  long chipID;
};

#endif
