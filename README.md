## Installation

1. **Install the Arduino IDE**: Download and install the Arduino IDE from the [official website](https://www.arduino.cc/en/Main/Software).

2. **Setup the M5Stack Board Manager**:
   - Open the Arduino IDE, go to File > Preferences.
   - In the "Additional Board Manager URLs" field, add the following URL:  
     `https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json`
   - Open Tools > Board: > Boards Manager... and search for "M5Stack".
   - Install the M5Stack board support package.

3. **Install Required Libraries**:
   - Open the Library Manager by navigating to Sketch > Include Library > Manage Libraries...
   - Search for `M5Unified` and `M5GFX` and install them. Make sure these libraries are compatible with the M5Cardputer.

4. **Load the Sketch**:
   - Copy the provided code into a new Arduino sketch.
   - Select the appropriate board (likely under an M5Stack heading) and the correct port under the Tools menu.
   - Upload the sketch to your M5Cardputer.

## Usage

- After uploading the sketch, the M5Cardputer will display "USB Serial Terminal Ready".
- Use the M5Cardputer's built-in keyboard to type and send data over USB.
- Incoming serial data from the USB connection will be displayed on the M5Cardputer's screen.
- Press the enter key to send your typed data; use the backspace key to correct any input before sending.

## Contributing

Contributions to this project are welcome. Feel free to fork the repository, make your changes, and submit a pull request.

## License

This project is released under the MIT License. See the LICENSE file in the repository for more details.

## Acknowledgements

- Thanks to the M5Stack community for providing the resources and support necessary to develop this project.
