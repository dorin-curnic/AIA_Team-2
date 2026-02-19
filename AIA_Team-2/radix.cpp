#include "radix.hpp"
#include <vector>
#include <cstdint>
#include <algorithm> 

void radixSort(std::vector<int>& arr) {
    if (arr.empty()) return;

    const int BASE = 256; 
    const int BYTE_SIZE = 4; 

    std::vector<int> output(arr.size());
    
    // Separate positive and negative numbers
    std::vector<int> positives;
    std::vector<int> negatives;

    for (int x : arr) {
        if (x >= 0)
            positives.push_back(x);
        else
            negatives.push_back(-x); // make negative numbers positive temporarily
    }

    auto lsd_radix = [&](std::vector<int>& nums) {
        std::vector<int> buffer(nums.size());
        for (int byte = 0; byte < BYTE_SIZE; ++byte) {
            int count[BASE] = {0};

            // Count occurrences
            for (int x : nums) {
                int b = (x >> (8 * byte)) & 0xFF;
                count[b]++;
            }

            // Accumulate counts
            for (int i = 1; i < BASE; ++i) {
                count[i] += count[i - 1];
            }

            // Build output array (stable sort)
            for (int i = nums.size() - 1; i >= 0; --i) {
                int b = (nums[i] >> (8 * byte)) & 0xFF;
                buffer[--count[b]] = nums[i];
            }

            nums.swap(buffer);
        }
    };

    // Sort positives
    lsd_radix(positives);
    // Sort negatives
    lsd_radix(negatives);
    std::reverse(negatives.begin(), negatives.end());

    // Merge back: negatives first (as negative), then positives
    int idx = 0;
    for (int x : negatives) arr[idx++] = -x;
    for (int x : positives) arr[idx++] = x;
}
