#include <iostream>
#include <limits>
#include <vector>

void insertIntoSortedArray(int arr[], int &n, int x) {
    size_t i = n - 1;
    for (; i >= 0 && arr[i] > x; i--) {
        arr[i + 1] = arr[i];
    }
    arr[i + 1] = x;
    n++;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    int tab[10] = {10, 20, 30, 40, 50};
    int size = 5;
    insertIntoSortedArray(tab, size, 55);
    printArray(tab, size);
    insertIntoSortedArray(tab, size, 55);
    printArray(tab, size);
    return 0;
}
