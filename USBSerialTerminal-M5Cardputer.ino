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
        if (isPrintable(incomingByte) || incomingByte == '\n') {
            if (incomingByte == '\n') {
                canvas.println();
            } else {
                canvas.print(incomingByte);
            }
            // Only push the sprite update for incoming data, not for typed characters
            canvas.pushSprite(4, 4);
        }
    }

    // Keyboard input handling
    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

        for (auto i : status.word) {
            if (i && i != '\b') { // Check if character is not null and not backspace
                data += i; // Accumulate typing in the buffer but don't display it in the terminal feed
            }
        }

        if (status.del && data.length() > 2) { // Handle backspace by removing last character
            data.remove(data.length() - 1);
        }

        if (status.enter) {
            Serial.println(data.substring(2)); // Send buffered data over serial, excluding the "> " prompt
            canvas.println(data); // Now display the buffered line in the terminal feed
            data = "> "; // Reset buffer for new input
            canvas.pushSprite(4, 4); // Update the display to show the new line in terminal feed
        }

        // Refresh the input area with current buffer content (real-time typing feedback)
        M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 28, M5Cardputer.Display.width(), 24, BLACK);
        M5Cardputer.Display.drawString(data, 4, M5Cardputer.Display.height() - 24);
    }
}
