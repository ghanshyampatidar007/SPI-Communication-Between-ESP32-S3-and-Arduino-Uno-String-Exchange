#include <SPI.h>
#define max 20

volatile bool dataReceived = false;
volatile byte receivedByte;
char rxBuffer[max]={0};
char txBuffer[max] = "Hello esp32s3"; // Reply string
volatile byte rxIndex = 0;
volatile byte txIndex = 0;

void setup() {
  Serial.begin(9600);
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

ISR(SPI_STC_vect) {

  receivedByte = SPDR; // Read byte from master
  // Save to rxBuffer
  if (rxIndex < max) {
    rxBuffer[rxIndex++] = receivedByte;

    if (rxIndex ==max) {
      rxBuffer[rxIndex-1] = '\0';
      dataReceived = true;
      rxIndex = 0;
      txIndex = 0;  // Reset for next reply
    }
  }

  // Send byte from txBuffer
  SPDR = txBuffer[txIndex];
  if (txIndex !=max-1) {
    txIndex++;
  }
}

void loop() {
  if (dataReceived) {
    Serial.print("Received from master: ");
    Serial.println(rxBuffer);
    dataReceived = false;
    delay(2000);
  }
}



