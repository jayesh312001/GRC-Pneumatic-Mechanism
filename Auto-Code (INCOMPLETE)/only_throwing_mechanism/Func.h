#define limitClk digitalRead(18)
#define limitAclk digitalRead(20)

#define reedSwitch digitalRead(21)

#define Throw_pwm 4
#define Throw_in1 5
#define Throw_in2 28

#define GrabP1 25
#define GrabP2 29

#define ThrowP1 23
#define ThrowP2 27

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
  digitalWrite(GrabP1, HIGH);
  digitalWrite(GrabP2, HIGH);

  //Throwing Pneumatic
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
