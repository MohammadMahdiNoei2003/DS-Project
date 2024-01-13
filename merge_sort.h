#include <stdio.h>

void merge(int arr[], int left[], int leftSize, int right[], int rightSize)
{
    int i = 0; // Index for left subarray
    int j = 0; // Index for right subarray
    int k = 0; // Index for merged array

    // Merge the two subarrays in sorted order
    while (i < leftSize && j < rightSize)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of the left subarray, if any
    while (i < leftSize)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of the right subarray, if any
    while (j < rightSize)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

// Merge Sort function
void merge_sort(int arr[], int size)
{
    if (size <= 1)
    {
        return; // Base case: array of size 1 is already sorted
    }

    int mid = size / 2;

    // Create two temporary subarrays
    int left[mid];
    int right[size - mid];

    // Populate the left and right subarrays
    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }

    // Recursively sort the left and right subarrays
    merge_sort(left, mid);
    merge_sort(right, size - mid);

    // Merge the sorted subarrays
    merge(arr, left, mid, right, size - mid);
}

// Function to print an array
void print_merge_sort_array(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ,", arr[i]);
    }
    printf("\n");
}