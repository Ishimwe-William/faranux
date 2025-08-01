# Laser Sensor Security System
Created by Faranux Team

## Overview
This project implements a laser-based security system using an Arduino Uno, consisting of a laser transmitter and receiver module. When the laser beam between the transmitter and receiver is interrupted, the system triggers an alarm through a buzzer and visual indication through an LED.

## Features
- Real-time laser beam interruption detection
- Visual feedback through LED indicator
- Audible alarm through buzzer
- Serial monitor status reporting
- Simple and reliable security implementation

## Components Required
- Arduino Uno Rev3
- Laser Transmitter Module (Tx)
- Laser Receiver Module (Rx)
- LED (Green)
- 180 ohm Resistor
- 5V Active Buzzer
- Connecting wires

## Pin Configuration
| Component | Arduino Pin |
|-----------|------------|
| Laser Tx  | D2         |
| Laser Rx  | D3         |
| LED       | D12        |
| Buzzer    | D5         |

## Circuit Diagram
![Circuit Diagram](circuit-diagram.png)

The circuit should be connected as shown in the schematic diagram above.

## How It Works
1. The laser transmitter continuously emits a laser beam to the receiver
2. When the beam is uninterrupted:
   - LED is ON (system armed)
   - Buzzer is OFF
   - Serial monitor shows "Secure - Beam connected"
3. When the beam is interrupted:
   - LED turns OFF
   - Buzzer activates
   - Serial monitor shows "ALERT! Beam interrupted!"

## Installation
1. Clone this repository:
2. Connect the components according to the circuit diagram
3. Upload the provided Arduino code to your Arduino Uno
4. Open Serial Monitor (baud rate: 9600)
5. Power up the system

## Serial Monitor Output
The system provides real-time status updates through the Serial Monitor:
```
Laser Security System Initializing...
System Armed and Ready!
Status: Secure - Beam connected
Status: ALERT! Beam interrupted!
```

## Usage
The system will start working immediately after powering up:
- Green LED indicates system is armed and functioning
- Buzzer will sound when the laser beam is interrupted
- Monitor system status through Serial Monitor

## Troubleshooting
| Problem | Solution |
|---------|----------|
| LED always OFF | Check LED polarity and 180Ω resistor |
| Buzzer not working | Verify 5V power connection |
| Laser not detecting | Align Tx and Rx modules properly |

## Safety Notes
- ⚠️ Do not point the laser beam at eyes
- ⚠️ Ensure proper voltage levels for all components
- ⚠️ Double-check connections before powering up
- Keep laser path clear of reflective surfaces

## Contributing
1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a new Pull Request

## License
This project is open-source and available under the MIT License.

## Authors
- Faranux Team

## Version History
- (2025-08-01): Initial release