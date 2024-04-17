#include <cs50.h>
#include <stdio.h>
#include <math.h>

//inicialising functions
int numberlength(long n);
bool checksum(long n, int l);
void validcard(long n, int l, bool s);

int main(void)
{
    //Promt User for card number
    long cardnumber = get_long("Number: ");

    //Calcualte Length
    int length = numberlength(cardnumber);

    //Calculate checksum
    bool sum = checksum(cardnumber, length);

    //validate cards
    validcard(cardnumber, length, sum);

}

int numberlength(long n)
{
    long cnumber = n;
    int length = 0;

    //get length of card
    while (cnumber > 0)
    {
        cnumber /= 10;
        length++;
    }
    return length;
}

bool checksum(long n, int l)
{
    //incial vairables
    long cnumber = n;
    int length = l, sumodds, sumeven, sums, ldigit;

    cnumber = n;
    int lengthother = length / 2;
    cnumber *= 10;

    //Multiply every other digit by 2, starting with the numbers' second-to last digit,
    while (lengthother > 0)
    {
        //extract other digit
        cnumber /= 100;
        int d = cnumber % 10;
        int sum = d;

        //multiply other digit
        sum *= 2;

        //Add products together
        while (sum > 0)
        {
            int di = sum % 10;
            sum = sum / 10;
            int sum2 = di;
            sumodds = sumodds + sum2;
        }
        lengthother--;
    }

    //reset credit cnumber and lengthother
    cnumber = n;
    lengthother = (length + 1) / 2;


    //Sum digits not multipled by 2 (Starting from the end)
    while (lengthother > 0)
    {
        int d = cnumber % 10;
        cnumber /= 100;
        int sum = d;

        sumeven = sumeven + sum;
        lengthother--;
    }

    sums = sumodds + sumeven;

    //find last digit
    ldigit = sums % 10;

    //return values
    if (ldigit == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void validcard(long n, int l, bool s)
{
    //inical varibles
    long fdigit = n;
    int length = l;
    bool valid = s;

    //get first digit
    while (length > 2)
    {
        fdigit /= 10;
        length--;
    }

    long vdigit = fdigit / 10;
    length = l;

    //Validate Card
    if (valid == false)
    {
        printf("INVALID\n");
    }
    else if ((fdigit == 34 || fdigit == 37) && (length == 15) && (valid == true))
    {
        printf("AMEX\n");
    }
    else if ((fdigit == 51 || fdigit == 52 || fdigit == 53 || fdigit == 54 || fdigit == 55) && (length == 16) && (valid == true))
    {
        printf("MASTERCARD\n");
    }
    else if ((vdigit == 4) && (length == 13 || length == 16) && (valid == true))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
