#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "sh1106.h"

#define WIDTH 128
#define HEIGHT 64

int main() {
    stdio_init_all();

    // Initialize I2C using pins GP8 & GP9 (default I2C0 pins)
    uint8_t i2c_address = 0x3C; // SH1106 I2C address
    uint sda_pin = 8;
    uint scl_pin = 9;

    // Initialize SH1106 OLED display
    SH1106 display(WIDTH, HEIGHT, i2c0, i2c_address, sda_pin, scl_pin);

    display.fill(0);

    // Draw a triangle
    display.drawTriangle(10, 10, 20, 20, 30, 15, 1);

    // Draw a filled triangle
    display.drawTriangleFill(40, 10, 50, 20, 60, 15, 1);

    // Update the display
    display.show();

    return 0;
}
