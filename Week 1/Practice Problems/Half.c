// Calculate your half of a restaurant bill
// Data types, operations, type casting, return value

#include <cs50.h>
#include <stdio.h>

float half(float bill, float tax, int tip);

int main(void)
{
    float bill_amount = get_float("Bill before tax and tip: ");
    float tax_percent = get_float("Sale Tax Percent: ");
    int tip_percent = get_int("Tip percent: ");

    printf("You will owe $%.2f each!\n", half(bill_amount, tax_percent, tip_percent));
}

// TODO: Complete the function
float half(float bill, float tax, int tip)
{
    //Tax Calcualtion
    float taxCalculation = tax / 100 + 1;

    //Tip Calculation
    float tipCalculation = ((float)tip / 100) + 1;

    //add tax to the bill
    float billWithTax = bill * taxCalculation;

    //add bill tip
    float billWithTip = billWithTax * tipCalculation;

    //Split bill
    float splitBill = billWithTip / 2;

    return splitBill;
}
