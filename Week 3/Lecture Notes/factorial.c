#include <stdio.h>
#include <cs50.h>

int factorial(int n);

int main(void)
{
    //prompt user for number
    int n = get_int("Type a number: ");
    printf("%i\n", factorial(n));
}

int factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }

    return n * factorial(n-1);

}
