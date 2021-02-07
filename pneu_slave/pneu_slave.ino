#include "Config.h"
#include<SPI.h>
//unsigned long halwa;
long prev_millis, curr_millis;
void setup() {
  Serial.begin(115200);
  pinMode(MISO, OUTPUT); // have to send on master in so it set as output
  SPCR |= _BV(SPE);
  SPI.attachInterrupt();// enable spi module'
  pinModes();
  relaysOff();
  Thrower.Open()
  Grabber.Open();
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
      ThrowEnc.write(0);
    } else if (limitAclk == LOW && limitClk == HIGH) {
      grabberClk(30);
      ThrowEnc.write(0);
    }
    Serial.println("Brake motor");
  }
  else {
    switch (button) {
      case RIGHT:
        ThrowMotor.clk(100);
        Serial.println(readEncoder);
        break;

      case LEFT:
        ThrowMotor.aclk(100);
        Serial.println(readEncoder);
        break;

      case SQUARE:
        Grabber.Close();
        Serial.println("Open the grabber");
        break;

      case CIRCLE:
        Grabber.Open();
        Serial.println("Grab the arrow");
        break;

      case CROSS:
        Thrower.Close();
        delay(10);
        Thrower.Free();
        Serial.println("Thrower Down");
        break;

      case TRIANGLE:
        Serial.print(reedCount);
        Serial.println("Thrower Up");
        while (reedCount < 2) {
          Serial.print(reedCount); Serial.println(" count") ;
          if (reedSwitch == 0) {
            reedCount++;
          } else {
            Serial.print(reedCount); Serial.println(" count") ;
            Thrower.Free();
          }
        }
        Serial.print(reedCount);
        Thrower.Open();
        delay(1000);
        reedCount = 0 ;
        break;

      case START:
        iniPos();
        break;

      case DOWN:
        Grabber.Open();
        delay(10);
        Grabber.Close();
        break;

      case SELECT:
        Grabber.Close();
        grabberAclk(25);
        ThrowMotor.brakeHercules();
        //move bot forward
        delay(3000);
        grabberAclk(2400);
        delay(3000);
        Thrower.Close();
        delay(3000);
        grabberAclk(2800);
        Grabber.Open();
        delay(1000);
        grabberAclk(3500);
        ThrowMotor.brakeHercules();
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
  ThrowMotor.brakeHercules();
  grabberAclk(35);
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
