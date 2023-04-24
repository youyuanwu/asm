extern "C" void kmain()
{
    // color of the text displayed by vga
    const short color = 0x0E00;
    static_assert(sizeof(short) == 2U);
    const char hello[] = "Hello from cpp file!";
    // fixed vga buffer location.
    short* vga = (short*)0xb8000;
    for (unsigned int i = 0; i<sizeof(hello);++i)
        // 80 is the windows width. This writes to the second line.
        vga[i+80] = color | hello[i];
}