#include "M5Cardputer.h"
#include "M5GFX.h"
#include <M5Unified.h> // Ensure broader support with M5Stack devices

M5Canvas canvas(&M5Cardputer.Display);
String data = "> ";
unsigned long lastKeyPressTime = 0; // Store the last key press time
const unsigned long debounceDelay = 200; // Debounce delay in milliseconds

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
    unsigned long currentTime = millis();

    // Check if there is incoming serial data over USB
    while (Serial.available()) {
        char incomingByte = Serial.read();
        if (isPrintable(incomingByte) || incomingByte == '\n') {
            if (incomingByte == '\n') {
                canvas.println();
            } else {
                canvas.print(incomingByte);
            }
            canvas.pushSprite(4, 4);
        }
    }

    // Keyboard input handling with debounce
    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed() && currentTime - lastKeyPressTime > debounceDelay) {
        Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

        for (auto i : status.word) {
            if (i && i != '\b') {
                data += i;
            }
        }

        if (status.del && data.length() > 2) {
            data.remove(data.length() - 1);
        }

        if (status.enter) {
            Serial.println(data.substring(2));
            canvas.println(data);
            data = "> ";
            canvas.pushSprite(4, 4);
        }

        // Refresh the input area with current buffer content
        M5Cardputer.Display.fillRect(0, M5Cardputer.Display.height() - 28, M5Cardputer.Display.width(), 24, BLACK);
        M5Cardputer.Display.drawString(data, 4, M5Cardputer.Display.height() - 24);
        
        lastKeyPressTime = currentTime; // Update the last key press time
    }
}
