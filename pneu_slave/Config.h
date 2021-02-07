// Include headers and libraries ---------------------
#include "Motor.h"
#include "Pneumatic.h"
#include <Encoder.h>


// Definition of pins ---------------------------------
#define Throw_pwm 4
#define Throw_in1 5
#define Throw_in2 28
#define GrabP1 23
#define GrabP2 27
#define ThrowP1 25
#define ThrowP2 29

// Definition of digitalReads -------------------------
#define limitClk digitalRead(18)
#define limitAclk digitalRead(20)
#define reedSwitch digitalRead(21)
#define readEncoder ThrowEnc.read()

// Creating objects of classes-------------------------
Motor ThrowMotor(Throw_pwm, Throw_in1, Throw_in2);
Encoder ThrowEnc(3, 2);
Pneumatic Thrower(ThrowP1, ThrowP2);
Pneumatic Grabber(GrabP1, GrabP2);


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
#define DISC 255
