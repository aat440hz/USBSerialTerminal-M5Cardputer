# M5Cardputer USB Serial Terminal

This project transforms your M5Cardputer into a USB serial terminal, allowing it to communicate with a PC or other USB serial devices. Utilizing the M5Cardputer's built-in keyboard for input and its display for output, this application creates an interactive terminal experience.

## Features

- **USB Serial Communication**: Communicate with a PC or other devices over USB at 115200 baud rate.
- **Interactive Display**: Utilizes the M5Cardputer's display to show incoming data and input text.
- **Keyboard Input**: Leverage the M5Cardputer's built-in keyboard for sending data over USB.

## Requirements

- M5Stack M5Cardputer
- Arduino IDE
- M5Stack library for Arduino (M5Unified, M5GFX)

## Installation

1. **Install the Arduino IDE**: Download and install the Arduino IDE from the [official website](https://www.arduino.cc/en/Main/Software).

2. **Setup the M5Stack Board Manager**:
   - Open the Arduino IDE, go to File > Preferences.
   - In the "Additional Board Manager URLs" field, add the following URL:  
     `https://dl.espressif.com/dl/package_esp32_index.json`
   - Open Tools > Board: > Boards Manager... and install the esp32 platform.

3. **Install Required Libraries**:
   - Open the Library Manager by navigating to Sketch > Include Library > Manage Libraries...
   - Search for `M5Unified` and `M5GFX` and install them.

4. **Load the Sketch**:
   - Copy the provided code into a new Arduino sketch.
   - Select the appropriate board (M5Stack ESP32) and port under the Tools menu.
   - Upload the sketch to your M5Cardputer.

## Usage

- Upon loading the sketch, the M5Cardputer displays "USB Serial Terminal Ready".
- Type using the built-in keyboard to send data over USB.
- Incoming serial data will be displayed on the screen.
- Use the enter key to send data, and the backspace key to correct input.

## Contributing

Contributions to this project are welcome. Please feel free to fork the repository, make your changes, and submit a pull request.

## License

This project is released under the MIT License. See the LICENSE file for more details.

## Acknowledgements

- Thanks to the M5Stack community for providing the hardware and software support necessary to create this project.
