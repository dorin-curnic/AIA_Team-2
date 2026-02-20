//
//  shell_sort.cpp
//  AIA_Team-2
//
//  Created by Bivol Liviu on 17.02.2026.
//

#include <vector>

void shellSort(std::vector<int> &arr) {
  int n = arr.size();
  if (n <= 1) return;

  // Generate Ciura gap sequence dynamically up to n
  std::vector<int> gaps = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
  int next_gap = 1750;
  while (next_gap < n) {
      next_gap = (int)(next_gap * 2.25);
      gaps.push_back(next_gap);
  }

  // Iterate backwards through the gap sequence
  for (int k = gaps.size() - 1; k >= 0; --k) {
      int gap = gaps[k];
      if (gap >= n && gap != 1) continue; // Skip gaps larger than array size

      for (int i = gap; i < n; i += 1) {
          int temp = arr[i];
          int j;
          for(j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
              arr[j] = arr[j - gap];
          }
          arr[j] = temp;
      }
  }
}