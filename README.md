## Dell Charger EPROM Emulator using Arduino

- Simple promgram used to emulate OneWire DS2502 EPROM with content of a 45W Original Charger (Readed from Vostro thin pin notebook)
- Tested on Arduino Pro micro
- Maybe also work on ATTINY85 smal MCU

### Sequence Diagram
                    
```seq
Notebook->Notebook: Charger is connected 
Notebook->Charger: Power up One Wire bus 
Note right of Charger: Prepare Emulated One Wire and EPROM with Data 
Notebook->Charger: RESET Signal 
Notebook->Charger: cmd 0xCC (skip Rom) 
Notebook->Charger: cmd 0xCF 0x00 0x08 (Read content 0x0008) 
Note right of Charger: Prepare CRC 
Charger->Notebook: response CRC 
Charger->Notebook: send EPROM Data 
Charger->Charger: Wait RESET signal
```
