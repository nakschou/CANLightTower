/*
  This Code is a basic recieve function that checks the 8th element of the data frame from a CAN signal
*/

#include <SPI.h>
#include "mcp_can.h"
#include <MCP_CAN.h> 

#define SPI_CS_PIN  17 

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    
    Serial.begin(115200);
    while(!Serial);
        
    while (CAN_OK != CAN.begin( CAN_500KBPS))    // init can bus : baudrate = 500k
    {
      //blink
    }
    Serial.println("I am the Reciever and the CAN BUS is OK!");
}

void loop(){
    unsigned char len = 0;
    unsigned char buf[8];
    byte ext = 0;  
    if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
            
        //CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf
        CAN.readMsgBuf(&len, buf);

        unsigned long canId = CAN.getCanId();
        
        Serial.println("-----------------------------");
        Serial.print("Here is the extended id:");
        Serial.println(canId);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i]);
            Serial.print("\t");
        }
        if(buf[0] == 1) // This is a simple way to check what data is in the 8 element data array
                        // Can be exteded to recognize our values Color-Time-repetitions
          Serial.println("This is where I like to blink");
        
        Serial.println();
    }
}

// END FILE
