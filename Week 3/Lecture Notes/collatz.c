// This program gives an example of recusion with multiple recursive cases
#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    int steps = 0;
    do
    {
        steps = collatz(get_int("Number: "));
    }
    while (steps < 0);


    printf("Number of steps = %i\n", steps);

    return 0;
}

int collatz(int n)
{
    //base case
    if (n == 1)
    {
        return 0;
    }
    //even numbers
    else if (n%2 == 0)
    {
        return 1 + collatz(n/2);
    }
    //odd numbers
    else
    {
        return 1 + collatz((3 * n) + 1);
    }
}
