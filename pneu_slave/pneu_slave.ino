#include "Config.h"

void setup() {
  Serial.begin(115200);
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();// enable spi module'
  pinModes();
  relaysOff();
}

ISR(SPI_STC_vect) {
  switch (button) {
    case DISC:
      button = 0;
      SPDR = 0;
    default:
      button = SPDR;
  }
}

void loop() {

  if (limitClk == LOW || limitAclk == LOW) {
    ThrowMotor.brakeHercules();
    ThrowEnc.write(0);
    if (limitClk == LOW && limitAclk == HIGH) {
      grabberAclk(30);
    } else if (limitAclk == LOW && limitClk == HIGH) {
      grabberClk(30);
    }
    Serial.println("Brake motor");
  }
  else {

    switch (button) {
      case RIGHT:
        ThrowMotor.clk(100);
        Serial.println(ThrowEnc.read());
        break;

      case LEFT:
        ThrowMotor.aclk(100);
        Serial.println(ThrowEnc.read());
        break;

      case SQUARE:
        Grabber.Open();
        delay(50);
        Grabber.Free();
        Serial.println("Open the grabber");
        break;

      case CIRCLE:
        Grabber.Close();
        delay(50);
        Grabber.Free();
        Serial.println("Grab the arrow");
        break;

      case CROSS:
        Thrower.Close();
        delay(50);
        Thrower.Free();
        Serial.println("Thrower Down");
        break;

      case TRIANGLE:
        if (readEncoder < 2000) {
          Serial.println("Thrower Up");
          while (reedCount < 2) {
            if (reedSwitch == 0) {
              reedCount++;
            } else {
              Thrower.Free();
            }
          }
          Thrower.Open();
          delay(1000);
          reedCount = 0 ;
        }

        break;

      case START:
        iniPos();
        break;

      case DOWN:
        Grabber.Open();
        delay(100);
        Grabber.Close();
        break;

      case SELECT:
        Grabber.Close();
        grabberAclk(20);
        ThrowMotor.brakeHercules();
        delay(1000);
        grabberAclk(2500);
        break;

      default:
        ThrowMotor.brakeHercules();
        break;

    }
  }
}


void iniPos() {
  while (limitClk == HIGH) {
    ThrowMotor.clk(60);
  }
  ThrowEnc.write(0);
  grabberAclk(50);
  ThrowEnc.write(0);
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
