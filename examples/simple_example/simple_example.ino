
#include <NJU6432B.h>

#define DATA_PIN 7
#define CLK_PIN 6
#define CE_PIN 5

NJU6432B display(DATA_PIN, CLK_PIN, CE_PIN);  // Set custom pins for data, clock, and enable

int segment = 0;

void setup() {
  Serial.begin(115200);
  display.begin();
}

void loop() {
  Serial.println(segment);
  display.setSegment(segment,1);
  display.update();
  delay(1000);
  segment++;
  if (segment > 111) {
    segment = 0;
  }
}
