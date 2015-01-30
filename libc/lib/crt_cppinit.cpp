#if 1
extern "C" 
void __static_initialization_and_destruction_0(int, int);

extern "C" 
void crti (void)
{
    __static_initialization_and_destruction_0(1, 0xffff);
}

extern "C" 
void crte (void)
{
    __static_initialization_and_destruction_0(0, 0xffff);
}
#endif

