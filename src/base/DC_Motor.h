/**
 * 直流电机类
 */

class DC_Motor {
public:
  DC_Motor();
  DC_Motor(uint8_t pin_h1, uint8_t pin_h2, uint8_t pin_pwm);
  ~DC_Motor();

  void run(int16_t speed);

private:
  uint8_t _pin_h1;//使能引脚1
  uint8_t _pin_h2;//使能引脚2
  uint8_t _pin_pwm;//速度引脚
  int16_t _last_speed;
};

DC_Motor::DC_Motor() {
  _pin_h1 = 0;
  _pin_h2 = 0;
  _pin_pwm = 0;
  _last_speed = 500;
}

DC_Motor::~DC_Motor() {}

DC_Motor::DC_Motor(uint8_t pin_h1, uint8_t pin_h2, uint8_t pin_pwm) {
  _pin_h1 = pin_h1;
  _pin_h2 = pin_h2;
  _pin_pwm = pin_pwm;
  _last_speed = 500;

  pinMode(_pin_h1, OUTPUT);
  pinMode(_pin_h2, OUTPUT);
}

void DC_Motor::run(int16_t speed) {
  speed = speed > 255 ? 255 : speed;
  speed = speed < -255 ? -255 : speed;

  if(_last_speed != speed) {
    _last_speed = speed;
  } else {
    return;
  }
 
  if(speed > 0) {//正转
    digitalWrite(_pin_h2, LOW);
    delayMicroseconds(5);
    digitalWrite(_pin_h1, HIGH);
    analogWrite(_pin_pwm,speed);
  } else if(speed < 0) {//反转
    digitalWrite(_pin_h1, LOW);
    delayMicroseconds(5);
    digitalWrite(_pin_h2, HIGH);
    analogWrite(_pin_pwm,-speed);
  } else {//停止
    digitalWrite(_pin_h2, LOW);
    digitalWrite(_pin_h1, LOW);
    analogWrite(_pin_pwm,0);
  }
}