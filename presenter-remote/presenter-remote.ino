#include <BleKeyboard.h>
#include <esp_bt.h>

BleKeyboard bleKeyboard("Presenter remote", "William Grover", 100);
int lastSteadyState = LOW;
int lastFlickerableState = LOW;
int currentState;
unsigned long lastDebounceTime = 0;
unsigned long keepAliveTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
  esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9); 
  pinMode(21, INPUT_PULLUP);
  keepAliveTime = millis() + 1000;
}

void loop() {
  if(bleKeyboard.isConnected()) {
    currentState = digitalRead(21);
    if (currentState != lastFlickerableState) {
      lastDebounceTime = millis();
      lastFlickerableState = currentState;
    }
    if ((millis() - lastDebounceTime) > 50) {
      if(lastSteadyState == HIGH && currentState == LOW) {
        Serial.println("next");
        bleKeyboard.write(KEY_RIGHT_ARROW);
      }
      lastSteadyState = currentState;
    }
    if (millis() > keepAliveTime) {
      Serial.println("keep alive");
      bleKeyboard.write(KEY_LEFT_SHIFT);
      keepAliveTime = millis()+1000;
    }
  }
}
