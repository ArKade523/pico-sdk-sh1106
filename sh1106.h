#ifndef PICO_SH1106_H
#define PICO_SH1106_H

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "display_i2c.h"
#include <cstdint>

#include "framebuffer.h"

class SH1106 : public Display_I2C {
public:
    SH1106(uint16_t width, uint16_t height, i2c_inst_t* i2c, uint8_t addr, uint gpio_sda, uint gpio_scl);

    void initDisplay();
    void powerOn();
    void reset();
    void fill(uint8_t color);
    void setPixel(uint16_t x, uint16_t y, uint8_t color);
    void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);
    void drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color);
    void drawCircleFill(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color);
    void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
    void drawRectFill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
    void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
    void drawTriangleFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
    void blit(FrameBuffer& src, uint16_t x, uint16_t y);
    void text(const std::string& str, uint16_t x, uint16_t y);
    void show();

protected:
    void writeCmd(uint8_t cmd);

    uint16_t width, height;
    i2c_inst_t* i2c;
    uint8_t addr;
    FrameBuffer frameBuffer;
};

#endif // PICO_SH1106_H
