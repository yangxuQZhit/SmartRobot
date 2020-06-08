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
  void readSensor(uint8_t device);
  void parseData();

  void readSerial3();
  void writeBuffer(int16_t index, uint8_t c);
  uint8_t readBuffer(int16_t index);
  void writeHead();
  void writeEnd();
  void sendString(String s);
  void sendFloat(float value);

private:
  bool isAvailable = false;
  bool isStart = false;
  uint8_t prevc = 0;
  uint8_t index = 0;
  uint8_t command_index = 0;
  uint8_t dataLen;
  uint8_t bufferBt2[52];
  uint8_t serialRead;

  String mVersion = "0e.01.018";
};

Bluetooth::Bluetooth() {}
Bluetooth::~Bluetooth() {}

void Bluetooth::connect() {
  Serial3.begin(115200);
  while (!Serial3) {}
}

void Bluetooth::run() {
  readSerial3();
  while(isAvailable) {
    unsigned char c = serialRead & 0xff;
    if((c == 0x55) && (isStart == false)) {
      if(prevc == 0xff) {
        index=1;
        isStart = true;
      }
    }
    else {
      prevc = c;
      if(isStart) {
        if(index == 2) {
          dataLen = c; 
        }
        else if(index > 2) {
          dataLen--;
        }
        writeBuffer(index,c);
      }
    }
    index++;
    if(index > 51) {
      index=0; 
      isStart=false;
    }
    if(isStart && (dataLen == 0) && (index > 3)) { 
      isStart = false;
      parseData(); 
      index=0;
    }
    readSerial3();
  }
}

void Bluetooth::readSensor(uint8_t device) {
  writeHead();
  Serial3.write(command_index);
  switch (device)
  {
  case VERSION:
    sendString(mVersion);
    break;
  
  default:
    sendFloat(0);
    break;
  }
}

void Bluetooth::parseData() {
  isStart = false;
  uint8_t action = readBuffer(4);
  uint8_t device = readBuffer(5);

  switch (action)
  {
  case GET:
    readSensor(device);
    writeEnd();
    break;
  
  default:
    break;
  }
}

void Bluetooth::readSerial3() {
  isAvailable = false;
  if(Serial3.available() > 0) {
    isAvailable = true;
    serialRead = Serial3.read();
  }
}

void Bluetooth::writeBuffer(int16_t index, uint8_t c) {
  bufferBt2[index] = c;
}

uint8_t Bluetooth::readBuffer(int16_t index) {
  return bufferBt2[index];
}

void Bluetooth::writeHead() {
  Serial3.write(0xff);
  Serial3.write(0x55);
}

void Bluetooth::writeEnd() {
  Serial3.println();
}

void Bluetooth::sendString(String s) {
  int16_t l = s.length();
  Serial3.write(4);
  Serial3.write(l);
  for(int16_t i = 0; i < l; i++)
  {
    Serial3.write(s.charAt(i));
  }
}

void Bluetooth::sendFloat(float value) {
  Serial3.write(2);
  val.floatVal = value;
  Serial3.write(val.byteVal[0]);
  Serial3.write(val.byteVal[1]);
  Serial3.write(val.byteVal[2]);
  Serial3.write(val.byteVal[3]);
}


