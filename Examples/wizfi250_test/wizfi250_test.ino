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
#include <SoftwareSerial.h>
#endif
#include "WizFi250.h"

//#define SPI_ENABLE

#define SSID      "STEST"
#define KEY       "87654321"
#define AUTH       "WPA2" 

#if defined(SPI_ENABLE)
#define spi_CS  8
#endif
#define wizfi250_rst  9
 
WizFi250 wizfi250(&Serial1, wizfi250_rst);

void setup() {
#if defined(SPI_ENABLE)
pinMode(spi_CS,OUTPUT);
digitalWrite(spi_CS, LOW);    
#else
Serial1.begin(115200);
#endif 
Serial1.begin(115200);
Serial.println("--------- WIZFI250 TEST --------");
  wizfi250.hw_reset();
  wizfi250.reset();
  delay(1000);
  Serial.println("Join " SSID );
  delay(10);
  if (wizfi250.join(SSID, KEY, AUTH)) {
    Serial.println("Successfully join  "  SSID);
  } else {
     Serial.println("Failed join " SSID);
  }
  wizfi250.clear();
 Serial.println("*************send command to get Wizfi250 status******************");
  wizfi250.sendCommand("AT+WSTAT\r");
  //delay(10);
  char c;
  while (wizfi250.receive((uint8_t *)&c, 1, 100) > 0) {
    Serial.print((char)c);
  }

}
void loop() {
  while (wizfi250.available()) {
    Serial.write(wizfi250.read());
  }
  while (Serial.available()) {
    wizfi250.write(Serial.read());
}
}
