/* 3/18/22
ALEX 1.0, a miniature robot consisting of a face on a pan and tilt servo module
  - ALEX is controlled by an IR remote (this version uses a Radioshack Make:it Robot Remote Control)
  - When switched into deep sleep, it  will be battery friendly consuming much less power. 
  - Please see the jpg schematic from fritzing for the parts layout.
  
  This is version 1, in future updates I'm hoping for Wifi, OSC, LCD face, and more!
*/



#include <Arduino.h>
#include <IRremote.hpp> // use the library for IR
#include "ServoEasing.hpp"

#define receiver 21
#define PanPin 33
#define TiltPin 32
#define modePin 26
//tiltPins are the top row on breadboard

bool isIRmode = false;

ServoEasing pan;
ServoEasing tilt;


// tilt 35 is start, 160 is straight up, 180 is max
byte tiltMin = 35;
byte tiltMax = 175;
byte panMin = 5;
byte panMax = 180;
bool iManualMode = true;

//#define START_DEGREE_VALUE  35 // The degree value written to the servo at time of attach.
#define START_DEGREE_VALUE  60 // The degree value written to the servo at time of attach.

void setup() {
  Serial.begin(115200);

  // Setup Deep sleep mode to be attached to pin 26 and woken up with a HIGH value
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_26,1); //1 = High, 0 = Low

  //SETUP Pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(modePin, INPUT_PULLUP);


  // initialize the IRreceiver
  IrReceiver.begin(receiver, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN); 
  
  //Setup Servo Motors
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_SERVO_EASING));
  Serial.print(F("Attach servo at pin "));
  Serial.println(PanPin);
  if (pan.attach(PanPin, START_DEGREE_VALUE) == INVALID_SERVO) {
    Serial.println(F("Error attaching servo"));
  }
  if (tilt.attach(TiltPin, START_DEGREE_VALUE) == INVALID_SERVO) {
    Serial.println(F("Error attaching servo"));
  }
  setEasingTypeForAllServos(EASE_CUBIC_IN_OUT);
  pan.setSpeed(400);
  tilt.setSpeed(400);

  // Wait for servo to reach start position.
  delay(300);
}

void loop() {
  isIRmode = digitalRead(modePin);
  delay(50);

  if (isIRmode){
    IRpolling();
  }
  else {
    Serial.println("going to sleep!");
    esp_deep_sleep_start();
  }
}