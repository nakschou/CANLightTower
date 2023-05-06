#include <can-serial.h>
#include <mcp2515_can.h>
#include <mcp_can.h>
#include <WatchDog.h>
#include <SPI.h>
#include "mcp_can.h"


const int SPI_CS_PIN = 17;  //Can Bus CS pin using LONGAN library
int pin8 = 8;   //Initialize pins for sending signals to the relay
int pin9 = 9;
int pin10 = 10;
int pin11 = 11;

String readString;    //Initialize strings for reading Can-Bus signals
String color;
String timeInterval;
String count;

int dash1; // '-' locations   //Initialize Can-Bus signal delimiters
int dash2;
int dash3;

unsigned long timer = millis();   //Initialize variables for time dependent color patterns
unsigned long flag1 = 0;
unsigned long flag2 = 0;
static unsigned long heartHold = 250;
long heartTimer = 0;
long colorTimer = 0;
long counter = 0;
long interval = 0;
int division = 0;


//Total runtime of the process. Used for timer purposes

mcp2515_can CAN(SPI_CS_PIN);   //Set CS Pin using SEEED Library


void setup()
{
  // Ensure that can bus signals can be received
  Serial.begin(115200);
  while (!Serial);
  while (CAN_OK != CAN.begin(CAN_500KBPS))
  {
    Serial.println("CAN BUS FAIL!");
    delay(100);
  }
  Serial.println("CAN BUS OK!");


  // Define pins as outputs
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  pinMode(pin10, OUTPUT);
  pinMode(pin11, OUTPUT);

  WatchDog::init(OVF_500MS);
}
/*
  void WatchDog()
  {

  }
*/
void loop()
{
  attachInterrupt(digitalPinToInterrupt(SPI_CS_PIN), MCP2515_ISR, RISING);   //Trigger an interrupt whenever a new CAN-BUS signal is received

  unsigned char len = 0;    //Variables which acquire Can-Bus message data
  unsigned char buf[8];

  if (CAN_MSGAVAIL == CAN.checkReceive())
  {
    CAN.readMsgBuf(&len, buf);    // read data.  len = data length, buf = data buffer

    unsigned long canId = CAN.getCanId();

    Serial.println("-----------------------------");   //Give metadata/ID info about CAN signal
    Serial.print("Get data from ID: ");
    Serial.println(canId, HEX);

    for (int i = 0; i < len; i++) // print the data
    {
      Serial.print(buf[i], HEX);
      Serial.print("\t");
    }

    counter = timer;   //Set "counter" to the time when a signal is received
    heartTimer = timer; //Update heartTimer whenever a CAN signal is received
  }

  String readString = buf;   //Turn CAN message into readable stirng

  // Parse Can-Bus data into workable Strings
  dash1 = readString.indexOf('-');  //finds location of first '-'
  color = readString.substring(0, dash1);   //captures first data String
  dash2 = readString.indexOf('-', dash1 + 1); //finds location of second '-'
  timeInterval = readString.substring(dash1 + 1, dash2); //captures second data String
  count = readString.substring(dash2 + 1); //captures remain part of data after last '-'

  // Print the parts of the message just to make sure everything is received properly
  /*
    Serial.print("color = ");
    Serial.println(color);
    Serial.print("hold time = ");
    Serial.println(timeInterval);
    Serial.print("number of times = ");
    Serial.println(count);
  */

  // Heartbeat conditions
  flag1 = (timer - heartTimer) >= heartHold;
  interval = timer - counter;
  division = interval / heartHold;

  if (division % 2 == 0) && (flag1 == 1)
  {
    digitalWrite(pin10, HIGH)
  }

  else if (division % 2 == 1) && (flag1 == 1)
  {
    digitalWrite(pin10, LOW)
  }


  // Color signal conditions

  if (timeInterval == "1")
  {
    digitalWrite(pin11, HIGH);
  }

  else if (timeInterval == "0")
  {
    digitalWrite(pin11, LOW);
  }

  else
  {
    flag2 = (timer - colorTimer) >= timeInterval;
    for i = 1 : count
      {
        if (color == "buzzer") && (flag2 == 1)
          {
            digitalWrite(pin11, HIGH);
          }

      else if (color == "buzzer") && (flag2 == 0)
          {
            digitalWrite(pin11, LOW);
          }
      }
   }

  /*
    if (color == "red")
    {
      digitalWrite(pin10, HIGH);
    }

    if (color == "green")
    {
      digitalWrite(pin9, HIGH);
    }
    else
    {
      digitalWrite(pin9, LOW);
    }

    if (color == "yellow")
    {
      digitalWrite(pin8, HIGH);
    }
    else
    {
      digitalWrite(pin8, LOW);
    }

    }
    }
