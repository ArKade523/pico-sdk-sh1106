#include "SH1106.h"

// Constructor
SH1106::SH1106(uint16_t width, uint16_t height, i2c_inst_t* i2c, uint8_t addr, uint gpio_sda, uint gpio_scl)
    : width(width), height(height), i2c(i2c), addr(addr), frameBuffer(width, height, FrameBuffer::Format::MONO_HLSB) {
    // Initialize I2C
    i2c_init(i2c, 800 * 1000); // 800kHz
    gpio_set_function(gpio_sda, GPIO_FUNC_I2C);
    gpio_set_function(gpio_scl, GPIO_FUNC_I2C);
    gpio_pull_up(gpio_sda);
    gpio_pull_up(gpio_scl);

    initDisplay();
}

// Initialize the display
void SH1106::initDisplay() {
    reset();
    fill(0);
    powerOn();
    show();
}

// Turn the display on
void SH1106::powerOn() {
    writeCmd(0xAE | 0x01); // Display ON
}

// Reset the display (if connected to a GPIO pin)
void SH1106::reset() {
    // Implement reset logic if connected to a GPIO pin
}

// Fill the display with a color
void SH1106::fill(uint8_t color) {
    frameBuffer.fill(color);
}

// Set the color of a single pixel
void SH1106::setPixel(uint16_t x, uint16_t y, uint8_t color) {
    frameBuffer.setPixel(x, y, color);
}

// Draw a line on the display
void SH1106::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color) {
    frameBuffer.drawLine(x0, y0, x1, y1, color);
}

// Draw a circle on the display
void SH1106::drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color) {
    frameBuffer.drawCircle(x0, y0, radius, color);
}

// Draw a filled circle on the display
void SH1106::drawCircleFill(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color) {
    frameBuffer.drawCircleFill(x0, y0, radius, color);
}

// Draw a rectangle on the display
void SH1106::drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color) {
    frameBuffer.drawRect(x, y, width, height, color);
}

// Draw a filled rectangle on the display
void SH1106::drawRectFill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color) {
    frameBuffer.drawRectFill(x, y, width, height, color);
}

// Draw a triangle on the display
void SH1106::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color) {
    frameBuffer.drawTriangle(x0, y0, x1, y1, x2, y2, color);
}

// Draw a filled triangle on the display
void SH1106::drawTriangleFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color) {
    frameBuffer.drawTriangleFill(x0, y0, x1, y1, x2, y2, color);
}

// Blit the contents of a frame buffer to the display
void SH1106::blit(FrameBuffer& src, uint16_t x, uint16_t y) {
    frameBuffer.blit(src, x, y);
}

// Draw text on the display
void SH1106::text(const std::string& str, uint16_t x, uint16_t y) {
    frameBuffer.text(str, x, y, 1);
}

// Update the display with the contents of the frame buffer
void SH1106::show() {
    for (uint8_t page = 0; page < height / 8; ++page) {
        writeCmd(0xB0 | page); // Set page address
        writeCmd(0x02); // Set lower column address
        writeCmd(0x10); // Set higher column address

        // Write data for the entire page
        uint16_t startIndex = width * page;
        for (uint16_t i = 0; i < width; ++i) {
            uint8_t data[] = {0x40, frameBuffer.getBuffer()[startIndex + i]};
            i2c_write_blocking(i2c, addr, data, 2, false);
        }
    }
}


// Write a command to the display
void SH1106::writeCmd(uint8_t cmd) {
    uint8_t buffer[2] = {0x80, cmd}; // Command mode
    i2c_write_blocking(i2c, addr, buffer, 2, false);
}
