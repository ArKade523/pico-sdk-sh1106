#include "framebuffer.h"
#include <algorithm>
#include <stdexcept>
#include "font8x8.h"

FrameBuffer::FrameBuffer(uint16_t width, uint16_t height, Format format)
    : width(width), height(height), format(format), buffer(width * height / 8, 0x00) {
}

FrameBuffer::FrameBuffer(const uint8_t* data, uint16_t width, uint16_t height, Format format)
    : width(width), height(height), format(format), buffer(data, data + width * height / 8) {
}

void FrameBuffer::fill(uint8_t color) {
    std::fill(buffer.begin(), buffer.end(), color ? 0xFF : 0x00);
}

void FrameBuffer::setPixel(uint16_t x, uint16_t y, uint8_t color) {
    if (x >= width || y >= height) {
        // throw std::out_of_range("Pixel coordinates out of bounds");
        return;
    }

    uint16_t index;
    uint8_t bit;

    switch (format) {
        case MONO_VLSB:
            index = (x / 8) + y * (width / 8);
            bit = x % 8;
            break;
        case MONO_HLSB:
            index = (y / 8) * width + x;
            bit = y % 8;
            break;
        default:
            // throw std::invalid_argument("Unsupported framebuffer format");
            return;
    }

    if (color) {
        buffer[index] |= (1 << bit);
    } else {
        buffer[index] &= ~(1 << bit);
    }
}

void FrameBuffer::drawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color) {
    int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int16_t err = dx + dy, e2;

    while (true) {
        setPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void FrameBuffer::drawCircle(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color) {
    int16_t x = radius - 1;
    int16_t y = 0;
    int16_t dx = 1;
    int16_t dy = 1;
    int16_t err = dx - (radius << 1);

    while (x >= y) {
        setPixel(x0 + x, y0 + y, color);
        setPixel(x0 + y, y0 + x, color);
        setPixel(x0 - y, y0 + x, color);
        setPixel(x0 - x, y0 + y, color);
        setPixel(x0 - x, y0 - y, color);
        setPixel(x0 - y, y0 - x, color);
        setPixel(x0 + y, y0 - x, color);
        setPixel(x0 + x, y0 - y, color);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void FrameBuffer::drawCircleFill(uint16_t x0, uint16_t y0, uint16_t radius, uint8_t color) {
    int16_t x = radius - 1;
    int16_t y = 0;
    int16_t dx = 1;
    int16_t dy = 1;
    int16_t err = dx - (radius << 1);

    while (x >= y) {
        drawLine(x0 - x, y0 + y, x0 + x, y0 + y, color);
        drawLine(x0 - y, y0 + x, x0 + y, y0 + x, color);
        drawLine(x0 - x, y0 - y, x0 + x, y0 - y, color);
        drawLine(x0 - y, y0 - x, x0 + y, y0 - x, color);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}

void FrameBuffer::drawRect(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color) {
    for (uint16_t i = x; i < x + width; ++i) {
        setPixel(i, y, color);
        setPixel(i, y + height - 1, color);
    }
    for (uint16_t i = y; i < y + height; ++i) {
        setPixel(x, i, color);
        setPixel(x + width - 1, i, color);
    }
}

void FrameBuffer::drawRectFill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint8_t color) {
    for (uint16_t i = y; i < y + height; ++i) {
        drawLine(x, i, x + width - 1, i, color);
    }
}

void FrameBuffer::drawTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color) {
    auto drawLine = [this](uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint8_t color) {
        int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int16_t err = dx + dy, e2;

        while (true) {
            setPixel(x0, y0, color);
            if (x0 == x1 && y0 == y1) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; x0 += sx; }
            if (e2 <= dx) { err += dx; y0 += sy; }
        }
    };

    drawLine(x0, y0, x1, y1, color);
    drawLine(x1, y1, x2, y2, color);
    drawLine(x2, y2, x0, y0, color);
}

void FrameBuffer::drawTriangleFill(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t color) {
    auto drawLine = [this](int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color) {
        int16_t dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int16_t dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int16_t err = dx + dy, e2;

        while (true) {
            setPixel(x0, y0, color);
            if (x0 == x1 && y0 == y1) break;
            e2 = 2 * err;
            if (e2 >= dy) { err += dy; x0 += sx; }
            if (e2 <= dx) { err += dx; y0 += sy; }
        }
    };

    auto swap = [](auto& a, auto& b) {
        auto temp = a;
        a = b;
        b = temp;
    };

    // Sort vertices by y-coordinate
    if (y1 < y0) { swap(y0, y1); swap(x0, x1); }
    if (y2 < y0) { swap(y0, y2); swap(x0, x2); }
    if (y2 < y1) { swap(y1, y2); swap(x1, x2); }

    int16_t dx1 = x1 - x0, dy1 = y1 - y0;
    int16_t dx2 = x2 - x0, dy2 = y2 - y0;
    int16_t dx3 = x2 - x1, dy3 = y2 - y1;

    int16_t sa = 0, sb = 0;
    for (int16_t y = y0; y <= y1; ++y) {
        int16_t a = x0 + sa / dy1;
        int16_t b = x0 + sb / dy2;
        sa += dx1;
        sb += dx2;
        if (a > b) swap(a, b);
        drawLine(a, y, b, y, color);
    }

    sa = dx3 * (y1 - y1);
    sb = dx2 * (y1 - y0);
    for (int16_t y = y1; y <= y2; ++y) {
        int16_t a = x1 + sa / dy3;
        int16_t b = x0 + sb / dy2;
        sa += dx3;
        sb += dx2;
        if (a > b) swap(a, b);
        drawLine(a, y, b, y, color);
    }
}

void FrameBuffer::blit(const FrameBuffer& src, uint16_t x, uint16_t y) {
    for (uint16_t srcY = 0; srcY < src.height; ++srcY) {
        for (uint16_t srcX = 0; srcX < src.width; ++srcX) {
            uint8_t pixelColor = (src.buffer[(srcY / 8) * src.width + srcX] >> (srcY % 8)) & 0x01;
            setPixel(x + srcX, y + srcY, pixelColor);
        }
    }
}

void FrameBuffer::text(const std::string& str, uint16_t x, uint16_t y, uint8_t color) {
    // Assuming a fixed-width font with dimensions 8x8 pixels
    const uint8_t fontWidth = 8;
    const uint8_t fontHeight = 8;

    for (size_t i = 0; i < str.length(); ++i) {
        char c = str[i];
        // Assuming 'font' is an array containing bitmap data for each character
        const uint8_t* charBitmap = font8x8[c]; // Adjust index based on font array

        for (uint8_t row = 0; row < fontHeight; ++row) {
            for (uint8_t col = 0; col < fontWidth; ++col) {
                uint8_t pixelColor = (charBitmap[row] >> col) & 0x01;
                setPixel(x + i * fontWidth + col, y + row, pixelColor ? color : !color);
            }
        }
    }
}

const uint8_t* FrameBuffer::getBuffer() const {
    return buffer.data();
}

uint16_t FrameBuffer::getWidth() const {
    return width;
}

uint16_t FrameBuffer::getHeight() const {
    return height;
}
