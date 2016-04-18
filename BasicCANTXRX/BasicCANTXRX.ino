/* Getting Started with the J1939 Teensy Caper
Written By Jeremy Daily
17 April 2016

This System is written for a Teensy3.2 with an SD board and the TeensyJ1939Caper

Description: A Basic CAN logger
*/
#include <FlexCAN.h>

const int CANRate = 500000;

FlexCAN CANbus(500000);
static CAN_message_t txCANmsg,rxCANmsg;

uint32_t txCANcount,rxCANcount;
uint32_t txCANtimer,rxCANtimer;
uint32_t currentMillis,previousMillis;

void setup()
{
  
 // pinMode(SDchipSelect, OUTPUT);
 // digitalWrite(SDchipSelect, HIGH);   // de-select the SD Card
 
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  
  Serial.println("Starting CAN Bus");
  CANbus.begin();
  
  
 
}

void loop(){
  currentMillis = millis();
  
  while ( CANbus.read(rxCANmsg) ) {
      Serial.write(rxCANmsg.buf[0]);
      rxCANtimer=micros();
      rxCANcount++;
      logCANframe();
  }
  if (currentMillis - previousMillis >= 100){
    previousMillis = currentMillis;
    Serial.println(rxCANcount);
    txCANmsg.buf[0]= (currentMillis & 0xFF000000) >> 24;
    txCANmsg.buf[1]= (currentMillis & 0x00FF0000) >> 16;
    txCANmsg.buf[2]= (currentMillis & 0x0000FF00) >>  8;
    txCANmsg.buf[3]= (currentMillis & 0x000000FF);
    CANbus.write(txCANmsg);
    txCANcount++;
  }
}

