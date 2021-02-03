#include "Motor.h"
#include "Func.h"
#include <Encoder.h>

Motor ThrowMotor(Throw_pwm, Throw_in1, Throw_in2);
Encoder ThrowEnc(3, 2);

bool initialPosition = false;
int reedCount = 0;

void setup() {
  Serial.begin(9600);
  pinModes();
  pOpen(GrabP1, GrabP2);
  delay(2000);
}

void loop() {

  //Move shaft clockwise until hits limit switch
  while (initialPosition != true) {
    if (limitSwitch == LOW) {
      //      Serial.println("Initial Reached");
      ThrowMotor.brakeHercules();
      initialPosition = true;
      ThrowEnc.write(0);
      //After hitting the limit switch, raise it up a little
      while (readEncoder < 50 ) {
        grabberAclk(50);
      }
      delay(3000);
      pClose(GrabP1, GrabP2);
      delay(2000); //Delay To grab arrow completely
      break;
    } else {
      ThrowMotor.clk(50);
    }
  }

  //Quickly open and close to grab arrow from a lower position
  grabberAclk(500);
  pOpen(GrabP1, GrabP2);
  delay(170);
  pClose(GrabP1, GrabP2);
  delay(500);

  //Move till the throwing position and then bring down thrower
  grabberAclk(2600);
  while (1);

  // Throw arrow
    while (reedCount < 2) {
    if (digitalRead(21) == 0) {
      reedCount++;
    } else {
      pHold(ThrowP1, ThrowP2);
    }
    }
    //  pOpen(ThrowP1, ThrowP2);
    delay(2000);
    initialPosition = false;
}

void grabberAclk(int pulses) {
  while (readEncoder < pulses) {
    ThrowMotor.aclk(50);
    //    Serial.println(ThrowEnc.read());
  }
  ThrowMotor.brakeHercules();
}

void grabberClk(int pulses) {
  while (readEncoder > -pulses) {
    ThrowMotor.clk(50);
    //    Serial.println(ThrowEnc.read());
  }
  ThrowMotor.brakeHercules();
}
