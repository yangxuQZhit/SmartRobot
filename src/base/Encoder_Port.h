class Encoder_Port {
public:
  Encoder_Port();
  Encoder_Port(uint8_t pin_A, uint8_t pin_B, uint8_t pin_PWM, 
               uint8_t pin_H1, uint8_t pin_H2);

  uint8_t get_pin_A();
  uint8_t get_pin_B();
  uint8_t get_pin_PWM();
  uint8_t get_pin_H1();
  uint8_t get_pin_H2();
private:
  uint8_t _pin_A;
  uint8_t _pin_B;
  uint8_t _pin_PWM;
  uint8_t _pin_H1;
  uint8_t _pin_H2;
};