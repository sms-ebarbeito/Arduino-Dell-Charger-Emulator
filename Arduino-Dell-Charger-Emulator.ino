/**
 *    This code emulates a DS2502 - 1kbit EEPROM as a dell power supply
 *    
 *    Suitable for INSPIRON / VOSTRO thin pin 45w, but with other memory content can use for another
 *    model or another brand like HP
 *
 *    OneWire messaging starts when AC adapter is plugged to notebook,
 *    Parasite power isn't enought to power an Arduino, you need to conect to power supply via DC-DC converter
 *    
 *    thanks to OneWireHub (Ingmar Splitt [orgua]) who makes and excelent slave library
 *    
 *    Comunication from the Notebook to the charguer:
 *    
 *    1) First RESET. this is the first command to start a comunication on OneWire
 *    2) cmd from notebook: 0xCC (skip rom, so there is only ONE device allowed on the bus)
 *    3) cmd from notebook: 0xF0 (read memory address requested is 0x0008)
 *    4) charger send CRC
 *    5) charger send memory content
 *    
 */

#include "OneWireHub.h"
#include "DS2502.h"

constexpr uint8_t pin_onewire   { 9 };

/** DELL CHARGER INSPIRON (thin pin) charger **/
constexpr uint8_t charger[41] PROGMEM = {
  'D', 'E', 'L', 'L', '0', '0', 'A', 'C', '0', '4', '5', '1', '9', '5', '0', '2',
  '3', 'C', 'N', '0', '0', '2', '8', '5', 'K', '7', '5', '6', '6', '1', '6', 'C', 
  'H', '0', 'E', 'I', 'G', 'A', '0', '3', 0x94
};

//Setup One Wire slave hub
auto hub       = OneWireHub(pin_onewire);
//Create a One Wire DS2502 EPROM
auto dellCH    = DS2502( 0x28, 0x0D, 0x01, 0x08, 0x0B, 0x02, 0x0A); // address does not matter, laptop uses skipRom -> note that therefore only one slave device is allowed on the bus

void setup() {
    Serial.begin(115200);
    Serial.println("OneWire-Hub DS2502 aka Dell Charger");

    // Add emulated eprom to One Wire
    hub.attach(dellCH);

    // Upload data to emulated eprom
    dellCH.writeMemory(charger, sizeof(charger), 0x00);
}

void loop() {
    // following function must be called periodically
    hub.poll();
}
