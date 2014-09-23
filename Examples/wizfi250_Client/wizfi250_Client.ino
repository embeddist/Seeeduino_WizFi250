/*
  Released 16 Feb 2014 
  Elefantasy

  Modified 20 SEP 2014
  Soohwan@wiznet.co.kr 
*/
#if defined(REL_GR_KURUMI)
;
#else
#include <Arduino.h>
#endif
#include "WizFi250.h"

//#define SPI_ENABLE

#define SSID      "STEST"
#define KEY       "87654321"
#define AUTH       "WPA2" 
 
#define  HOST_IP       "192.168.168.102"
#define  REMOTE_PORT    9090
#define LOCAL_PORT      1234

#if defined(SPI_ENABLE)
#define spi_CS  8
#endif
#define wizfi250_rst  9
 
WizFi250 wizfi250(&Serial1, wizfi250_rst);
boolean returnValue=false;
void setup() {

#if defined(SPI_ENABLE)
pinMode(spi_CS,OUTPUT);
digitalWrite(spi_CS, HIGH);   
#else
Serial1.begin(115200);
#endif 
Serial.begin(115200);
Serial.println("--------- WIZFI250 TEST --------");
  wizfi250.hw_reset();
  wizfi250.reset();
  delay(1000);
  Serial.println("Join " SSID );
  wizfi250.sendCommand("AT+WLEAVE\r");
   delay(1000);
   if (!wizfi250.join(SSID, KEY, AUTH)) {
    Serial.println("Failed join " SSID);
     Serial.println("Please Restart");
  } else {
    
  Serial.println("Successfully join " SSID);
  wizfi250.sendCommand("AT+WSTAT\r");
  delay(5);
  char c;
  while(wizfi250.receive((uint8_t *)&c, 1, 100) > 0) {
    Serial.print((char)c);
  }
  delay(2000);  
  returnValue =wizfi250.connect(HOST_IP,REMOTE_PORT,LOCAL_PORT);
  if(returnValue)
   Serial.println("Now you can send data to Server or receive data from Server!");
}
}
unsigned int time_point = 0;

void loop() {
  if(wizfi250.available()) {
    Serial.print((char)wizfi250.read());
  }
   if(Serial.available()) {
    wizfi250.print((char)Serial.read());
  }
  
}
