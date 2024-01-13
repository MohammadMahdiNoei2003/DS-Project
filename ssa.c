#include <stdio.h>

#include "merge_sort.h"
#include "quick_sort.h"
#include "bubble_sort.h"
#include "binary_search.h"

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ,", arr[i]);
    }
    printf("\n");
}

int main() {
    int size;
    printf("Enter size of the Array: ");
    scanf("%d", &size);

    int array[size];
    printf("\nEnter %d elements", size);
    for (int i = 0; i < size; i++) {
        printf("\nElement %d: ", i+1);
        scanf("%d", &array[i]);
    }

    printf("\nOriginal Array: ");
    print_array(array, size);

    merge_sort(array, size - 1);

    printf("Sorted Array by Merge Sort: ");
    print_merge_sort_array(array, size);
    printf("\n");

    int target;
    printf("Enter the target value to search: ");
    scanf("%d", &target);

    int result = binary_search(array, 0, size - 1, target);

    if (result == -1) {
        printf("Target value not found in this array.\n");
    }
    else {
        printf("Target value found at index %d of array.\n", result);
    }

    return 0;
}