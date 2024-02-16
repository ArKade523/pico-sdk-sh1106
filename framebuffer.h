#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <cstdint>
#include <vector>
#include <string>

class FrameBuffer {
public:
    enum Format {
        MONO_VLSB,
        MONO_HLSB
    };

    FrameBuffer(uint16_t width, uint16_t height, Format format);
    FrameBuffer(const uint8_t* data, uint16_t width, uint16_t height, Format format);
    void fill(uint8_t color);
    void setPixel(uint16_t x, uint16_t y, uint8_t color);
    void drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color);
    void drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color);
    void drawCircleFill(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color);
    void drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
    void drawRectFill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color);
    void drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);
    void drawTriangleFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color);

    const uint8_t* getBuffer() const;
    uint16_t getWidth() const;
    uint16_t getHeight() const;
    void blit(const FrameBuffer& src, uint16_t x, uint16_t y);
    void text(const std::string& str, uint16_t x, uint16_t y, uint8_t color);


private:
    uint16_t width;
    uint16_t height;
    Format format;
    std::vector<uint8_t> buffer;
};

#endif // FRAMEBUFFER_H
