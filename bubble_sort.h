#include <stdio.h>

void bubble_swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[i] > arr[j + 1])
            {
                bubble_swap(&arr[i], &arr[j + 1]);
            }
        }
    }
}

void print_bubble_sort_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ,", arr[i]);
    }
    printf("\n");
}