#include "./base/Bluetooth.h"

Bluetooth bluetooth;

void setup() {
  bluetooth.connect();
}

void loop() {
  bluetooth.run();
}
