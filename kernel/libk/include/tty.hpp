#pragma once
#include <stddef.h>
#include <stdint.h>

class tty
{
public:
    static void init();
    static void putchar_at(char c, uint8_t color, size_t x, size_t y);
    static void putchar(char c);
    static void write(const char* data, size_t size);
    static void write_str(const char* str);
    static void set_color(uint8_t color);

    enum class vga : uint8_t
    {
        BLACK = 0,
        WHITE = 15
    };

    static inline uint8_t vga_color(vga foreground, vga background);
    static inline uint16_t vga_symbol(unsigned char uc, uint8_t color);

private:
    static const size_t VGA_WIDTH = 80;
    static const size_t VGA_HEIGHT = 25;
    static size_t row;
    static size_t column;
    static uint8_t color;
    static uint16_t* vga_buffer;
};