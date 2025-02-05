#include <stdio.h>
#include "united.h"

_pure_ _nothrow_ int Add(int a, int b) {
    return a + b;
}

_hot_ _const_ int Multiply(int a, int b) {
    return a * b;
}

_cold_ _deprecated_ void OldFunction(void) {
    printf("This function is deprecated.\n");
}

struct _packed_ PackedStruct {
    int a;
    char b;
    short c;
};

struct _aligned_(16) AlignedStruct {
    int a;
    char b;
    short c;
};

#if defined(__x86_64__)
_sysv_abi_ void CdeclFunction(void) {
    printf("This function uses the cdecl calling convention.\n");
}

_ms_abi_ void FastcallFunction(void) {
    printf("This function uses the fastcall calling convention.\n");
}
#elif defined(__i386__)
_cdecl_ void CdeclFunction(void) {
    printf("This function uses the cdecl calling convention.\n");
}

_fastcall_ void FastcallFunction(void) {
    printf("This function uses the fastcall calling convention.\n");
}
#endif

/* This feature will need to be updated to ensure compatibility with the later standards */
void LongLongTest(void) {
    _long_long_ a = _make_long_long_(1, 0);
    _long_long_ b = _make_long_long_(2, 0);
    _long_long_ result;

    result = a;
    _long_long_add_(result, b);
    printf("%d + %d = %d\n", _long_long_low_(a), _long_long_low_(b), _long_long_low_(result));

    result = a;
    _long_long_mul_(result, b);
    printf("%d * %d = %d\n", _long_long_low_(a), _long_long_low_(b), _long_long_low_(result));
}

_vla_(char, str) = "Hello, world!";

/* This whole file uses ANSI C for programming, and should work with the mainstream compilers. */
c_style int main(void) {
    printf("United.h feature test:\n");

    printf("For loop macro test:\n");
    _for_(int i = 0, i < 10, i++, {
        printf("%d\n", i);
    })
    printf("\n");

    printf("Pure/nothrow add test: %d\n", Add(1, 2));
    printf("Hot/const multiply test: %d\n\n", Multiply(3, 4));

    printf("Testing struct alignment:\n");
    printf("Packed struct size: %lu\n", sizeof(struct PackedStruct));
    printf("Aligned struct size: %lu\n", sizeof(struct AlignedStruct));
    printf("\n");

    printf("Testing long long operations:\n");
    LongLongTest();
    printf("\n");

    printf("VLA test:\n");
    printf("%s\n", str);

    localvar(
        /* This macro allows for a more local variable declaration with ANSI C */
        _atomic_ int atomic = 3;
        printf("Atomic variable: %d\n", atomic);
    )

    printf("Calling conventions test:\n");
    #if defined(__x86_64__)
    CdeclFunction();
    FastcallFunction();
    #elif defined(__i386__)
    CdeclFunction();
    FastcallFunction();
    #endif
    return 0;
}
