# TeensyCaper
Electronics to interface a PRJC Teensy 3.2 32-bit Arduino Compatible board with J1939 connections in heavy duty equipment. Includes Two CAN Channels, J1708, and LIN.

This repository assumes you know how to work with the <a target="_blank" href="https://www.pjrc.com/store/teensy32.html">Teensy</a> and <a href="https://www.pjrc.com/teensy/teensyduino.html">Teensyduino.</a>

## Bill of Materials

Reference the Schematic for the Designators. Most items are from <a target="_blank" href="http://www.mouser.com"> Mouser </a> or Sparkfun.

| Comment | Description | Designator | Quantity | Manufacturer | Manufacturer Part Number | Supplier | Supplier Part Number |
| ------- | ----------- | ---------- | ------ | ------------ | ------------------------ | -------- | -------------------- |
| CR1225FV-LF | Coin Cell Battery 3V 2-PIN VERT 48mAh 12.5 x 2.5mm | Batt1 | 1 | Renata | CR1225FV-LF | Mouser | 614-CR1225FV-LF| 
| Teensy 3.2 | 32 Bit Arduino-Compatible Microcontroller | BRD1 | 1 | <a target="_blank" href="https://www.pjrc.com/store/teensy32.html">PRJC</a> | TEENSY32 | Sparkfun | DEV-13736| 
| 0.1uF | Multilayer Ceramic Capacitors MLCC - Leaded 50volts 0.1uF 10% X7R | C1, C2, C5, C6 | 4 | AVX | SR215C104KAA | Mouser | 581-SR215C104K| 
| 330 uF | Aluminum Electrolytic Capacitors - Leaded 330uF 35V | C3, C4 | 2 | Panasonic | EEU-FC1V331 | Mouser | 667-EEU-FC1V331| 
| 10uF | Multilayer Ceramic Capacitors MLCC - Leaded 50volts 10uF 10% X7R | C7 | 1 | AVX | SR655C106KAR | Mouser | 581-SR655C106KAR| 
| STPS2150 | DIODE SCHOTTKY 60V 2A AXIAL | D1 | 1 | STMicroelectronics | STPS2150 | Mouser | 511-STPS2150| 
| ESP8266 | Sparkfun ESP8266 Module (WRL-13678) | J1 | 1 | Espressif | ESP8266 | Sparkfun | WRL-13678| 
| 10 Pos Mini-Fit Jr. | Headers & Wire Housings 10 CKT R/A HEADER | J2 | 1 | Molex | 39-30-1100 | Mouser | 538-39-30-1100| 
| Headers | Pin headers for Teensy | BRD1 | 2 | 3M  |  929400-01-28-RK | Mouser |  517-929400-01-28-RK| 
| 2N3904 | NPN General Purpose Amplifier | Q1, Q2 | 2 | Central Semiconductor | 2N3904 | Mouser | 610-2N3904| 
| 4.7k | Metal Film Resistors - Through Hole 4.7K OHM 1/4W 1% | R1, R3, R5, R6, R10, R12 | 6 | Yageo | MFR-25FRF52-4K7 | Mouser | 603-MFR-25FRF52-4K7| 
| 47 | Metal Film Resistors - Through Hole 47 OHM 1/4W 1% | R2, R7, R8 | 3 | Yageo | MFR-25FRF52-47R | Mouser | 603-MFR-25FRF52-47R| 
| 1k | Metal Film Resistors - Through Hole 1K ohm 1/4W 1% | R4, R9 | 2 | Yageo | MFR-25FRF52-1K | Mouser | 603-MFR-25FRF521K| 
| MCP2562 | High-Speed CAN Transceiver, 8-Pin PDIP, Industrial Temperature | U1, U2 | 2 | Microchip Technology | MCP2562-E/P | Mouser | 579-MCP2562-E/P| 
| MCP2515-E/P | Stand-Alone CAN Controller With SPI Interface, 18-Pin PDIP | U3 | 1 | Microchip Technology | MCP2515-E/P | Mouser | 579-MCP2515-E/P| 
| MCP2003-E/P | TXRX LIN BUS BIDIRECT 8DIP | U4 | 1 | Microchip Technology | MCP2003-E/P | Mouser | 579-MCP2003EP| 
| SN65HVD12P | RS-485 Interface IC 3.3V RS485 | U6 | 1 | Texas Instruments | SN65HVD12P | Mouser | 595-SN65HVD12P| 
| LD1086V33 | IC REG LDO 3.3V 1.5A TO220AB | VR1 | 1 | STMicroelectronics | LD1086D2M33TR | Mouser | 511-LD1086D2M33-TR| 
| OKI-78SR | 5V DC/DC Converter (7805 replacement) | VR2 | 1 | Murata Power Solutions | OKI-78SR-5/1.5-W36-C | Mouser | 580-OKI78SR5/1.5W36C | 
| Crystal | Crystals 32.768KHz 12ppm 12.5pF | | 1 | Citizen | CFS206-32.768KEZB-U | Mouser | 695-CFS206-327KEZB-U |

Since this is an open source project, feel free to make substitutions as you see fit. Often an engineer or hobbiest will have other version of the parts available to them. 

The Battery and Crystal are for the real time clock on the Teensy. PRJC also sells an SD card adapter to add "flight data recorder" capabilities.

The external interface is with the a 10 position Molex Mini-Fit Jr. and the Molex part numbers to build interface cables are as follows:
* Mouser Part #: 538-39-01-2100
* Molex Part #: 39-01-2100
* Mouser Part #: 538-39-00-0039
* Molex Part #: 39-00-0039

It is advisable to obtain a pin extraction tool for Mini-fit Jr. contacts as well: 
* Mouser Part #: 538-11-03-0044
* Molex Part #: 11-03-0044
Crimpers are also available, but they are expensive (~$250):
* Mouser Part #: 538-63819-0900
* Molex Part #: 63819-0900

The printed circuit board can be ordered from OSH Park in batches of 3 using the following link:

<a target="_blank" href="https://oshpark.com/shared_projects/nv1WiUQg"><img src="https://a800d827b6de8403a51e-6ffc2e718631809086ea40332b2055f7.ssl.cf1.rackcdn.com/assets/badge-5b7ec47045b78aef6eb9d83b3bac6b1920de805e9a0c227658eac6e19a045b9c.png" alt="Order from OSH Park"></img></a>

OSH Park sells the Teensy 3.2 too!

## Interface Cables
This section describes some different interface cables than can be made to interface the teensy caper to the networks.
### J1939 at 250k
The black SAE Standard 9-pin connector has the following connections:

| SAE Pin | Description | Suggested Colors | TeensyCaper Pin |
| --- | ----------- | --- | --- |
| A | Ground | Black | J2:1
| B | Raw Battery + | Red | J2:2
| C | J1939 H | Yellow | J2:3 |
| D | J1939 L | Green | J2:4 |
| E | Shield  | Not used | Not used |
| F | J1708 H | Pink | J2:6 |
| G | J1708 L | Purple | J2:7 |
| H | CAN2 H | White | J2:8 |
| J | CAN2 L | Blue | J2:9 |

Sometimes SAE Pin E can be used for LIN or K-line communications.

The TeensyCaper molex Pin J2:5 is LIN and the pin J2:10 is an open collector that can be switched to ground.

### J1939 Y Splitter Cable
To build a splitter cable, the machined sockets that are used in the diagnostic connector are doubled up. This is not a manuracture approved method of splitting a cable, but it works quite well. 

The parts list is as follows:

|  Description                  |  Quantity | Manufacturer | Manufacturer Part Number | Supplier | Supplier Part Number |
|  -----------------------------|  -------- | ------------ | ------------------------ | -------- | -------------------- |
| 9-pin Diagnostic Plug Housing | 1         | Amphenol Sine Systems | AHD16-9-1939S | Mouser | 654-AHD16-9-1939S |
| 16 gauge Socket Connector     | 9         | Amphenol Sine Systems | AT62-201-16141 | Mouser | 654-AT62-201-16141 |
| 9-pin Inline Receptical       | 2         | Amphenol Sine Systems | AHD14-9-1939P | Mouser | 654-AHD14-9-1939P |
| 16 gauge Pin Connector        | 18        | Amphenol Sine Systems | AT60-202-16141 | Mouser | 654-AT60-202-16141 |

You will need 18 wires, preferably 2 each of different colors. The wires can be cut to about 8 inches. The side that gets doubled up, it is suggested to strip the ends about 1/2 inch. The other ends get stripped about 1/4 inch. Uing automotive grade 20 gauge wire with TXL or GXL insulation is recommended. Allied Wire and Cable can sell rolls of it; for example, <a target="_blank" href="http://www.awcwire.com/part.aspx?partname=txl-20">TXL-20</a>.

These part numbers also corrospond to Deutsch part numbers by changing the A to a D.

### Man-in-the-Middle Cable
This cable connects to one J1939 connector with a plug housing on CAN1 of the TeensyCaper and another receptical housing to J1939 on CAN2.
The CAN 2 cavities are not used on the 9-pin connector. Power, ground, and J1708 are doubled up on the plug housing. 

