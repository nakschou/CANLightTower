#include "mbed.h"

CAN can1(PD_0, PD_1);

int main()
{
  CANMessage msg;
  msg.id = 0x123;
  msg.len = 8;
  msg.data[0] = 0x01;
  msg.data[1] = 0x02;
  msg.data[2] = 0x03;
  msg.data[3] = 0x04;
  msg.data[4] = 0x05;
  msg.data[5] = 0x06;
  msg.data[6] = 0x07;
  msg.data[7] = 0x08;

while(1){
  if (can1.write(msg))
  {
    printf("CAN message sent successfully\r\n");
  }
  else
  {
    printf("Failed to send CAN message\r\n");
  }
}
}