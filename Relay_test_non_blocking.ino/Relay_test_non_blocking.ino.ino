/*
This example should the relay pin and the builtin LED at a cycle of 1s on 1s off
There are no delays in a Non-Blocking Format
*/

//const int BUTTON_PIN    = -;
const int RED_RELAY_PIN = 4;
const int YELLOW_RELAY_PIN = 5;
const int GREEN_RELAY_PIN = 6;
const int BUZZER_RELAY_PIN = 7;

const int 

const int THRESHOLD = 1000; //ms
const int RED_LED_BUILTIN = 13;//D13?
const int YELLOW_LED_BUILTIN = 14;//D13?
const int GREEN_LED_BUILTIN = 15;//D13?
const int BUZZER_LED_BUILTIN = 16;//D13?

void setup() {
  //Define each Digital pin to be an output or input
  //pinMode(BUTTON_PIN,INPUT);
  pinMode(RED_RELAY_PIN,OUTPUT);
  pinMode(RED_LED_BUILTIN, OUTPUT);
  pinMode(YELLOW_RELAY_PIN,OUTPUT);
  pinMode(YELLOW_LED_BUILTIN, OUTPUT);
  pinMode(GREEN_RELAY_PIN,OUTPUT);
  pinMode(GREEN_LED_BUILTIN, OUTPUT);
  pinMode(BUZZER_RELAY_PIN,OUTPUT);
  pinMode(BUZZER_LED_BUILTIN, OUTPUT);
}
  
unsigned long redbefore = millis();
unsigned long yellowbefore = millis();
unsigned long greenbefore = millis();
unsigned long buzzerbefore = millis();

void loop() {
  unsigned long now = millis();
  if(update(THRESHOLD, redbefore, now, RED_RELAY_PIN, RED_LED_BUILTIN)) {
    redbefore = now;
  }
  if(update(THRESHOLD, yellowbefore, now, YELLOW_RELAY_PIN, YELLOW_LED_BUILTIN)) {
    yellowbefore = now;
  }
  if(update(THRESHOLD, greenbefore, now, GREEN_RELAY_PIN, GREEN_LED_BUILTIN)) {
    greenbefore = now;
  }
  if(update(THRESHOLD, redbefore, now, BUZZER_RELAY_PIN, BUZZER_LED_BUILTIN)) {
    buzzerbefore = now;
  }
}

boolean update(int time, unsigned long before, unsigned long now, int RELAY_PIN, int LED_BUILTIN) {
  if(now-before >= time) {
    digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN));
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    return true;
  }
  return false;
}
