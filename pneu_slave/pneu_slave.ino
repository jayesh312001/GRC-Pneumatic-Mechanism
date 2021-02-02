#include "Motor.h"
#include "Func.h"
#include <Encoder.h>
#include<SPI.h>

Motor ThrowMotor(Throw_pwm, Throw_in1, Throw_in2);
Encoder ThrowEnc(3, 2);

bool initialPosition = false;
int reedCount = 0;
byte button = 0;
int flag = 0;
void setup() {
  Serial.begin(115200);
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();// enable spi module'
  pinModes();
  relaysOff();

}

ISR(SPI_STC_vect) {
  button = SPDR;
}

void loop() {

  if (limitClk == LOW || limitAclk == LOW) {
    ThrowMotor.brakeHercules();
      Serial.println("Brake motor");
  }
  else {
    if (button == RIGHT) {
      ThrowMotor.clk(100);
      Serial.println("Motor clock");
    }
    else if (button == LEFT) {
      ThrowMotor.aclk(100);
      Serial.println("Motor anticlock");
    }
    // Grabbing Pneumatic
    else if (button == SQUARE) {
      pClose(23, 27);
      Serial.println("P1CLOSE");
    }
    else if (button == CIRCLE) {
      pOpen(23, 27);
      Serial.println("P1Open");
    }

    // Throwing Pneumatic
    else if (button == CROSS) {
      pClose(25, 29);
      Serial.println("P2clOSE");
    }
    else if (button == TRIANGLE) {
      pOpen(25, 29);
      Serial.println("P2Open");
    } 
    else if (button == START) {
      relaysOff();
      Serial.println("Relays Off");
    }
    else {
      ThrowMotor.brakeHercules();
      Serial.println("Brake motor");
    }
  }

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
