// Include headers and libraries ---------------------
#include "Bot.h"
#include "Pneumatic.h"
#include <Encoder.h>


// Definition of pins ---------------------------------
#define Grab_pwm 4
#define Grab_in1 5
#define Grab_in2 28
#define GrabP1 23
#define GrabP2 27
#define ThrowP1 25
#define ThrowP2 29


// Base Motor pinouts
#define FR1 
#define FR2
#define FRP

#define BR1 
#define BR2
#define BRP

#define BL1 
#define BL2
#define BLP

#define FL1 
#define FL2
#define FLP

// Definition of digitalReads -------------------------
#define limitClk digitalRead(18)
#define limitAclk digitalRead(20)
#define reedSwitch digitalRead(21)
#define readEncoder GrabEnc.read()

// Creating objects of classes-------------------------
Motor GrabMotor(Grab_pwm, Grab_in1, Grab_in2);
Encoder GrabEnc(3, 2);
Pneumatic Thrower(ThrowP1, ThrowP2);
Pneumatic Grabber(GrabP1, GrabP2);

Motor motor1(FR1, FR2, FRP);
Motor motor2(BR1, BR2, BRP);
Motor motor3(BL1, BL2, BLP);
Motor motor4(FL1, FL2, FLP);

Bot bot(motor1, motor2, motor3, motor4);


// Variables- -----------------------------------------
int reedCount = 0;
byte button = 0;

// Custom functions ----------------------------------
void pinModes() {
  pinMode(GrabP1, OUTPUT);
  pinMode(GrabP2, OUTPUT);
  pinMode(ThrowP1, OUTPUT);
  pinMode(ThrowP2, OUTPUT);
  pinMode(21, INPUT_PULLUP); //Reed Switch
  pinMode(18, INPUT_PULLUP); //LimitClock
  pinMode(20, INPUT_PULLUP); //LimitAntiClock
}

void relaysOff() {
  digitalWrite(GrabP1, HIGH);
  digitalWrite(GrabP2, HIGH);
  digitalWrite(ThrowP1, HIGH);
  digitalWrite(ThrowP2, HIGH);
}

void pClose(int pin1, int pin2) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}
void pFree(int pin1, int pin2) {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}

void pOpen(int pin1, int pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void pHold(int pin1, int pin2) {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
}

// Constants for PS ------------------------------
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4
#define L1 5
#define L2 6
#define R1 7
#define R2 8
#define TRIANGLE 9
#define CIRCLE 10
#define CROSS 11
#define SQUARE 17
#define L3 15
#define R3 16
#define PS 12
#define START 13
#define SELECT 14
#define UPRIGHT 15
#define UPLEFT 16
#define DOWNLEFT 17
#define DOWNRIGHT 18
#define DISC 255
