#include <iostream>

using namespace std;

void merge(int arr[], int left[], int leftSize, int right[], int rightSize)
{
    int i = 0;
    int j = 0;
    int k = 0;

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

    while (i < leftSize)
    {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < rightSize)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void sort(int arr[], int size)
{
    if (size <= 1)
    {
        return;
    }

    int mid = size / 2;

    int left[mid];
    int right[size - mid];

    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int i = mid; i < size; i++)
    {
        right[i - mid] = arr[i];
    }

    sort(left, mid);
    sort(right, size - mid);

    merge(arr, left, mid, right, size - mid);
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << ", ";
    }
}

int main()
{
    int size;
    cout << "Enter size of array: ";
    cin >> size;
    int arr[size];
    cout << "Enter array elements: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Element " << i + 1 << ": ";
        cin >> arr[i];
    }

    sort(arr, size);
    cout << "Array: " << endl
         << "{";
    printArray(arr, size);
    cout << "}" << endl;

    int max = arr[size - 1];
    int min = arr[0];

    cout << "Maximum: " << max << endl;
    cout << "Minimum: " << min << endl;

    return 0;
}