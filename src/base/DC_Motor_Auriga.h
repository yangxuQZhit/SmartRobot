class DC_Motor_Auriga
{
private:
  /* data */
  uint8_t _pin_pwm;
  uint8_t _pin_direction;
  int16_t _last_speed;
public:
  DC_Motor_Auriga(/* args */);
  ~DC_Motor_Auriga();

  DC_Motor_Auriga(uint8_t pin_pwm, uint8_t pin_direction);

  void run(int16_t speed);
};

DC_Motor_Auriga::DC_Motor_Auriga(/* args */) {
  _pin_pwm = 0;
  _pin_direction = 0;
  _last_speed = 100;
}

DC_Motor_Auriga::~DC_Motor_Auriga() {}

DC_Motor_Auriga::DC_Motor_Auriga(uint8_t pin_pwm, uint8_t pin_direction) {
  _pin_pwm = pin_pwm;
  _pin_direction = pin_direction;
  _last_speed = 100;

  pinMode(_pin_direction, OUTPUT);
}

void DC_Motor_Auriga::run(int16_t speed) {
  speed	= speed > 255 ? 255 : speed;
  speed	= speed < -255 ? -255 : speed;

  if(_last_speed != speed) {
    _last_speed = speed;
  } else {
    return;
  }

  if(speed >= 0) {//正转
    digitalWrite(_pin_direction, HIGH);
    delayMicroseconds(5);
    analogWrite(_pin_pwm, speed);
  } else {//反转
    digitalWrite(_pin_direction, LOW);
    delayMicroseconds(5);
    analogWrite(_pin_pwm, -speed);
  }
}
