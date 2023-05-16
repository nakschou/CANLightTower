#include <WatchDog.h>

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
//#include <can-serial.h>
//#include <mcp2515_can.h>
#include <SPI.h>
#include "mcp_can.h"

const int heartbeatseizuretime = 100; //ms
const int greenflashtime = 500; //ms
const int yellowflashtime = 500; //ms
const int slowredflashtime = 1000;

const int SPI_CS_PIN = 17;  //Can Bus CS pin using LONGAN library
  //Initialize pins for sending signals to the relay
int ROTATE_RELAY_PIN = 4;
int CYCLE_RELAY_PIN = 5;
int YELLOW_RELAY_PIN = 8;
int BUZZER_RELAY_PIN = 9;
int GREEN_RELAY_PIN = 10;
int RED_RELAY_PIN = 11; 
int CAN_ID = 3;


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

bool manual_mode = false;
bool auto_mode = false;
bool throttle_on = false;
bool about_to_start = false;
bool rtc_comms = false;

//Total runtime of the process. Used for timer purposes

MCP_CAN CAN(SPI_CS_PIN);   //Set CS Pin using SEEED Library


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
  pinMode(LED_BUILTIN, OUTPUT);

  WatchDog::init(isr, OVF_500MS);
}

void loop() {
  unsigned char len = 0;    //Variables which acquire Can-Bus message data
  unsigned char buf[8];

  if (CAN_MSGAVAIL == CAN.checkReceive()) {  //Check if a CAN signal is available
    CAN.readMsgBuf(&len, buf);    // read data.  len = data length, buf = data buffer

    unsigned long canId = CAN.getCanId();
    if(canId == 3) {
      //put stuff in here TODO
      if(buf[0] == 0) {
        manual_mode = true;
        auto_mode = false;
      }
      if(buf[0] == 1) {
        manual_mode = false;
        auto_mode = true;
      }
      if(buf[0] == 2) {
        throttle_on = false;
      }
      if(buf[0] == 3) {
        throttle_on = true;
      }
      if(buf[0] == 4) {
        about_to_start = true;
      }
      rtc_comms = true;
    } else {
      rtc_comms = false;
    }
     
    

    //This is where we will add a switch statement to decide which of the functions to perform: steady red, flashing etc.

    heartTimer = timer; //Update heartTimer whenever a CAN signal is received
  }
  timer = millis(); //Update timer
  checkHeartBeat();

  steadyGreenLight();
  flashGreenRotateYellow();
  steadyYellow();
  flashYellowRotateYellow();
  slowFlashRed();
  fastFlashRed();
  steadyRed();
}

void red_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  if(now-redbefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(repetitions == 0) {
      digitalWrite(RED_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(RED_RELAY_PIN, !digitalRead(RED_RELAY_PIN));
    redbefore = now;
    redcount = repetitions - 1;
    //Serial.print(count);
  }
}

void yellow_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  //if the time has passed
  if(now-yellowbefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(repetitions == 0) {
      digitalWrite(YELLOW_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(YELLOW_RELAY_PIN, !digitalRead(YELLOW_RELAY_PIN));
    yellowbefore = now;
    yellowcount = repetitions - 1;
    //Serial.print(count);
  }
}

void green_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  if(now-greenbefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(repetitions == 0) {
      digitalWrite(GREEN_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(GREEN_RELAY_PIN, !digitalRead(GREEN_RELAY_PIN));
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    greenbefore = now;
    greencount = repetitions - 1;
    //Serial.print(count);
  }
}

void buzzer_relay_operation(int duration, int repetitions) {
  unsigned long now = millis();
  if(now-buzzerbefore >= duration) {
    //Serial.print("Here" + repetitions-1);
    if(repetitions == 0) {
      digitalWrite(BUZZER_RELAY_PIN, LOW);
      return;
    }
    digitalWrite(BUZZER_RELAY_PIN, !digitalRead(BUZZER_RELAY_PIN));
    buzzerbefore = now;
    buzzercount = repetitions - 1;
    //Serial.print(count);
  }
}

void rotate_relay_operation() {
  digitalWrite(ROTATE_RELAY_PIN, HIGH);
}

void checkHeartBeat() {
  if(timer - heartTimer >= heartHold) {
    redcount = 1;
    red_relay_operation(heartbeatseizuretime, redcount);
  } else {
    redcount = 0;
  }
}

void steadyGreenLight() {
  if(auto_mode && !throttle_on) {
    digitalWrite(GREEN_RELAY_PIN, HIGH);
  }
}

void flashGreenRotateYellow() {
  if(auto_mode && throttle_on) {
    greencount = 1;
    rotate_relay_operation();
  }
  green_relay_operation(greenflashtime, greencount);
}

void steadyYellow() {
  if(manual_mode && !throttle_on) {
    digitalWrite(YELLOW_RELAY_PIN, HIGH);
  }
}

void flashYellowRotateYellow() {
  if(manual_mode && throttle_on) {
    yellowcount = 1;
    rotate_relay_operation();
  }
  yellow_relay_operation(yellowflashtime, yellowcount);
}

void slowFlashRed() {
  if(rtc_comms) {
    redcount = 1;
  }
  red_relay_operation(slowredflashtime, redcount);
}

void fastFlashRed() {
  if(0) {
    redcount = 1;
  }
  red_relay_operation(heartbeatseizuretime, redcount);
}

void steadyRed() {
  if(0) {
    digitalWrite(RED_RELAY_PIN, HIGH);
  }
}

void turnAllOff() {
  manual_mode = false;
  auto_mode = false;
  throttle_on = false;
  about_to_start = false;
  redcount = 0;
  yellowcount = 0;
  greencount = 0;
  buzzercount = 0;
  rotatecount = 0;
  digitalWrite(RED_RELAY_PIN, LOW);
  digitalWrite(YELLOW_RELAY_PIN, LOW);
  digitalWrite(GREEN_RELAY_PIN, LOW);
  digitalWrite(BUZZER_RELAY_PIN, LOW);
  digitalWrite(ROTATE_RELAY_PIN, LOW);
}

void isr() {
  digitalWrite(GREEN_RELAY_PIN, !digitalRead(GREEN_RELAY_PIN));
}