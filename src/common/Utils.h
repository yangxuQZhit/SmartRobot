#include <PinDef.h>

class Utils {
public:
  Utils(/* args */);
  ~Utils();

  static void readSerial3();
  static void writeBuffer(int16_t index, uint8_t c);
  static void writeSerial(uint8_t c);
  static uint8_t readBuffer(int16_t index);
  static void writeHead();
  static void writeEnd();
  static void sendString(String s);
  static void sendFloat(float value);
};

Utils::Utils(/* args */)
{
}

Utils::~Utils()
{
}


void Utils::readSerial3() {
  
}