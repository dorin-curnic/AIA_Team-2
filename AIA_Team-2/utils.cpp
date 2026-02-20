//
//  utils.cpp
//  AIA_Team-2
//
//  Created by Iustin on 14.02.2026.
//

#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <windows.h>
#include <psapi.h> // enabled for memory tracking

std::vector<int> readInput(const std::string &filepath) {
  std::vector<int> arr;
    std::ifstream inFile(filepath);
    if (!inFile) {
        // we try looking in data/ folder
        std::string dataPath = "data/" + filepath;
        inFile.open(dataPath);
        if (!inFile) {
             throw std::runtime_error("Could not open input file: " + filepath + " or " + dataPath);
        }
    }

  int val;
  while (inFile >> val) {
    arr.push_back(val);
  }
  return arr;
}

void writeOutput(const std::string &filepath, const std::vector<int> &arr) {
  std::ofstream outFile(filepath);
  if (!outFile) {
    throw std::runtime_error("Could not open output file: " + filepath);
  }

  for (size_t i = 0; i < arr.size(); ++i) {
    outFile << arr[i] << (i == arr.size() - 1 ? "" : " ");
  }
  outFile << "\n";
}

void printArray(const std::vector<int> &arr) {
  for (size_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

size_t getPeakMemoryUsage() {
  PROCESS_MEMORY_COUNTERS pmc;
  if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
      return pmc.PeakWorkingSetSize;
  }
  return 0;
}

long long getCurrentTimeMicros() {
  auto now = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
      now.time_since_epoch());
  return duration.count();
}
