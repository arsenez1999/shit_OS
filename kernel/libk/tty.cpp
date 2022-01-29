#include "include/tty.hpp"

size_t tty::row;
size_t tty::column;
uint8_t tty::color;
uint16_t *tty::vga_buffer;

void tty::init()
{
    row = 0;
    column = 0;
    color = vga_color(vga::WHITE, vga::BLACK);
    vga_buffer = reinterpret_cast<uint16_t*>(0xb8000);
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_HEIGHT; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            vga_buffer[index] = vga_symbol(' ', color);
        }
    }
}

void tty::putchar_at(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    vga_buffer[index] = vga_symbol(c, color);
}

void tty::putchar(char c)
{
    putchar_at(c, color, column, row);
    if (++column == VGA_WIDTH)
    {
        column = 0;
        if (++row == VGA_HEIGHT)
        {
            row = 0;
        }
    }
}

void tty::write(const char *data, size_t size)
{
    for (size_t i = 0; i < size; i++)
        putchar(data[i]);
}

void tty::write_str(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        putchar(str[i]);
}

void tty::set_color(uint8_t color)
{
    tty::color = color;
}

uint8_t tty::vga_color(tty::vga foreground, tty::vga background)
{
    return static_cast<uint8_t>(background) << 4 | static_cast<uint8_t>(foreground);
}

uint16_t tty::vga_symbol(unsigned char uc, uint8_t color)
{
    return static_cast<uint16_t>(color) << 8 | static_cast<uint16_t>(uc);
}