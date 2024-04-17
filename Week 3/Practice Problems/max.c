//Learning Goals:
//Pass and array into a function
//Create a helper that finds a maximum value

// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("%i\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    //inisalise comparison variable
    int m;


    //Ittarate over the array
    for (int i = 0; i < n; i++)
    {
        //Hold instance of current element
        m = array[i];

        for (int j = 0; j < n; j++)
        {
            //Compair largest element so far to rest of elements
            if (m < array[j])
            {
                m = array[j];
            }

        }

        //if current element is largest element return
        if (array[i] == m)
        {
            return m;
        }
        
    }

    return m;
}
