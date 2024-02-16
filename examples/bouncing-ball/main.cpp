#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "sh1106.h"
#include "framebuffer.h"

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

    int16_t x = WIDTH / 2, y = HEIGHT / 2;
    int16_t dx = 1, dy = 1;

    while (true) {
        // Clear the display
        display.fill(0);

        // Draw a circle
        display.drawCircleFill(x, y, RADIUS, 1);

        // Update the display
        display.show();

        // Update the circle's position
        x += dx;
        y += dy;

        // Check for collisions with the edges of the display
        if (x - RADIUS <= 0 || x + RADIUS >= WIDTH) {
            dx = -dx;
        }
        if (y - RADIUS <= 0 || y + RADIUS >= HEIGHT) {
            dy = -dy;
        }

        sleep_ms(1); // Delay to control the speed of the animation
    }

    return 0;
}
