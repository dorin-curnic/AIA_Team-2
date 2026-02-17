//
//  shell_sort.cpp
//  AIA_Team-2
//
//  Created by Bivol Liviu on 17.02.2026.
//

void shellSort(std::vector<int> &arr) {
  int n = arr.size();

  for (int gap = n / 2; gap > 0; gap /= 2) {

    for (int i = gap; i < n; i += 1) {
      int temp = arr[i];
      int j;
      
      for(j=i; j >= gap && arr[j - gap] > temp; j-=gap)
        arr[j] = arr[j - gap];

      arr[j] = temp;
    }
  }
}