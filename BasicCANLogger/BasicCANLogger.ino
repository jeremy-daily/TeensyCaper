/* Getting Started with the J1939 Teensy Caper
Written By Jeremy Daily
17 April 2016

This System is written for a Teensy3.2 with an SD board and the TeensyJ1939Caper 
Needs to cut pin4 from the SD card

Description: A Basic CAN logger

*/

#include <SPI.h>
#include "SdFat.h"
//#include "FreeStack.h"

#include <FlexCAN.h>

// SD chip select pin.  Be sure to disable any other SPI devices such as Enet.
const uint8_t SDchipSelect = 10;
const uint8_t CANchipSelect = A1;

// Log file base name.  Must be six characters or less.
#define CANFILE_BASE_NAME "CANlog"
#define J1708FILE_BASE_NAME "J1708log"

// global for card size
uint32_t cardSize;

const int CANRate = 250000;

FlexCAN CANbus(CANRate);

static CAN_message_t txCANmsg,rxCANmsg;

uint32_t txCANcount,rxCANcount;
uint32_t txCANtimer,rxCANtimer;
uint32_t currentMillis,previousMillis;
boolean recording = true;

// File system object.
SdFat sd;

// Log file.
SdFile CANfile;


// Time in micros for next data record.
uint32_t logTime;

// Write data header.
void writeHeader() {
  CANfile.println(F("CAN Data Log"));
  CANfile.print(F("Rate,"));
  CANfile.println(CANRate, DEC);
  CANfile.print(F("Network,"));
  CANfile.print(F("Micros,"));
  CANfile.print(F("Line,"));
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
  uint32_t currentMicros = micros();
  CANfile.print("CAN");
  CANfile.print(",");
  CANfile.print(currentMicros,DEC);
  CANfile.print(",");
  CANfile.print(rxCANcount);
  CANfile.print(",");
  CANfile.print(rxCANmsg.id,HEX);
  CANfile.print(",");
  CANfile.print(rxCANmsg.len,DEC);
  CANfile.print(",");
  for( int idx=0; idx<rxCANmsg.len; ++idx ) {
      CANfile.print(rxCANmsg.buf[idx],HEX);
      CANfile.print(",");
  
    }
  CANfile.println();
  rxCANcount++;
}
void logJ1708byte(){
  uint32_t currentMicros = micros();
  uint8_t c = Serial3.read();
  CANfile.print("J1708");
  CANfile.print(",");
  CANfile.print(currentMicros,DEC);
  CANfile.print(",");
  CANfile.println(c,HEX);
  
}

void setup()
{
  
  pinMode(SDchipSelect, OUTPUT);
  digitalWrite(SDchipSelect, HIGH);   // de-select the SD Card
  pinMode(CANchipSelect, OUTPUT);
  digitalWrite(CANchipSelect, HIGH);   // de-select the SD Card
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH); //turn on LED
  pinMode(0,INPUT_PULLUP);
  
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Starting CAN Logger");
  while (!sd.begin(SDchipSelect, SPI_FULL_SPEED)) {
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

 

 
 
  
  Serial.println("Starting CAN Bus");
  CANbus.begin();
  Serial3.begin(9600);
  
}


void logData(){
  const uint8_t BASE_NAME_SIZE = sizeof(CANFILE_BASE_NAME) - 1;
  
  char fileName[13] = CANFILE_BASE_NAME "00.csv";
   // Find an unused file name.
  if (BASE_NAME_SIZE > 6) {
    Serial.println("FILE_BASE_NAME too long");
  }
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
  
  recording = digitalRead(0);
  if (recording){
      delay(150);
      recording = digitalRead(0);    
      if (recording){
          if (!CANfile.open(fileName, O_CREAT | O_WRITE | O_APPEND)) {
              Serial.println("file.open error!");
              return;
          }
          Serial.print(F("Logging data to: "));
          Serial.println(fileName);
          writeHeader();
          
          while (recording) {
            recording = digitalRead(0);
            if (Serial3.available()) logJ1708byte();
            while (CANbus.read(rxCANmsg)) logCANframe();
  
            currentMillis = millis();
            if (currentMillis - previousMillis >= 1000){
              previousMillis = currentMillis;
              Serial.println(rxCANcount);
            }
          }
          
          CANfile.close();
          delay(1000);
          digitalWrite(13,HIGH);
          delay(1000);
          digitalWrite(13,LOW);
          rxCANcount = 0;
        }
     }
    
}

void loop(){
  logData();
  
}

