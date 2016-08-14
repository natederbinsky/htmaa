#include <Cmd.h>
#include <Servo.h>
#include <EEPROM.h>

////////////////////////////////////
// Constants
////////////////////////////////////

const int PIN_GREEN = 7;
const int PIN_RED = 6;
const int PIN_BLUE = 5;
const int PIN_BUTTON = 2;
const int PIN_SERVO = 9;

const int PW_LENGTH = 4;
const char* PW_DEFAULT = "1234";

////////////////////////////////////
// Variables
////////////////////////////////////

Servo myServo;
bool lockOpen;

////////////////////////////////////

// Initial setup
void setup() {
  pinMode(PIN_GREEN,OUTPUT);
  pinMode(PIN_RED,OUTPUT);
  pinMode(PIN_BLUE,OUTPUT);
  pinMode(PIN_BUTTON,INPUT);

  myServo.attach(PIN_SERVO);

  // Use carriage return to end commands
  Serial.begin(9600);
  cmdInit(&Serial);

  cmdAdd("move",tryMove);
  cmdAdd("change",tryChange);
}

////////////////////////////////////

// Loops continuously
void loop() {
  if (digitalRead(PIN_BUTTON)) {
    resetPassword();
  }
  cmdPoll();
}

////////////////////////////////////

// Response to a "move" command
void tryMove(int argCount, char** args) {
  if (argCount==2) {
    attemptOpen(args[1]);
  }
}

////////////////////////////////////

// Response to a "change" command
void tryChange(int argCount, char** args) {
  if (argCount==3) {
    attemptChange(args[1],args[2]);
  }
}

////////////////////////////////////

// blink an led for .1 seconds
void blink(int pin) {
  digitalWrite(pin,HIGH);
  delay(100);
  digitalWrite(pin,LOW);
  delay(100);
}

////////////////////////////////////

// changes the password stored on the Arduino
// and blinks blue
void setPassword(const char* code) {
  for (int i=0; i<PW_LENGTH; i++) {
    EEPROM.write(i,code[i]);
  }
  blink(PIN_BLUE);
  blink(PIN_BLUE);
}

////////////////////////////////////

// returns true if input password matches Arduino memory
bool verifyPassword(const char* attempt) {
  for (int i=0; i<PW_LENGTH; i++) {
    if (EEPROM.read(i)!=attempt[i]) {
      return false;
    }
  }
  return true;
}

////////////////////////////////////

// if the provided password is correct, moves the servo
// if successful, blink green; else red
void attemptOpen(const char* input) {
  if (verifyPassword(input)) {
    blink(PIN_GREEN);
    setLock(!lockOpen);
  } else {
    blink(PIN_RED);
  }
}

////////////////////////////////////

// if the provided old password is correct, change to the new password
// if successful, blink blue; else red
void attemptChange(const char* oldPass, const char* newPass) {
   if (verifyPassword(oldPass)) {
    setPassword(newPass);
  } else {
    blink(PIN_RED);
  }
}

////////////////////////////////////

// sets the stored password to the default
void resetPassword() {
  setPassword(PW_DEFAULT);
}

////////////////////////////////////

// moves the servo between the "open" and "closed" positions
void setLock(bool open) {
  lockOpen = open;
  if (open) {
    myServo.write(0);
  } else {
    myServo.write(90);
  }
}

