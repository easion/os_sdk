#define get_esp() ({ int v; __asm__ __volatile__("movl %%esp,%0":"=r"(v)); v; })

#define check_stack() do { \
    unsigned long esp,top; \
    esp=get_esp(); \
    top=stack_top(); \
    if(esp>top) { \
	__libclog_printf("%s:%d: stack underflow, %d bytes\n",__FILE__,__LINE__,esp-top); \
	abort(); \
    } \
    if(esp<(top-0x80000)) { \
	__libclog_printf("%s:%d: stack overflow, %d bytes\n",__FILE__,__LINE__,(top-0x800000)-esp); \
	abort(); \
    } \
} while(0)
