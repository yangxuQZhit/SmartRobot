#include <HardwareSerial.h>

#define BUFFER_SIZE 10

extern HardwareSerial Serial3;
extern HardwareSerial Serial;

String mVersion = "0e.01.018";

int incomingByte = 0;
unsigned char buffers[BUFFER_SIZE];

union {
  uint8_t byte_value[2];
  int16_t short_value;
} speed;

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

int16_t get_left_speed(unsigned char *buffers) {
  speed.byte_value[0] = buffers[6];
  speed.byte_value[1] = buffers[7];
  return speed.short_value;
}

int16_t get_right_speed(unsigned char *buffers) {
  speed.byte_value[0] = buffers[8];
  speed.byte_value[1] = buffers[9];
  return speed.short_value;
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
    Serial.print("left speed: ");
    Serial.println(get_left_speed(buffers));
    Serial.print("right speed: ");
    Serial.println(get_right_speed(buffers));
  }
}
