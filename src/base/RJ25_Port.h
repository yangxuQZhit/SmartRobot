class RJ25_Port {
public:
  RJ25_Port();
  RJ25_Port(uint8_t pin_1, uint8_t pin_2);
  
  bool digital_read(uint8_t pin, uint8_t mode);
  void digital_write(uint8_t pin, bool value);

  int16_t analog_read(uint8_t pin);
  void analog_write(uint8_t pin, int16_t value);

  uint8_t get_pin_1();
  uint8_t get_pin_2();
private:
  uint8_t _pin_1;
  uint8_t _pin_2;
};