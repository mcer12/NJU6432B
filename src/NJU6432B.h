#ifndef NJU6432B_H
#define NJU6432B_H

#include <Arduino.h>

class NJU6432B {
  public:
    NJU6432B(uint8_t dataPin, uint8_t clockPin, uint8_t enPin);
    ~NJU6432B();
    bool begin();
    uint8_t* getBuffer();
    void setSegment(uint8_t segment, uint8_t state);
    void update();
    void clear();
    void fill();

  protected:
    uint8_t* buffer;
    uint8_t _dataPin, _clockPin, _enPin;
    void sendData(uint8_t* buffer);  // Now protected
    void shiftByte(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t byte);
};

#endif
