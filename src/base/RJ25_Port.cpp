#include "RJ25_Port.h"

RJ25_Port::RJ25_Port() {
  _pin_1 = 0;
  _pin_2 = 0;
}

RJ25_Port::RJ25_Port(uint8_t pin_1, uint8_t pin_2) {
  _pin_1 = pin_1;
  _pin_2 = pin_2;
}

bool RJ25_Port::digital_read(uint8_t pin, uint8_t mode) {
  pinMode(pin, mode);
  return digitalRead(pin);
}

void RJ25_Port::digital_write(uint8_t pin, bool value) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, value);
}

int16_t RJ25_Port::analog_read(uint8_t pin) {
  pinMode(pin, INPUT);
  return analogRead(pin);
}

void RJ25_Port::analog_write(uint8_t pin, int16_t value) {
  pinMode(pin, OUTPUT);
  analogWrite(pin, value);
}

uint8_t RJ25_Port::get_pin_1() {
  return _pin_1;
}

uint8_t RJ25_Port::get_pin_2() {
  return _pin_2;
}