/*
This example should the relay pin and the builtin LED at a cycle of 1s on 1s off
There are no delays in a Non-Blocking Format
*/

//const int BUTTON_PIN    = -;
const int RED_RELAY_PIN = 4;
const int YELLOW_RELAY_PIN = 5;
const int GREEN_RELAY_PIN = 6;
const int BUZZER_RELAY_PIN = 7;

const int THRESHOLD = 1000; //ms

const int RED_LED_BUILTIN = 13;//D13?
const int YELLOW_LED_BUILTIN = 14;//D13?
const int GREEN_LED_BUILTIN = 15;//D13?
const int BUZZER_LED_BUILTIN = 16;//D13?

void setup() {
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
  if(now-redbefore >= THRESHOLD) {
    digitalWrite(RED_RELAY_PIN, !digitalRead(RED_RELAY_PIN));
    digitalWrite(RED_LED_BUILTIN, !digitalRead(RED_LED_BUILTIN));
    redbefore = now;
  }
  if(now-yellowbefore >= THRESHOLD) {
    digitalWrite(YELLOW_RELAY_PIN, !digitalRead(YELLOW_RELAY_PIN));
    digitalWrite(YELLOW_LED_BUILTIN, !digitalRead(YELLOW_LED_BUILTIN));
    yellowbefore = now;
  }
  if(now-greenbefore >= THRESHOLD) {
    digitalWrite(GREEN_RELAY_PIN, !digitalRead(GREEN_RELAY_PIN));
    digitalWrite(GREEN_LED_BUILTIN, !digitalRead(GREEN_LED_BUILTIN));
    greenbefore = now;
  }
  if(now-buzzerbefore >= THRESHOLD) {
    digitalWrite(BUZZER_RELAY_PIN, !digitalRead(BUZZER_RELAY_PIN));
    digitalWrite(BUZZER_LED_BUILTIN, !digitalRead(BUZZER_LED_BUILTIN));
    buzzerbefore = now;
  }
}
