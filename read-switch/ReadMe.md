# Reed Switch Arduino Project

This project demonstrates how to interface a reed switch with an Arduino board to detect the presence of a magnetic field. The system uses an LED to provide visual feedback of the switch state.

## Hardware Requirements

- Arduino board (Any Arduino board will work)
- Reed switch
- LED (optional, as we're using the built-in LED)
- 10kΩ pull-up resistor (optional, not needed if using internal pull-up)
- Jumper wires
- Magnet for testing

## Pin Configuration

- Reed Switch: Connected to Digital Pin 2
- LED: Built-in LED on Pin 13

## Circuit Description

The project uses a reed switch with Arduino's internal pull-up resistor. If you prefer using an external pull-up resistor:

1. Disable the internal pull-up by removing `INPUT_PULLUP` and using just `INPUT`
2. Connect a 10kΩ resistor between the reed switch pin and 5V
3. Connect the reed switch between the digital pin and GND

### Circuit Options:

1. Using internal pull-up (current setup):
   - Reed switch between PIN 2 and GND
   - No external resistor needed

2. Using external pull-up:
   - 10kΩ resistor between PIN 2 and 5V
   - Reed switch between PIN 2 and GND

## How It Works

1. When no magnet is present:
   - Reed switch remains open
   - Digital pin reads HIGH
   - LED remains OFF
   - Serial monitor shows "Switch opened"

2. When magnet is nearby:
   - Reed switch closes
   - Digital pin reads LOW
   - LED turns ON
   - Serial monitor shows "Switch closed"

## Installation

1. Connect the reed switch between digital pin 2 and GND
2. Upload the provided Arduino sketch to your board
3. Open serial monitor at 9600 baud to see the switch state

## Files Included

- `read-switch-arduino.ino`: Arduino sketch file
- `schematic/read_switch.svg`: Circuit schematic
- `schematic/read_switch_breadboard.svg`: Breadboard layout

## Debugging

If you're having issues:
1. Check all wire connections
2. Verify the reed switch isn't damaged
3. Ensure the magnet is strong enough
4. Monitor the serial output at 9600 baud

## License

This project is open source and available under the MIT License.

## Contributing

Feel free to submit issues and enhancement requests.