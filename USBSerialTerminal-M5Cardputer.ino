#include "M5Cardputer.h"
#include "M5GFX.h"
#include <M5Unified.h> // Ensure broader support with M5Stack devices

M5Canvas canvas(&M5Cardputer.Display);
String data = "> ";

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    Serial.begin(115200); // Start Serial over USB at 115200 baud rate
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextSize(1.0);
    M5Cardputer.Display.drawRect(0, 0, M5Cardputer.Display.width(), M5Cardputer.Display.height() - 28, GREEN);
    M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 4, M5Cardputer.Display.width(), 4, GREEN);
    
    canvas.setTextSize(1.0);
    canvas.createSprite(M5Cardputer.Display.width() - 8, M5Cardputer.Display.height() - 36);
    canvas.setTextScroll(true);
    canvas.println("USB Serial Terminal Ready");
    canvas.pushSprite(4, 4);
    M5Cardputer.Display.drawString(data, 4, M5Cardputer.Display.height() - 24);
}

void loop() {
    M5Cardputer.update();
    // Check if there is incoming serial data over USB
    while (Serial.available()) {
        char incomingByte = Serial.read();
        // Only add printable characters or new line, exclude control characters
        if (isPrintable(incomingByte) || incomingByte == '\n') {
            data += incomingByte;
        }
        
        // If incomingByte is newline, print and reset data string
        if (incomingByte == '\n') {
            canvas.println(data);
            canvas.pushSprite(4, 4);
            data = "> ";
        }
    }

    // Keyboard input handling
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            // Handling keyboard input
            for (auto i : status.word) {
                if (i) { // Check if character is not null
                    data += i;
                    Serial.write(i); // Send character over USB Serial
                }
            }

            if (status.del && data.length() > 2) { // Prevent deletion of "> "
                data.remove(data.length() - 1);
                Serial.write('\b'); // Send backspace character over USB Serial
            }

            if (status.enter) {
                Serial.println(); // Send newline over USB Serial to emulate Enter key
                data.remove(0, 2); // Clear the "> " at the beginning of the string
                canvas.println("> " + data);
                canvas.pushSprite(4, 4);
                data = "> ";
            }

            // Clear and redraw the text area
            M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 28, M5Cardputer.Display.width(), 25, BLACK);
            M5Cardputer.Display.drawString(data, 4, M5Cardputer.Display.height() - 24);
        }
    }
}