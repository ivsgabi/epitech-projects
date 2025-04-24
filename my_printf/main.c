#include "my.h"

int main(void)
{
    my_printf("toto1");
    // expected output: toto1

    char str[5];
    my_strcpy(str,"toto");
    str[1] = 6;
    my_printf("%S",str);
    // expected output: t\\006to

    int c = 100;
    my_printf("%b", c);
    // expected output: 1100100

    my_printf("%i",-12);
    // expected output: -12

    my_printf("%s", "test");
    // expected output: test

    my_printf("%d", 12);
    // expected output: 12

    my_printf("%o", 100);
    // expected output: 144

    my_printf("%X", 123456);
    // expected output: 1e240

    my_printf("%%");
    // expected output: %

    my_printf("%#x");
    // expected output: 0x1e240

    my_printf("%#o");
    // expected output: 0361100
}