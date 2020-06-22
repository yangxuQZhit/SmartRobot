#include <HardwareSerial.h>

extern HardwareSerial Serial2;

class USB_Host {
public:
  USB_Host();
  ~USB_Host();

  void init(uint8_t baud_rate);
private:

};

USB_Host::USB_Host() {}
USB_Host::~USB_Host() {}

void USB_Host::init(uint8_t baud_rate) {
  Serial2.begin(baud_rate);
}