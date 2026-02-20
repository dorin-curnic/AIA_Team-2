#include "introsort.hpp"
#include <algorithm>
#include <cmath>

void ins(std::vector<int>& a, int l, int r) {
    for (int i = l + 1; i <= r; i++) {
        int k = a[i];
        int j = i - 1;
        while (j >= l && a[j] > k) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = k;
    }
}

// heapsort fallback
void heap(std::vector<int>& a, int l, int r) {
    int n = r - l + 1;
    // build heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        int x = i;
        while (true) {
            int big = x;
            int lf = 2 * x + 1;
            int rt = 2 * x + 2;
            if (lf < n && a[l + lf] > a[l + big])
                big = lf;
            if (rt < n && a[l + rt] > a[l + big])
                big = rt;
            if (big == x) break;
            std::swap(a[l + x], a[l + big]);
            x = big;
        }
    }
    
    // extract from heap
    for (int i = n - 1; i > 0; i--) {
        std::swap(a[l], a[l + i]);
        int sz = i;
        int j = 0;
        while (true) {
            int big = j;
            int lf = 2 * j + 1;
            int rt = 2 * j + 2;
            if (lf < sz && a[l + lf] > a[l + big])
                big = lf;
            if (rt < sz && a[l + rt] > a[l + big])
                big = rt;
            if (big == j) break;
            std::swap(a[l + j], a[l + big]);
            j = big;
        }
    }
}

// median of 3 pivot
int med3(std::vector<int>& a, int l, int r) {
    int m = l + (r - l) / 2;
    if (a[l] > a[m]) std::swap(a[l], a[m]);
    if (a[l] > a[r]) std::swap(a[l], a[r]);
    if (a[m] > a[r]) std::swap(a[m], a[r]);
    std::swap(a[m], a[r - 1]);
    return a[r - 1];
}

// partition
int part(std::vector<int>& a, int l, int r) {
    int p = med3(a, l, r);
    int i = l;
    int j = r - 1;
    while (true) {
        while (a[++i] < p);
        while (a[--j] > p);
        if (i < j)
            std::swap(a[i], a[j]);
        else
            break;
    }
    std::swap(a[i], a[r - 1]);
    return i;
}

// main introsort recursive
void intro(std::vector<int>& a, int l, int r, int d) {
    int sz = r - l + 1;
    if (sz <= 16) {
        ins(a, l, r);
        return;
    }
    if (d == 0) {
        heap(a, l, r);
        return;
    }
    int piv = part(a, l, r);
    intro(a, l, piv - 1, d - 1);
    intro(a, piv + 1, r, d - 1);
}

void introSort(std::vector<int> &arr) {
    if (arr.size() <= 1) return;
    int depth = 2 * log2(arr.size());
    intro(arr, 0, arr.size() - 1, depth);
}
