#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "sh1106.h"
#include "FrameBuffer.h"

#define WIDTH 128
#define HEIGHT 64
#define RADIUS 10

int main() {
    stdio_init_all();

    // Initialize I2C using pins GP8 & GP9 (default I2C0 pins)
    uint8_t i2c_address = 0x3C; // SH1106 I2C address
    uint sda_pin = 8;
    uint scl_pin = 9;

    // Initialize SH1106 OLED display
    SH1106 display(WIDTH, HEIGHT, i2c0, i2c_address, sda_pin, scl_pin);

    // Write code here
    
    return 0;
}
