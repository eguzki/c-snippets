#include <stdio.h>

#include <b.h>
#include <a.h>
 
void fooD(void)
{
    fooA();
    fooB();
    puts("Hello, I am D");
}
