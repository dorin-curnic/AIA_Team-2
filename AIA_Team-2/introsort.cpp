#include <cmath>
#include <vector>

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
            int temp = a[l + x];
            a[l + x] = a[l + big];
            a[l + big] = temp;
            x = big;
        }
    }
    
    // extract from heap
    for (int i = n - 1; i > 0; i--) {
        int temp = a[l];
        a[l] = a[l + i];
        a[l + i] = temp;
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
            int temp = a[l + j];
            a[l + j] = a[l + big];
            a[l + big] = temp;
            j = big;
        }
    }
}

// median of 3 pivot
int med3(std::vector<int>& a, int l, int r) {
    int m = l + (r - l) / 2;
    if (a[l] > a[m]) { int t=a[l]; a[l]=a[m]; a[m]=t; }
    if (a[l] > a[r]) { int t=a[l]; a[l]=a[r]; a[r]=t; }
    if (a[m] > a[r]) { int t=a[m]; a[m]=a[r]; a[r]=t; }
    int tm = a[m]; a[m] = a[r - 1]; a[r - 1] = tm;
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
        if (i < j) {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        } else {
            break;
        }
    }
    int tm2 = a[i]; a[i] = a[r - 1]; a[r - 1] = tm2;
    return i;
}

// main introsort recursive
void intro(std::vector<int>& a, int l, int r, int d) {
    int sz = r - l + 1;
    if (sz <= 100) {
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
