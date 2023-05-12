//#include <WatchDog.h>

/*Please Implement the folowing functions:
1.Steady green light
2.Flashing Green & rotating yellow
3.Steady Yellow
4.flashing yellow and rotating yellow
5.slow flash red
6.fast flash red
7.steady red
8.turn all off

*/
#include <can-serial.h>
#include <mcp2515_can.h>
#include <mcp_can.h>
#include <SPI.h>
#include "mcp_can.h"

const int heartbeatseizuretime = 100; //ms

const int SPI_CS_PIN = 17;  //Can Bus CS pin using LONGAN library
int RED_RELAY_PIN = 8;   //Initialize pins for sending signals to the relay
int YELLOW_RELAY_PIN = 9;
int GREEN_RELAY_PIN = 10;
int BUZZER_RELAY_PIN = 11;
int ROTATE_RELAY_PIN = 12;

String readString;    //Initialize strings for reading Can-Bus signals
String color;
String timeInterval;
String count;

int dash1; // '-' locations   //Initialize Can-Bus signal delimiters
int dash2;
int dash3;

unsigned long timer = millis();   //Initialize variables for time dependent color patterns
static unsigned long heartHold = 250;
long heartTimer = 0;
long interval = 0;
int division = 0;

unsigned long redbefore = millis();
unsigned long yellowbefore = millis();
unsigned long greenbefore = millis();
unsigned long buzzerbefore = millis();
unsigned long rotatebefore = millis();

unsigned int redcount = 0;
unsigned int yellowcount = 0;
unsigned int greencount = 0;
unsigned int buzzercount = 0;
unsigned int rotatecount = 0;

//Total runtime of the process. Used for timer purposes

mcp2515_can CAN(SPI_CS_PIN);   //Set CS Pin using SEEED Library


void setup() {
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
  pinMode(RED_RELAY_PIN, OUTPUT);
  pinMode(YELLOW_RELAY_PIN, OUTPUT);
  pinMode(GREEN_RELAY_PIN, OUTPUT);
  pinMode(BUZZER_RELAY_PIN, OUTPUT);

  //WatchDog::init(OVF_500MS);
}
/*
  void WatchDog()
  {

  }
*/
void loop() {
  unsigned char len = 0;    //Variables which acquire Can-Bus message data
  unsigned char buf[8];

  if (CAN_MSGAVAIL == CAN.checkReceive()) {  //Check if a CAN signal is available
    CAN.readMsgBuf(&len, buf);    // read data.  len = data length, buf = data buffer

    unsigned long canId = CAN.getCanId();

    //This is where we will add a switch statement to decide which of the functions to perform: steady red, flashing etc.

    heartTimer = timer; //Update heartTimer whenever a CAN signal is received
  }
  timer = millis(); //Update timer
  checkHeartBeat();

  boolean redcond = false; //example of a condition for a color signal
  if(redcond) {
    redcount = 5;
    red_relay_operation(heartbeatseizuretime, redcount);
  }
  // Color signal conditions

}

void red_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  if(now-redbefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(count == 0) {
      digitalWrite(RED_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(RED_RELAY_PIN, !digitalRead(RED_RELAY_PIN));
    redbefore = now;
    redcount = redcount - 1;
    //Serial.print(count);
  }
}

void yellow_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  //if the time has passed
  if(now-yellowbefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(count == 0) {
      digitalWrite(YELLOW_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(YELLOW_RELAY_PIN, !digitalRead(YELLOW_RELAY_PIN));
    yellowbefore = now;
    yellowcount = yellowcount - 1;
    //Serial.print(count);
  }
}

void green_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  if(now-greenbefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(count == 0) {
      digitalWrite(GREEN_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(GREEN_RELAY_PIN, !digitalRead(GREEN_RELAY_PIN));
    greenbefore = now;
    greencount = greencount - 1;
    //Serial.print(count);
  }
}

void buzzer_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  if(now-buzzerbefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(count == 0) {
      digitalWrite(BUZZER_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(BUZZER_RELAY_PIN, !digitalRead(BUZZER_RELAY_PIN));
    buzzerbefore = now;
    buzzercount = buzzercount - 1;
    //Serial.print(count);
  }
}

void rotate_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  if(now-rotatebefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(count == 0) {
      digitalWrite(ROTATE_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(ROTATE_RELAY_PIN, !digitalRead(ROTATE_RELAY_PIN));
    rotatebefore = now;
    rotatecount = rotatecount - 1;
    //Serial.print(count);
  }
}

void checkHeartBeat() {
  if(timer - heartTimer >= heartHold) {
    redcount = 1;
    red_relay_operation(heartbeatseizuretime, redcount);
  } else {
    redcount = 0;
  }
}