#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Presenter remote", "William Grover", 100);
int lastSteadyState = LOW;
int lastFlickerableState = LOW;
int currentState;
unsigned long lastDebounceTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    bleKeyboard.write(KEY_RIGHT_ARROW);
    delay(1000);
    bleKeyboard.write(KEY_LEFT_ARROW);
    delay(1000);
  }
}
