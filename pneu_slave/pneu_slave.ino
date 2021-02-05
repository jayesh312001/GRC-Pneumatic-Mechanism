#include "Motor.h"
#include "Func.h"
#include <Encoder.h>
#include<SPI.h>

Motor ThrowMotor(Throw_pwm, Throw_in1, Throw_in2);
Encoder ThrowEnc(3, 2);

bool initialPosition = false;
int reedCount = 0;
byte button = 0;
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
    if(limitClk == LOW) {
      ThrowMotor.aclk(60);
      delay(50);
      ThrowMotor.brakeHercules();
    } else if(limitAclk == LOW) {
      ThrowMotor.clk(60);
      delay(50);
      ThrowMotor.brakeHercules();
    }
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
      pClose(25, 29);
      Serial.println("P1CLOSE");
    }
    else if (button == CIRCLE) {
      pOpen(25, 29);
      Serial.println("P1Open");
    }

    // Throwing Pneumatic
    else if (button == CROSS) {

      pClose(23, 27);

      Serial.println("P2clOSE");
    }
    else if (button == DOWN) {
      pHold(23, 27);
      Serial.println("Motor anticlock");
    }
    else if (button == TRIANGLE) {
      Serial.println("P2Open");
      while (reedCount < 2) {
        if (reedSwitch == 0) {
          reedCount++;
        } else {
          pHold(23, 27);
        }
      }
      pOpen(23, 27);
      delay(1000);
      reedCount = 0 ;
    }
    else if (button == START) {
      while (limitClk == HIGH) {
        ThrowMotor.clk(60);
      }
      ThrowMotor.brakeHercules();
      delay(10);
      ThrowMotor.aclk(60);
      delay(50);
      ThrowMotor.brakeHercules();
      ThrowEnc.write(0);
    }
    else if (button == SELECT) {
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
