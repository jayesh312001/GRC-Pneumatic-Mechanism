#include "Motor.h"
#include "Func.h"
#include <Encoder.h>

Motor ThrowMotor(Throw_pwm, Throw_in1, Throw_in2);
Encoder ThrowEnc(3, 2);

bool initialPosition = false;
int reedCount = 0;
void setup() {
  Serial.begin(9600);
  digitalWrite(23, HIGH);
  digitalWrite(25, HIGH);
  digitalWrite(27, HIGH);
  digitalWrite(29, HIGH);
  pinMode(18, INPUT_PULLUP);
  pinMode(23, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(29, OUTPUT);
  pClose(25, 29); //RELAY PINOUTS
  pinMode(21, INPUT_PULLUP);
  //  attachInterrupt(digitalPinToInterrupt(21),pneumatic,CHANGE);
}

void loop() {

  //WORKING'
  pClose(25, 29);
  delay(2000);
  while(reedCount < 3) {
    if(digitalRead(21) == 0) {
      reedCount++;
    } else {
      pHold(25,29);
    }
  }
  pOpen(25,29);
  delay(1000);
  reedCount = 0 ;

}
