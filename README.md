
# NJU6432B Library

This is an Arduino library for controlling the NJU6432B LCD driver, see manufacturer [datasheet](https://docs.rs-online.com/3725/0900766b8002ada1.pdf) for details and pinout. The library provides functions to manage the display buffer, send data, and control individual segments of the display.

![alt text](https://raw.githubusercontent.com/mcer12/NJU6432B/refs/heads/main/images/showcase.webp)

## Installation

1. Copy this repository to your arduino libraries folder.
2. Restart the Arduino IDE to ensure the library is recognized.
3. You should now see library examples in Arduino IDE

## Usage

### Constructor
NJU6432B(uint8_t dataPin, uint8_t clockPin, uint8_t enPin);

- `dataPin`: The pin connected to the data line of the NJU6432B.
- `clockPin`: The pin connected to the clock line of the NJU6432B.
- `enPin`: The pin connected to the enable line of the NJU6432B.

### Public Methods

#### `bool begin()`
Initializes the NJU6432B driver and allocates the display buffer.

#### `uint8_t* getBuffer()`
Returns a pointer to the display buffer.

#### `void setSegment(uint8_t segment, uint8_t state)`
Sets the state of a specific segment.

- `segment`: The segment index (0–111).
- `state`: The state of the segment (`1` for on, `0` for off).

#### `void update()`
Sends the buffer to NJU6432B.

#### `void clear()`
Clears all segments.

#### `void fill()`
Enables all segments.
