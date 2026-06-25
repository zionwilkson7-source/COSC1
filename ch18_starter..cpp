// ============================================================
// COSC 1437 - Chapter 18: Searching and Sorting Algorithms
// Name:
// Date:
// ============================================================

#include <iostream>
using namespace std;

// ============================================================
// CONSTANTS
// ============================================================
const int SIZE = 10;

// ============================================================
// FUNCTION PROTOTYPES
// ============================================================

// --- Searching ---
int linearSearch(int arr[], int size, int target);
int binarySearch(int arr[], int size, int target);

// --- Sorting (YOU implement these) ---
void bubbleSort(int arr[], int size);
void selectionSort(int arr[], int size);
void insertionSort(int arr[], int size);

// --- Sorting (Scaffolded - study and run these) ---
void quickSort(int arr[], int low, int high);
int  partition(int arr[], int low, int high);
void mergeSort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);

// --- Utility ---
void printArray(int arr[], int size);
void copyArray(int src[], int dest[], int size);


// ============================================================
// MAIN
// ============================================================
int main()
{
    // Original dataset - DO NOT modify this
    int original[SIZE] = {64, 25, 12, 78, 33, 90, 47, 5, 61, 18};

    // Working copy used for each sort so we always start fresh
    int arr[SIZE];

    cout << "=== Chapter 18: Searching and Sorting ===" << endl << endl;

    // ----------------------------------------------------------
    // PART 1: LINEAR SEARCH
    // ----------------------------------------------------------
    cout << "--- Linear Search ---" << endl;
    cout << "Array: ";
    printArray(original, SIZE);

    int target = 78;
    int result = linearSearch(original, SIZE, target);
    if (result != -1)
        cout << "Found " << target << " at index " << result << endl;
    else
        cout << target << " not found." << endl;

    target = 99;
    result = linearSearch(original, SIZE, target);
    if (result != -1)
        cout << "Found " << target << " at index " << result << endl;
    else
        cout << target << " not found." << endl;

    cout << endl;

    // ----------------------------------------------------------
    // PART 2: BUBBLE SORT
    // ----------------------------------------------------------
    cout << "--- Bubble Sort ---" << endl;
    copyArray(original, arr, SIZE);
    cout << "Before: ";
    printArray(arr, SIZE);

    bubbleSort(arr, SIZE);

    cout << "After:  ";
    printArray(arr, SIZE);
    cout << endl;

    // ----------------------------------------------------------
    // PART 3: SELECTION SORT
    // ----------------------------------------------------------
    cout << "--- Selection Sort ---" << endl;
    copyArray(original, arr, SIZE);
    cout << "Before: ";
    printArray(arr, SIZE);

    selectionSort(arr, SIZE);

    cout << "After:  ";
    printArray(arr, SIZE);
    cout << endl;

    // ----------------------------------------------------------
    // PART 4: INSERTION SORT
    // ----------------------------------------------------------
    cout << "--- Insertion Sort ---" << endl;
    copyArray(original, arr, SIZE);
    cout << "Before: ";
    printArray(arr, SIZE);

    insertionSort(arr, SIZE);

    cout << "After:  ";
    printArray(arr, SIZE);
    cout << endl;

    // ----------------------------------------------------------
    // PART 5: QUICK SORT (scaffolded)
    // ----------------------------------------------------------
    cout << "--- Quick Sort (scaffolded) ---" << endl;
    copyArray(original, arr, SIZE);
    cout << "Before: ";
    printArray(arr, SIZE);

    quickSort(arr, 0, SIZE - 1);

    cout << "After:  ";
    printArray(arr, SIZE);
    cout << endl;

    // ----------------------------------------------------------
    // PART 6: MERGE SORT (scaffolded)
    // ----------------------------------------------------------
    cout << "--- Merge Sort (scaffolded) ---" << endl;
    copyArray(original, arr, SIZE);
    cout << "Before: ";
    printArray(arr, SIZE);

    mergeSort(arr, 0, SIZE - 1);

    cout << "After:  ";
    printArray(arr, SIZE);
    cout << endl;

    // ----------------------------------------------------------
    // PART 7: BINARY SEARCH
    // Note: Binary Search requires a SORTED array!
    // We re-sort arr with bubbleSort first.
    // ----------------------------------------------------------
    cout << "--- Binary Search ---" << endl;
    copyArray(original, arr, SIZE);
    bubbleSort(arr, SIZE);   // must sort before binary searching
    cout << "Sorted array: ";
    printArray(arr, SIZE);

    target = 47;
    result = binarySearch(arr, SIZE, target);
    if (result != -1)
        cout << "Found " << target << " at index " << result << endl;
    else
        cout << target << " not found." << endl;

    target = 99;
    result = binarySearch(arr, SIZE, target);
    if (result != -1)
        cout << "Found " << target << " at index " << result << endl;
    else
        cout << target << " not found." << endl;

    cout << endl;

    return 0;
}


// ============================================================
// UTILITY FUNCTIONS (provided for you)
// ============================================================

// Prints all elements of an array on one line
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Copies src[] into dest[] element by element
void copyArray(int src[], int dest[], int size)
{
    for (int i = 0; i < size; i++)
        dest[i] = src[i];
}


// ============================================================
// PART 1 - LINEAR SEARCH (provided for you)
// ============================================================
// Examines each element one at a time until the target is found
// or the end of the array is reached.
// Returns the index of the target, or -1 if not found.
int linearSearch(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
            return i;   // found it - return the index
    }
    return -1;          // never found it
}


// ============================================================
// PART 2 - BUBBLE SORT  ** YOU IMPLEMENT THIS **
// ============================================================
// Compare adjacent pairs. If left > right, swap them.
// After each full pass, the largest unsorted value "bubbles"
// to its correct position at the end.
// Repeat for (size - 1) passes total.
//
// Hint: you need two nested loops.
//   Outer loop: controls the number of passes (size - 1 passes)
//   Inner loop: walks through the unsorted portion comparing neighbors
void bubbleSort(int arr[], int size)
{
    // TODO: implement bubble sort here

}


// ============================================================
// PART 3 - SELECTION SORT  ** YOU IMPLEMENT THIS **
// ============================================================
// On each pass, find the smallest element in the unsorted
// portion of the array, then swap it into its correct position.
//
// Hint: you need two nested loops.
//   Outer loop: position we're filling (0 to size-2)
//   Inner loop: search through the rest of the array for the minimum
//   After inner loop: swap arr[outer] with arr[minIndex]
void selectionSort(int arr[], int size)
{
    // TODO: implement selection sort here

}


// ============================================================
// PART 4 - INSERTION SORT  ** YOU IMPLEMENT THIS **
// ============================================================
// Build the sorted portion one element at a time.
// Take the next unsorted element and "insert" it into its
// correct position by shifting larger elements right.
//
// Hint:
//   Outer loop: starts at index 1 (first element is trivially sorted)
//   Save arr[i] as "key"
//   Inner loop: shift elements that are greater than key one spot right
//   Place key in the gap that was created
void insertionSort(int arr[], int size)
{
    // TODO: implement insertion sort here

}


// ============================================================
// PART 5 - QUICK SORT (scaffolded - study this, do not modify)
// ============================================================
// Strategy: pick a "pivot" value, then rearrange the array so
// everything smaller than pivot is on the left, everything larger
// is on the right. Then recursively sort each half.
//
// RECURSION NOTE: quickSort calls itself on smaller sub-arrays.
// Each call works on a smaller piece (low..high shrinks each time)
// until low >= high, meaning the piece has 0 or 1 element - already sorted.
// That's the base case that stops the recursion.

// partition() rearranges arr[low..high] around a pivot.
// Returns the final index of the pivot.
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];  // use the last element as pivot
    int i = low - 1;        // i tracks the boundary of "small" elements

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            // swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i]   = arr[j];
            arr[j]   = temp;
        }
    }

    // Place pivot in its correct sorted position
    int temp   = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high]  = temp;

    return i + 1;  // return pivot's final index
}

// quickSort recursively sorts arr[low..high]
void quickSort(int arr[], int low, int high)
{
    // BASE CASE: if low >= high, this sub-array has 0 or 1 element - done
    if (low >= high)
        return;

    // Partition the array; pi is where the pivot landed
    int pi = partition(arr, low, high);

    // RECURSIVE CALLS: sort the left half and right half independently
    quickSort(arr, low, pi - 1);   // everything left of pivot
    quickSort(arr, pi + 1, high);  // everything right of pivot
}


// ============================================================
// PART 6 - MERGE SORT (scaffolded - study this, do not modify)
// ============================================================
// Strategy: split the array in half, sort each half, then
// merge the two sorted halves back together.
//
// RECURSION NOTE: mergeSort splits until each piece is 1 element
// (base case: left >= right). Then merge() combines sorted pieces
// back up. Think of it like splitting a deck of cards in half
// repeatedly, then carefully interleaving them back in order.

// merge() combines two already-sorted halves: arr[left..mid] and arr[mid+1..right]
void merge(int arr[], int left, int mid, int right)
{
    // Calculate the sizes of the two halves
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Temporary arrays to hold the two halves
    int L[n1], R[n2];

    // Copy data into temp arrays
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    // Merge the two halves back into arr[], picking the smaller element each time
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    // Copy any remaining elements from either half
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// mergeSort recursively sorts arr[left..right]
void mergeSort(int arr[], int left, int right)
{
    // BASE CASE: a single element is already sorted
    if (left >= right)
        return;

    // Find the midpoint
    int mid = left + (right - left) / 2;

    // RECURSIVE CALLS: sort the left half, then the right half
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Merge the two sorted halves together
    merge(arr, left, mid, right);
}


// ============================================================
// PART 7 - BINARY SEARCH  ** YOU IMPLEMENT THIS **
// ============================================================
// IMPORTANT: The array MUST be sorted before calling this!
//
// Strategy: repeatedly cut the search range in half.
//   - Check the middle element
//   - If it matches, return that index
//   - If target < middle, search the LEFT half
//   - If target > middle, search the RIGHT half
//   - If low > high, the element is not in the array
//
// Hint: use a while loop with variables low, high, and mid.
//   low starts at 0, high starts at size - 1
//   Each iteration: mid = (low + high) / 2
int binarySearch(int arr[], int size, int target)
{
    // TODO: implement binary search here

    return -1;  // not found (keep this as your default return)
}