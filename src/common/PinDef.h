#define DATA_SERIAL       0
#define DATA_SERIAL1      1
#define DATA_SERIAL2      2
#define DATA_SERIAL3      3

#define GET               1
#define RUN               2
#define RESET             4
#define START             5

#define VERSION           0

union{
  uint8_t byteVal[4];
  float floatVal;
  long longVal;
}val;