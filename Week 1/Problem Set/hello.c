#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //get user name
    string name = get_string("What's your name? ");
    //print user name to terminal
    printf("Hello %s!!\n", name);
}
