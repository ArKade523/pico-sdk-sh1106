# pico-sdk-sh1106
A simple-to-use SH1106 display library for the Raspberry Pi Pico using the Pico SDK

## How to use
1. Clone the repository
2. Copy the `sh1106` folder to your project's `lib` folder
3. Include the library in your project's `CMakeLists.txt` file
```cmake
add_subdirectory(lib/sh1106)
target_link_libraries(your_project_name sh1106)
```

4. Include the library in your project's source file
```cpp
#include "sh1106/sh1106.h"
```

5. Use the library
```cpp
SH1106 display(WIDTH, HEIGHT, i2c0, i2c_address, sda_pin, scl_pin);
display.fill(0);
display.text("Hello, World!", 0, 0, 1);
display.show();
```

## Available functions
```cpp
void display::initDisplay();
void display::powerOn();
void display::reset();
void display::fill(uint8_t color);
void display::setPixel(uint16_t x, uint16_t y, uint8_t color);
void display::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);
void display::drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color);
void display::drawCircleFill(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color);
void display::drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
void display::drawRectFill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
void display::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void display::drawTriangleFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
void display::blit(FrameBuffer& src, uint16_t x, uint16_t y);
void display::text(const std::string& str, uint16_t x, uint16_t y);
void display::show();
```

