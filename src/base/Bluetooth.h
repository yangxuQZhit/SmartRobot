#include <HardwareSerial.h>
#include "../common/PinDef.h"

extern HardwareSerial Serial3;

class Bluetooth {
public:
  Bluetooth();
  ~Bluetooth();

  void connect();
  void run();

private:
  String mVersion = "0e.01.018";
};

Bluetooth::Bluetooth() {}
Bluetooth::~Bluetooth() {}

void Bluetooth::connect() {
  Serial3.begin(115200);
  while (!Serial3) {}
}

void Bluetooth::run() {
  Serial3.write(0xff);
  Serial3.write(0x55);
  Serial3.write(0x00);//command_index
  Serial3.write(0x04);
  Serial3.write(mVersion.length());
  for(int16_t i = 0; i < mVersion.length(); i++) {
    Serial3.write(mVersion.charAt(i));
  }
  Serial3.println();
}


