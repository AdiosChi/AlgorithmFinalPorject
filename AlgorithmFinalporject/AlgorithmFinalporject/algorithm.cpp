#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>    // For timing
using namespace std;

void Swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void quickSort(vector<int>& arr, int f, int l) {
    if (f >= l) return;

    int X = arr[f];
    int i = f + 1;
    int j = l;

    while (i <= j) {
        while (arr[j] > X && j >= f + 1) {
            j--;
        }
        while (arr[i] <= X && i <= l) {
            i++;
        }
        if (i < j) {
            Swap(arr[i], arr[j]);
        }
    }

    Swap(arr[f], arr[j]);
    quickSort(arr, f, j - 1);
    quickSort(arr, j + 1, l);
}

void maxheap(vector<int>& arr, int n, int i) {
    int parent = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[parent])
        parent = left;

    if (right < n && arr[right] > arr[parent])
        parent = right;

    if (parent != i) {
        Swap(arr[i], arr[parent]);
        maxheap(arr, n, parent);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        maxheap(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        Swap(arr[0], arr[i]);
        maxheap(arr, i, 0);
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
}

// Function to generate a random array
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int& num : arr) {
        num = rand() % 1000000; // Random number in range [0, 999999]
    }
    return arr;
}

// Function to measure average sorting time
void measureSortingTime(int size) {
    double totalQuickSortTime = 0.0;
    double totalHeapSortTime = 0.0;
    double totalInsertionSortTime = 0.0;

    for (int i = 0; i < 4; ++i) {
        // Generate random array
        vector<int> arr = generateRandomArray(size);

        // Measure Quick Sort time
        vector<int> quickSortArray = arr;
        auto start = chrono::high_resolution_clock::now();
        quickSort(quickSortArray, 0, quickSortArray.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        totalQuickSortTime += chrono::duration<double, milli>(end - start).count();

        // Measure Heap Sort time
        vector<int> heapSortArray = arr;
        start = chrono::high_resolution_clock::now();
        heapSort(heapSortArray);
        end = chrono::high_resolution_clock::now();
        totalHeapSortTime += chrono::duration<double, milli>(end - start).count();

        // Measure Insertion Sort time
        vector<int> insertionSortArray = arr;
        start = chrono::high_resolution_clock::now();
        insertionSort(insertionSortArray);
        end = chrono::high_resolution_clock::now();
        totalInsertionSortTime += chrono::duration<double, milli>(end - start).count();

        cout << "Array size: " << size << "\n";
        cout << "Average Quick Sort time: " << totalQuickSortTime / 4 << " ms\n";
        cout << "Average Heap Sort time: " << totalHeapSortTime / 4 << " ms\n";
        cout << "Average Insertion Sort time: " << totalInsertionSortTime / 4 << " ms\n";
        cout << "-----------------------------------------\n";
    }
}
    int main() {
        srand(static_cast<unsigned>(time(0)));

        // Array sizes to test
        vector<int> sizes = { 100, 1000, 10000, 100000, 1000000 };

        for (int size : sizes) {
            measureSortingTime(size);
        }

        return 0;
    }
