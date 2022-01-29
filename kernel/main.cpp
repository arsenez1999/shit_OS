#include <tty.hpp>

extern "C" void kernel_main()
{
    tty::init();
    tty::write_str("Hello, world!");
}