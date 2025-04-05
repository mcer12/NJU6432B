#include "NJU6432B.h"

NJU6432B::NJU6432B(uint8_t dataPin, uint8_t clockPin, uint8_t enPin)
{
  _dataPin = dataPin;
  _clockPin = clockPin;
  _enPin = enPin;
}

NJU6432B::~NJU6432B()
{
  if (buffer != NULL)
  {
    free(buffer);
    buffer = NULL;
  }
}

bool NJU6432B::begin()
{

  buffer = (uint8_t *)malloc(14);
  if (buffer == NULL)
  {
    Serial.println("NJU6432B: Failed to allocate buffer.");
  }
  else
  {
    memset(buffer, 0, 14);
  }

  // Set flag bits, those need to keep this value for every transaction
  buffer[6] &= ~(1 << 0);
  buffer[13] |= (1 << 0);

  pinMode(_dataPin, OUTPUT);
  pinMode(_clockPin, OUTPUT);
  pinMode(_enPin, OUTPUT);

  update();

  return true;
}

uint8_t *NJU6432B::getBuffer()
{
  return buffer;
}

void NJU6432B::shiftByte(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t byte)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    uint8_t bit;
    if (bitOrder == LSBFIRST)
    {
      bit = (byte >> i) & 0x01;
    }
    else
    {
      bit = (byte >> (7 - i)) & 0x01;
    }
    digitalWrite(dataPin, bit);
    delayMicroseconds(1);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(1);
    digitalWrite(clockPin, LOW);
    delayMicroseconds(1);
  }
}

void NJU6432B::sendData(uint8_t *buffer)
{
  digitalWrite(_enPin, HIGH);
  delayMicroseconds(1);
  for (uint8_t i = 0; i < 14; i++)
  {
    shiftByte(_dataPin, _clockPin, MSBFIRST, buffer[i]);
  }
  digitalWrite(_enPin, LOW);
  delayMicroseconds(4);
}

void NJU6432B::setSegment(uint8_t segment, uint8_t state)
{
  if (segment < 112 && segment != 48 && segment != 104) // 48 and 104 are flag bits
  {
    uint8_t byteIndex = segment / 8;
    uint8_t bitIndex = segment % 8;
    if (state > 0)
    {
      buffer[byteIndex] |= (1 << bitIndex);
    }
    else
    {
      buffer[byteIndex] &= ~(1 << bitIndex);
    }
  }
}

void NJU6432B::update()
{
  sendData(buffer);
}

void NJU6432B::clear()
{
  memset(buffer, 0, 14);
  // Resetting the flag bits
  buffer[6] &= ~(1 << 0);
  buffer[13] |= (1 << 0);
}

void NJU6432B::fill()
{
  memset(buffer, 0xFF, 14);
  // Resetting the flag bits
  buffer[6] &= ~(1 << 0);
  buffer[13] |= (1 << 0);
}
