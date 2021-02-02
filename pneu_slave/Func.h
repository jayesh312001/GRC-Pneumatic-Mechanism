#define limitClk digitalRead(18)
#define limitAclk digitalRead(20)

#define reedSwitch digitalRead(21)

#define Throw_pwm 4
#define Throw_in1 5
#define Throw_in2 28

#define GrabP1 23
#define GrabP2 27

#define ThrowP1 25
#define ThrowP2 29

#define readEncoder ThrowEnc.read()

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
  //Grabber Pneumatic
  digitalWrite(23, HIGH);
  digitalWrite(27, HIGH);

  //Throwing Pneumatic
  digitalWrite(25, HIGH);
  digitalWrite(29, HIGH);
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
