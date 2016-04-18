/* Getting Started with the J1939 Teensy Caper
Written By Jeremy Daily
17 April 2016

This System is written for a Teensy3.2 with an SD board and the TeensyJ1939Caper 
Needs to cut pin4 from the SD card

Description: A Basic CAN logger

*/

#include <SPI.h>
#include "SdFat.h"
#include "FreeStack.h"

#include <FlexCAN.h>

// SD chip select pin.  Be sure to disable any other SPI devices such as Enet.
const uint8_t SDchipSelect = A1;

// Log file base name.  Must be six characters or less.
#define CANFILE_BASE_NAME "CANlog"

// global for card size
uint32_t cardSize;

const int CANRate = 500000;

FlexCAN CANbus(500000);

static CAN_message_t txCANmsg,rxCANmsg;

uint32_t txCANcount,rxCANcount;
uint32_t txCANtimer,rxCANtimer;
uint32_t currentMillis,previousMillis;

// File system object.
SdFat sd;

// Log file.
SdFile CANfile;

char fileName[13];

// Time in micros for next data record.
uint32_t logTime;

// Write data header.
void writeHeader() {
  CANfile.println(F("CAN Data Log"));
  CANfile.print(F("Rate,"));
  CANfile.println(CANRate, DEC);
  CANfile.print(F("Line,"));
  CANfile.print(F("Micros,"));
  CANfile.print(F("ID,"));
  CANfile.print(F("DLC,"));
  CANfile.print(F("B0,"));
  CANfile.print(F("B1,"));
  CANfile.print(F("B2,"));
  CANfile.print(F("B3,"));
  CANfile.print(F("B4,"));
  CANfile.print(F("B5,"));
  CANfile.print(F("B6,"));
  CANfile.print(F("B7,"));
  CANfile.println();
}
void logCANframe(){
  CANfile.open(fileName);
  CANfile.print(rxCANcount);
  CANfile.print(",");
  CANfile.print(rxCANtimer,DEC);
  CANfile.print(",");
  CANfile.print(rxCANmsg.id,HEX);
  CANfile.print(",");
  CANfile.print(rxCANmsg.len,DEC);
  CANfile.print(",");
  for( int idx=0; idx<rxCANmsg.len; ++idx ) {
      CANfile.print(rxCANmsg.buf[idx],HEX);
    }
  CANfile.println();
  CANfile.close();
}

void setup()
{
  
  pinMode(SDchipSelect, OUTPUT);
  digitalWrite(SDchipSelect, HIGH);   // de-select the SD Card
 
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.println("Starting CAN Logger");
  while (!sd.begin(SDchipSelect, SPI_HALF_SPEED)) {
    delay(100);
    Serial.println("Error with SD Card.");
  }
 
  Serial.print("\nInitializing SD card...");


  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!sd.cardBegin(SDchipSelect, SPI_FULL_SPEED)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
   Serial.println("Wiring is correct and a card is present."); 
  }

  cardSize = sd.card()->cardSize();
  // print the type of card
    switch (sd.card()->type()) {
  case SD_CARD_TYPE_SD1:
    Serial.print("SD1\n");
    break;

  case SD_CARD_TYPE_SD2:
    Serial.print("SD2\n");
    break;

  case SD_CARD_TYPE_SDHC:
    if (cardSize < 70000000) {
      Serial.print("SDHC\n");
    } else {
      Serial.print("SDXC\n");
    }
    break;

  default:
    Serial.print("Unknown\n");
  }

 

 
  
  const uint8_t BASE_NAME_SIZE = sizeof(CANFILE_BASE_NAME) - 1;
  if (BASE_NAME_SIZE > 6) {
    Serial.println("FILE_BASE_NAME too long");
  }

  char fileName[13] = CANFILE_BASE_NAME "00.csv";

  while (sd.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      Serial.println("Can't create file name. Overwriting.");
      break;
    }
  }
  
  Serial.println("Starting CAN Bus");
  CANbus.begin();
  
  CANfile.open(fileName);
  Serial.print(F("Logging CAN data to: "));
  Serial.println(fileName);
  writeHeader();
  CANfile.close();
}

void loop(){
  currentMillis = millis();
  
  while ( CANbus.read(rxCANmsg) ) {
      rxCANtimer=micros();
      rxCANcount++;
      logCANframe();
  }
  if (currentMillis - previousMillis >= 1000){
    previousMillis = currentMillis;
    Serial.println(rxCANcount);
  }
}

