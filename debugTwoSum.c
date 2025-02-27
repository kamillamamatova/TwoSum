#include <stdio.h>
#include <stdlib.h>

// Stores index-value pairs
typedef struct{
    int value;
    int index;
} pair;

// Swap function
void swap(pair * a, pair * b){
    pair tmp = *a;
    *a = *b;
    *b = tmp;
}

// Partition function
int partition(pair arr[], int low, int high){
    // Last element is the pivot
    int pivot = arr[high].value;
    // Pointer for the smaller element
    int i = low - 1;

    for(int j = low; j <= high - 1; j++){  // Fixed loop bounds
        // If the current element is smaller than the pivot
        if(arr[j].value < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    // Move pivot to the correct position
    swap(&arr[i + 1], &arr[high]);
    // Return pivot index
    return(i + 1);
}

// Quicksort function
void quickSort(pair arr[], int low, int high){
    if(low < high){
        int partitionIdx = partition(arr, low, high);

        // Recursively sort through the left subarray
        quickSort(arr, low, partitionIdx - 1);
        // Recursively sort through the right array
        quickSort(arr, partitionIdx + 1, high);
    }
}

int* twoSum(int* nums, int numSize, int target, int* returnSize){
    // The result will always have 2 values
    *returnSize = 2;
    // Allocate memory
    int * result = (int*)malloc(2 * sizeof(int));

    // Create an array of pairs
    pair * pairs = (pair*)malloc(numSize * sizeof(pair));
    for(int i = 0; i < numSize; i++){
        // Store value
        pairs[i].value = nums[i];
        // Store index
        pairs[i].index = i;
    }

    // Sort the pairs array based on the values
    quickSort(pairs, 0, numSize - 1);

    // Two-Pointer approach
    int left = 0, right = numSize - 1;
    while(left < right){
        int sum = pairs[left].value + pairs[right].value;
        if(sum == target){
            result[0] = pairs[left].index;
            result[1] = pairs[right].index];
            free(pairs);
            return result;
        }
        else if(sum < target){
            left++;
        }
        else{
            right--;
        }
    }

    free(pairs);
    return NULL;
}

// Prints the result in the correct format
void runTestCase(int * nums, int numSize, int target){
    int returnSize;
    int * result = twoSum(nums, numSize, target, &returnSize);

    // Print input
    printf("Input: nums = [");
    for(int i = 0; i < numSize; i++){
        printf("%d", nums[i]);
        if(i < numSize - 1){
            printf(",");
        }
    }
    printf("], target = %d\n", target);

    // Check for valid result
    if (result) {
        printf("Output: [%d,%d]\n", result[0], result[1]);
        printf("Explanation: Because nums[%d] + nums[%d] == %d, we return [%d,%d].\n", 
               result[0], result[1], target, result[0], result[1]);
        free(result);
    } else {
        printf("No valid pair found.\n");
    }
}

int main(){
    int numSize, target;

    // Ask user for array size
    printf("How many elements are in the array: ");
    scanf("%d", &numSize);

    // Allocate memory
    int * nums = (int*)malloc(numSize * sizeof(int));

    // Ask user for elements
    printf("\nEnter %d elements: ", numSize);
    for(int i = 0; i < numSize; i++){
        scanf("%d", &nums[i]);
    }

    // Ask user for target value
    printf("\nEnter the target value: ");
    scanf("%d", &target);

    runTestCase(nums, numSize, target);

    // Free allocated memory
    free(nums);

    return 0;
}
