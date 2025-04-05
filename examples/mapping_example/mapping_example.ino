
#include <NJU6432B.h>

#define DATA_PIN 7
#define CLK_PIN 6
#define CE_PIN 5
#define BUTTON_PIN 2
#define DIGITS_COUNT 10

#define I_PLUS 80
#define I_MINUS 81
#define I_R 88
#define I_ECR 89
#define I_Z 91
#define I_EQUAL 92
#define I_P 93
#define I_X_2 94
#define I_DIVIDE 95
#define I_Z 94

#define BAT_1 111
#define BAT_2 97
#define BAT_3 99
#define BAT_4 101
#define BAT_LINE 100

#define STL 102
#define M 103
#define MINUS 82
#define RETURN 83


const uint8_t segments[DIGITS_COUNT][8] = {
  {72, 75, 73, 87, 85, 86, 84, 74}, // BR | B | BL | TL | M | T | TR | DOT
  {64, 67, 65, 79, 77, 78, 76, 66}, // BR | B | BL | TL | M | T | TR | DOT
  {56, 59, 57, 71, 69, 70, 68, 58}, // BR | B | BL | TL | M | T | TR | DOT
  {52, 55, 53, 63, 61, 62, 60, 54}, // BR | B | BL | TL | M | T | TR | DOT
  {44, 47, 45, 43, 41, 42, 40, 46}, // BR | B | BL | TL | M | T | TR | DOT
  {36, 39, 37, 35, 33, 34, 32, 38}, // BR | B | BL | TL | M | T | TR | DOT
  {28, 31, 29, 27, 25, 26, 24, 30}, // BR | B | BL | TL | M | T | TR | DOT
  {20, 23, 21, 19, 17, 18, 16, 22}, // BR | B | BL | TL | M | T | TR | DOT
  {12, 15, 13, 11, 9, 10, 8, 14}, // BR | B | BL | TL | M | T | TR | DOT
  {4, 7, 5, 3, 1, 2, 0, 6}, // BR | B | BL | TL | M | T | TR | DOT
};

const uint8_t numbers[10][8] = {
  {1, 1, 1, 1, 0, 1, 1, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {1, 0, 0, 0, 0, 0, 1, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {0, 1, 1, 0, 1, 1, 1, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {1, 1, 0, 0, 1, 1, 1, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {1, 0, 0, 1, 1, 0, 1, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {1, 1, 0, 1, 1, 1, 0, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {1, 1, 1, 1, 1, 1, 0, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {1, 0, 0, 0, 0, 1, 1, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {1, 1, 1, 1, 1, 1, 1, 0}, // BR | B | BL | TL | M | T | TR | DOT
  {1, 1, 0, 1, 1, 1, 1, 0}, // BR | B | BL | TL | M | T | TR | DOT
};

NJU6432B display(DATA_PIN, CLK_PIN, CE_PIN);  // Set custom pins for data, clock, and enable

void writeNumber(int number) {
  bool leading = false;

  for (int i = 9; i >= 0; i--) {
    uint8_t digit = number % 10;
    if (number == 0) {
      clearDigit(i); // blank
    } else {
      leading = true;
      setDigit(i, digit);
    }
    number /= 10;

  }
}

void setDigit(uint8_t position, uint8_t number) {
  for (int i = 0; i < 8; i++) {
    if (numbers[number][i] > 0) {
      display.setSegment(segments[position][i], 1);
    } else {
      display.setSegment(segments[position][i], 0);
    }
  }
}

void clearDigit(uint8_t position) {
  for (int i = 0; i < 8; i++) {
    display.setSegment(segments[position][i], 0);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Using internal pull-up resistor

  display.begin();
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    display.clear();
    display.update();
    delay(200);
  }

  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim(); // removes whitespace, including \r and \n

    if (input.length() > 0) {
      int segmentNumber = input.toInt();

      if (segmentNumber >= 0 && segmentNumber < 112) {
        Serial.println(segmentNumber);
        display.setSegment(segmentNumber, 1);
        display.update();
      } else {
        Serial.println("Error: Segment number must be between 0 and 111.");
      }
    }
  }
}
