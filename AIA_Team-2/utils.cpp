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
#if defined(_WIN32)
#include <windows.h>
#include <psapi.h>
#elif defined(__APPLE__)
#include <mach/mach.h>
#elif defined(__linux__)
#include <sys/resource.h>
#include <unistd.h>
#endif

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
#if defined(_WIN32)
  PROCESS_MEMORY_COUNTERS pmc;
  if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
      return pmc.PeakWorkingSetSize;
  }
#elif defined(__APPLE__)
  struct mach_task_basic_info info;
  mach_msg_type_number_t infoCount = MACH_TASK_BASIC_INFO_COUNT;
  if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO, (task_info_t)&info, &infoCount) == KERN_SUCCESS) {
      return (size_t)info.resident_size_max;
  }
#elif defined(__linux__)
  struct rusage r_usage;
  getrusage(RUSAGE_SELF, &r_usage);
  // ru_maxrss is in kilobytes on Linux
  return (size_t)(r_usage.ru_maxrss * 1024L);
#endif
  return 0;
}

long long getCurrentTimeMicros() {
  auto now = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
      now.time_since_epoch());
  return duration.count();
}
