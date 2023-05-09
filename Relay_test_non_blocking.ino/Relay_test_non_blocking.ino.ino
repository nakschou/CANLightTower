/*
This example should the relay pin and the builtin LED at a cycle of 1s on 1s off
There are no delays in a Non-Blocking Format
*/

//const int BUTTON_PIN    = -;
const int RELAY_PIN     = 4;
//const int LED_BUILTIN     = 13;//D13?
bool is_on = false;
void setup() {
  //Define each Digital pin to be an output or input
  //pinMode(BUTTON_PIN,INPUT);
  pinMode(RELAY_PIN,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}
  
unsigned long before = millis();

void loop() {
unsigned long now = millis();
	if (now - before >= 1000 && is_on==false) {
    digitalWrite(RELAY_PIN, HIGH);  // turn the Relay on (HIGH is the voltage level)
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    is_on = true;
    before = now;
  }
  else if(now - before >= 1000 && is_on == true){
    digitalWrite(RELAY_PIN, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
    is_on = false;
    before = now;
  }
}
  



