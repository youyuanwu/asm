extern "C" void kmain()
{
    const short color = 0x0F00;
    const char hello[] = "Hello from cpp file!";
    short* vga = (short*)0xb8000;
    for (unsigned int i = 0; i<sizeof(hello);++i)
        vga[i+80] = color | hello[i];
}