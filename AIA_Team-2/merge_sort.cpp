#include "merge_sort.hpp"
#include <iostream>
#include <cstring>

void merge(std::vector<int>& arr, std::vector<int>& temp, int l, int mid, int r) {
    // Copy the entire segment
    std::memcpy(&temp[l], &arr[l], (r - l + 1) * sizeof(int));

    // Merge back + sorting
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (temp[i] <= temp[j])
            arr[k++] = temp[i++];
        else
            arr[k++] = temp[j++];
    }
    // Adding remainders
    while (i <= mid)
        arr[k++] = temp[i++];
    while (j <= r)
        arr[k++] = temp[j++];
}

void mergeSortAlg(std::vector<int>& arr, std::vector<int>& temp, int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        // Sorting left and right
        mergeSortAlg(arr, temp, l, mid);
        mergeSortAlg(arr, temp, mid + 1, r);
        // Merging back
        merge(arr, temp, l, mid, r);
    }
}

// Cover function
void mergeSort(std::vector<int>& arr) {
    if (arr.size() <= 1) return;
    // Single temp vector
    std::vector<int> temp(arr.size());
    mergeSortAlg(arr, temp, 0, arr.size() - 1);
}
