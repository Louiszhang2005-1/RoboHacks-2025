#include <Servo.h>

Servo seedDispenser;

void setup() {
  // put your setup code here, to run once:
  seedDispenser.attach(12);
}

int count = 0;

void loop() {
  while (count < 2) {
    int pos;
    for (pos = 0; pos <= 120; pos++) {
        seedDispenser.write(pos);
        delay(15);
    }

    for (pos = 120; pos <= 0; pos--) {
        seedDispenser.write(pos);
        delay(15);
    }

    count++;
  }

}
