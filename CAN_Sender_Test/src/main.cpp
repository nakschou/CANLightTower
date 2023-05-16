#include "mbed.h" // This is a required library for the CANMessage object(may be the wrong term)

/*

The code below is one way to build a CAN message data packet using the 
mbed.h library funtionalities. We pick an identifier and choose the value
of the first data packet to fepresent our current functions.

1.Steady green light - autonomous
2.Flashing Green & rotating yellow - receiving commands from agx for throttle and in auto mode
3.Steady Yellow - manual mode receiving throttle commands from remote
4.flashing yellow and rotating yellow
5.slow flash red - no comm from rtc to arduino
6.fast flash red - no comma from agx to rtc(may be a tricky one) 
7.steady red - Unused at this time
8.turn all off - called before any new light function

*/

CAN can(PD_0, PD_1, 500000); // CAN interface pins and baud rate
//The line above establishes a connectionn with CAN bus 1
//PD_0 represents RD and PD_1 represents TD on the RTC pinout
int main() {
    CANMessage msg;//Initialize a can message
    //The identifier is used to filter out the important messages coming through the can bus
    //we dont want to use all of the data on the bus just the light tower specific stuff
    msg.id = 0x12345678;       // Extended message identifier; This can be reduced to 0x000 for an 11 bit identifier(we can pick this ID)
    msg.len = 8;               // Data length (we will use 8 bytes)
    msg.format = CANExtended;  // Set frame format to extended; This line can be omitted if an 11 bit identifier is desired
    msg.data[0] = 0x01;        // Data byte 0; We use this to send a single digit command to the Arduino CAN board
    msg.data[1] = 0x00;        // Data byte 1
    msg.data[2] = 0x00;        // Data byte 2
    msg.data[3] = 0x00;        // Data byte 2
    msg.data[4] = 0x00;        // Data byte 4
    msg.data[5] = 0x00;        // Data byte 5
    msg.data[6] = 0x00;        // Data byte 6
    msg.data[7] = 0x00;        // Data byte 7
    
    while (1) {//While loop used to send to the canbus at the 500Kbits/sec
        // It seems like this is the line we would insert into the RTC code to write to the existing
        // FIFO queue.
        can.write(msg);        // Send the CAN message
        //wait_us(1000 * 1000);   //Wait 1 second
        printf("In the while loop");
    }
}