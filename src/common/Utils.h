class Utils {
public:
  static void readSerial3();
  static void writeBuffer(int16_t index, uint8_t c);
  static void writeSerial(uint8_t c);
  static uint8_t readBuffer(int16_t index);
  static void writeHead();
  static void writeEnd();
  static void sendString(String s);
  static void sendFloat(float value);
};

void Utils::readSerial3() {
  isAvailable = false;
  if(Serial3.available() > 0) {
    isAvailable = true;
    BluetoothSource = DATA_SERIAL3;
    serialRead = Serial3.read();
  }
}

void Utils::writeBuffer(int16_t index, uint8_t c) {
  if(BluetoothSource == DATA_SERIAL3)
  {
    bufferBt2[index]=c;
  }
}

void Utils::writeSerial(uint8_t c) {
  if (BluetoothSource == DATA_SERIAL3) {
    Serial3.write(c);
  }
}

uint8_t Utils::readBuffer(int16_t index) {
  if (BluetoothSource == DATA_SERIAL3) {
    return bufferBt2[index];
  }
}

void Utils::writeHead() {
  writeSerial(0xff);
  writeSerial(0x55);
}

void Utils::writeEnd() {
  if (BluetoothSource == DATA_SERIAL3) {
    Serial3.println();
  }
}

void Utils::sendString(String s) {
  int16_t l = s.length();
  writeSerial(4);
  writeSerial(l);
  for(int16_t i=0;i<l;i++)
  {
    writeSerial(s.charAt(i));
  }
}

void Utils::sendFloat(float value) {
  writeSerial(2);
  val.floatVal = value;
  writeSerial(val.byteVal[0]);
  writeSerial(val.byteVal[1]);
  writeSerial(val.byteVal[2]);
  writeSerial(val.byteVal[3]);
}

