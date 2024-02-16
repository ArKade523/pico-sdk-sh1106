#ifndef PICO_SDK_DISPLAY_I2C_H
#define PICO_SDK_DISPLAY_I2C_H

#include <cstdint>
#include <string>
#include "hardware/i2c.h"
#include "framebuffer.h"

class Display_I2C {
public:
    Display_I2C(uint16_t width, uint16_t height, i2c_inst_t* i2c, uint8_t addr, uint gpio_sda, uint gpio_scl) : 
        width(width), height(height), i2c(i2c), addr(addr), frameBuffer(width, height, FrameBuffer::MONO_HLSB) { }

    virtual void initDisplay() = 0;
    virtual void powerOn() = 0;
    virtual void reset() = 0;
    virtual void fill(uint8_t color) = 0;
    virtual void setPixel(uint16_t x, uint16_t y, uint8_t color) = 0;
    virtual void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color) = 0;
    virtual void drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color) = 0;
    virtual void drawCircleFill(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color) = 0;
    virtual void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color) = 0;
    virtual void drawRectFill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color) = 0;
    virtual void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color) = 0;
    virtual void drawTriangleFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color) = 0;
    virtual void blit(FrameBuffer& src, uint16_t x, uint16_t y) = 0;
    virtual void text(const std::string& str, uint16_t x, uint16_t y) = 0;
    virtual void show() = 0;

private:
    uint16_t width, height;
    i2c_inst_t* i2c;
    uint8_t addr;
    FrameBuffer frameBuffer; 
};

#endif //PICO_SDK_DISPLAY_I2C_H