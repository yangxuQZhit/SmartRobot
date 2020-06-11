#include <HardwareSerial.h>
#include "src/base/DC_Motor_Auriga.h"
// #include "Arduino.h"
#include <SoftwareSerial.h>
#include <MeAuriga.h>

#define BUFFER_SIZE 52

extern HardwareSerial Serial;

String mVersion = "09.01.016";//Makeblock MeAuriga V1.3 开发板

int incomingByte = 0;
unsigned char buffers[BUFFER_SIZE];
DC_Motor_Auriga dc(5, 4);           //直流电机
MeSmartServo mysmartservo(PORT5);   //智能舵机

uint8_t serialRead;
boolean isStart = false;
boolean isAvailable = false;
uint8_t index = 0;
uint8_t dataLen;
uint8_t prevc=0;

union {
  uint8_t byte_value[2];
  int16_t short_value;
} speed;

void connect() {//连接移动app
  Serial.write(0xff);
  Serial.write(0x55);
  Serial.write(0x00);  
  Serial.write(0x04);
  Serial.write(mVersion.length());   
  Serial.write(mVersion.c_str());
  Serial.println();
}

void printBuffer(unsigned char *buffer) {
  for (size_t i = 0; i < 10; i++) {
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

void readSerial(void)
{
  isAvailable = false;
  if(Serial.available() > 0)
  {
    isAvailable = true;
    serialRead = Serial.read();
  }
}

void runDevice(uint8_t device_id) {
  switch (device_id){
    case 5://遥控杆
      Serial.print("left_speed: ");
      Serial.println(get_left_speed(buffers));
      dc.run(get_left_speed(buffers));
      break;
    case 11://舵机
      select_cmd(buffers[6]);
      break;
    default:
      break;
  }
}

void select_cmd(uint8_t cmd) {
  switch (cmd)
  {
  case 6://命令1
    /* code */
    mysmartservo.moveTo(1,360,50);
    break;
  case 7://命令2
    /* code */
    mysmartservo.moveTo(1,-360,50);
    break;
  case 8://命令3
    /* code */
    break;
  case 9://命令4
    /* code */
    break;
  default:
    break;
  }
}

void setup() {
  Serial.begin(115200);
  mysmartservo.begin(115200);
  // delay(5);
  mysmartservo.assignDevIdRequest();
  // delay(50);
}

void loop() {//while循环可以优化
  if(Serial.available() > 0) {
    serialRead = Serial.read();
    isAvailable = true;
  }
  while(isAvailable) {
    unsigned char c = serialRead & 0xff;
    if((c == 0x55) && (isStart == false)) {
      if(prevc == 0xff) {
        index=1;
        isStart = true;
      }
    } else {
      prevc = c;
      if(isStart) {
        if(index == 2) {
          dataLen = c; 
        } else if(index > 2) {
          dataLen--;
        }
        buffers[index] = c;
      }
    }
    index++;
    if(index > BUFFER_SIZE - 1) {
      index=0; 
      isStart=false;
    }
    if(isStart && (dataLen == 0) && (index > 3)) { 
      isStart = false;
      switch(buffers[4]) {
        case 1://GET
          connect();
          break;
        case 2://RUN
          printBuffer(buffers);
          runDevice(buffers[5]);
          break;
      }
      index=0;
    }
    isAvailable = false;
    if(Serial.available() > 0) {
      isAvailable = true;
      serialRead = Serial.read();
    }
  }
}
