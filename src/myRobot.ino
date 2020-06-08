#include <HardwareSerial.h>

extern HardwareSerial Serial3;

#define DATA_SERIAL                            0
#define DATA_SERIAL1                           1
#define DATA_SERIAL2                           2
#define DATA_SERIAL3                           3

#define GET 1
#define RUN 2
#define RESET 4
#define START 5

#define VERSION                0

boolean isAvailable = false;
boolean isStart = false;
uint8_t prevc=0;
uint8_t index = 0;
uint8_t command_index = 0;
uint8_t dataLen;
uint8_t bufferBt2[52];

uint8_t BluetoothSource = DATA_SERIAL;
uint8_t serialRead;

String mVersion = "0e.01.018";

union
{
  uint8_t byteVal[4];
  float floatVal;
  long longVal;
}val;

void readSerial3() {
  isAvailable = false;
  if(Serial3.available() > 0) {
    isAvailable = true;
    BluetoothSource = DATA_SERIAL3;
    serialRead = Serial3.read();
  }
}

void writeBuffer(int16_t index, uint8_t c) {
  if(BluetoothSource == DATA_SERIAL3)
  {
    bufferBt2[index]=c;
  }
}

void writeSerial(uint8_t c) {
  if (BluetoothSource == DATA_SERIAL3) {
    Serial3.write(c);
  }
}

uint8_t readBuffer(int16_t index) {
  if (BluetoothSource == DATA_SERIAL3) {
    return bufferBt2[index];
  }
}

void writeHead()
{
  writeSerial(0xff);
  writeSerial(0x55);
}

void writeEnd() {
  if (BluetoothSource == DATA_SERIAL3) {
    Serial3.println();
  }
}

void sendString(String s) {
  int16_t l = s.length();
  writeSerial(4);
  writeSerial(l);
  for(int16_t i=0;i<l;i++)
  {
    writeSerial(s.charAt(i));
  }
}

void sendFloat(float value) {
  writeSerial(2);
  val.floatVal = value;
  writeSerial(val.byteVal[0]);
  writeSerial(val.byteVal[1]);
  writeSerial(val.byteVal[2]);
  writeSerial(val.byteVal[3]);
}

void readSensor(uint8_t device) {
  writeHead();
  writeSerial(command_index);
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

void parseData() {
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

void setup() {
  // put your setup code here, to run once:
  Serial3.begin(115200);
  while (!Serial3) {}
}

void loop() {
  // put your main code here, to run repeatedly:
  readSerial3();
  while(isAvailable)
  {
    unsigned char c = serialRead & 0xff;
    if((c == 0x55) && (isStart == false))
    {
      if(prevc == 0xff)
      {
        index=1;
        isStart = true;
      }
    }
    else
    {
      prevc = c;
      if(isStart)
      {
        if(index == 2)
        {
          dataLen = c; 
        }
        else if(index > 2)
        {
          dataLen--;
        }
        writeBuffer(index,c);
      }
    }
    index++;
    if(index > 51)
    {
      index=0; 
      isStart=false;
    }
    if(isStart && (dataLen == 0) && (index > 3))
    { 
      isStart = false;
      parseData(); 
      index=0;
    }
    readSerial3();
  }
}
