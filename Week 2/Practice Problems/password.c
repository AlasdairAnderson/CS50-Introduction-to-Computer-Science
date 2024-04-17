// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    //inicialise check varibales
    bool upper = false;
    bool lower = false;
    bool number = false;
    bool symbol = false;

    int i = 0;
    //loop through password
    while (password[i] != '\0')
    {
        //valuate if any criteria is met
        if (ispunct(password[i]))
        {
            symbol = true;
        }
        else if (isdigit(password[i]))
        {
            number = true;
        }
        else if (isupper(password[i]))
        {
            upper = true;
        }
        else if (islower(password[i]))
        {
            lower = true;
        }

        i++;
    }

    //does the password meet the requirements
    if (symbol == true && number == true && upper == true && lower == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
