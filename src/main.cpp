#include <Arduino.h>
#include <git_revision.h>

#define GPS_EN 18
#define BUCK_EN 11
#define ALIVE_LED 20

void setup() {
  //Serial port for debugging purposes
  Serial.begin(115200);
  Serial.printf("Git info: %s %s\n", __GIT_COMMIT__, __GIT_REMOTE_URL__);
  Serial.printf("Built on %s at %s\n", __DATE__, __TIME__);

  //Set GPS_EN pin as output
  pinMode(GPS_EN, OUTPUT);
  digitalWrite(GPS_EN, LOW);

  //Set ALIVE_LED pin as output
  pinMode(ALIVE_LED, OUTPUT);

  //Set BUCK_EN pin
  digitalWrite(BUCK_EN, OUTPUT);
  digitalWrite(BUCK_EN, HIGH);
 
  // //Open a serial connection for the GPS module
  Serial2.setTX(4);
  Serial2.setRX(5);
  Serial2.begin(9600);
}

uint64_t t0 = 0;

void loop() {
  uint16_t dt = millis() - t0;
  if(dt < 1000) {
    digitalWrite(ALIVE_LED, HIGH);
  }else if(1000 < dt && dt < 2000) {
    digitalWrite(ALIVE_LED, LOW);
  }else if(2000 < dt){
    t0 = millis();
  }
  while (Serial2.available()) {
    Serial.write(Serial2.read());
  }

  while (Serial.available()) {
    Serial2.write(Serial.read());
  }
}
