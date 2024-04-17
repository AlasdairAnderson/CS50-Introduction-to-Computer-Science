#include <stdio.h>

int main(void)
{
    int a[5] = {1,2,3,4,5};
    int *p = a;

    printf("%i\n", *p);
    printf("%i\n", *(p + 20000));

}
