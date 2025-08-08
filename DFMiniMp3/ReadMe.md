# DFMini MP3 Player Arduino Examples
Created by Faranux.com Electronics Team
https://faranux.com/

This repository contains two implementations for controlling the DFPlayer Mini MP3 module, developed and tested by the Faranux.com team.

## Hardware Requirements
* Developed by Faranux.com Electronics Team
* Tested on Arduino UNO/NANO
* DFPlayer Mini MP3 module (DFR0299)
* Micro SD card (FAT32 formatted)
* Speaker (3-4Ω)
* Connecting wires
* 1kΩ resistor

## Circuit Diagram
```
                           DFPlayer Mini
                         +-----------+
         Arduino 5V -----|VCC     16|
    Arduino Pin 11 ------|RX      15|
    Arduino Pin 10 ------|TX        |
                  ------|SPK_1     |------ Speaker (+)
                  ------|SPK_2     |------ Speaker (-)
         Arduino GND ----|GND       |
                         +-----------+

Note: 1kΩ resistor should be placed between Arduino Pin 11 and DFPlayer RX
```

## Code Examples

### 1. Official Library Implementation
Located in `Official_DFMiniMp3.ino`
- Basic implementation using DFRobot's official library
- Developed and tested by Faranux.com team

### 2. Makuna Library Implementation (MH2024K16SS)
Located in `MH2024K16SS_DFMiniMp3_By_Makuna_Library.ino`
- Advanced implementation with extended features
- Optimized for MH2024K16SS chip variant
- Tested and verified by Faranux.com team

## SD Card Setup Instructions
1. Format SD card to FAT32
2. Create folder named 'mp3' in root directory
3. Copy MP3 files with names: 0001.mp3, 0002.mp3, etc.
4. Maximum supported size: 32GB

## Troubleshooting Tips by Faranux.com
* Check all connections carefully
* Verify SD card format (must be FAT32)
* Ensure MP3 files are properly named
* Monitor Serial output for error messages
* Test speaker connections
* Verify power supply is stable

## Credits
* Original development and testing by Faranux.com Electronics Team
* Based on DFRobot's official documentation
* Enhanced with Makuna library support
* Visit https://faranux.com/ for more projects and tutorials

## License
This project is open-source and shared by Faranux.com team for educational purposes.

## Support
For technical support and questions:
* Visit: https://faranux.com/
* Follow our tutorials
* Check our documentation