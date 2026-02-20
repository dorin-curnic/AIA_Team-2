#include "merge_sort.hpp"

void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    std::vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSortRec(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        if (r - l <= 16) {
            // Insertion Sort optimization for small subarrays
            for (int i = l + 1; i <= r; i++) {
                int key = arr[i];
                int j = i - 1;
                while (j >= l && arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = key;
            }
            return;
        }
        
        int m = l + (r - l) / 2;
        mergeSortRec(arr, l, m);
        mergeSortRec(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSort(std::vector<int> &arr) {
    if (arr.empty()) return;
    mergeSortRec(arr, 0, arr.size() - 1);
}
