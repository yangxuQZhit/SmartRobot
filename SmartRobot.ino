#include <HardwareSerial.h>

#define BUFFER_SIZE 10

extern HardwareSerial Serial3;
extern HardwareSerial Serial;

String mVersion = "0e.01.018";

int incomingByte = 0;
unsigned char buffers[BUFFER_SIZE];

void connect() {
  Serial3.write(0xff);
  Serial3.write(0x55);
  Serial3.write(0x00);  //command_index
  Serial3.write(0x04);
  Serial3.write(mVersion.length());   //length
  Serial3.write(mVersion.c_str());
  Serial3.println();
}

void printBuffer(unsigned char *buffer) {
  for (size_t i = 0; i < BUFFER_SIZE; i++) {
    /* code */
    Serial.print(buffers[i], DEC);
    Serial.print("\t");
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
}

void loop() {
  connect();
  if (Serial3.available() > 0) {
    Serial3.readBytes(buffers, BUFFER_SIZE);
    printBuffer(buffers);
  }
}
