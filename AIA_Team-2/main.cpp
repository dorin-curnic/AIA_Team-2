//
//  main.cpp
//  AIA_Team-2
//
//  Created by Dorin Curnic on 08.02.2026.
//

#include "flags.hpp"
#include "utils.hpp"
#include "insertion_sort.hpp"
#include "shell_sort.hpp"
#include "introsort.hpp"
#include "merge_sort.hpp"
#include "radix.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <psapi.h>

using namespace std;

int main(int argc, const char* argv[]) {
  Flags flags;
  int flagsReturnCode = parseFlags(argc, argv, flags);

  if (flagsReturnCode == 1) {
    // Extract base filename from argv[0] for cleaner help output
    std::string programName = argv[0];
    size_t lastSlash = programName.find_last_of("/\\");
    if (lastSlash != std::string::npos) {
      programName = programName.substr(lastSlash + 1);
    }
    printHelp(programName.c_str());
    return 0;
  }

  if (flagsReturnCode != 0) {
    return flagsReturnCode;
  }

  // track overall time
  long long startTotal = getCurrentTimeMicros();

  // read input
  long long startRead = getCurrentTimeMicros();
  std::vector<int> data;
  try {
    data = readInput(flags.inputFile);
  } catch (const std::exception &e) {
    std::cerr << "Error reading file: " << e.what() << std::endl;
    return 1;
  }
  long long endRead = getCurrentTimeMicros();

  // we validate size read matches flag if required (optional)
  if (data.size() != static_cast<size_t>(flags.size)) {
    std::cerr << "Warning: Read " << data.size() << " elements, but flag specified " << flags.size << std::endl;
  }

  // sort
  long long startSort = getCurrentTimeMicros();
  if (flags.sortAlgorithm == "insertion" || flags.sortAlgorithm == "insertion_sort" || flags.sortAlgorithm == "insertionSort") {
    insertionSort(data);
  } else if (flags.sortAlgorithm == "shell" || flags.sortAlgorithm == "shellSort") {
    shellSort(data);
  } else if (flags.sortAlgorithm == "intro" || flags.sortAlgorithm == "introSort") {
    introSort(data);
  } else if (flags.sortAlgorithm == "merge" || flags.sortAlgorithm == "mergeSort") {
    mergeSort(data);
  } else if (flags.sortAlgorithm == "radix" || flags.sortAlgorithm == "radixSort") {
    radixSort(data);
  } else {
    std::cerr << "Unknown algorithm: " << flags.sortAlgorithm << std::endl;
    return 1;
  }
  long long endSort = getCurrentTimeMicros();

  // we write output
  long long startWrite = getCurrentTimeMicros();
  if (flags.hasOutputFile) {
    try {
      writeOutput(flags.outputFile, data);
    } catch (const std::exception &e) {
      std::cerr << "Error writing file: " << e.what() << std::endl;
      return 1;
    }
  } else if (flags.stdoutMode) {
    printArray(data);
  }
  long long endWrite = getCurrentTimeMicros();
  long long endTotal = getCurrentTimeMicros();

  // Profiling Memory usage
  PROCESS_MEMORY_COUNTERS pmc;
  double memoryUsedMB = 0;
  if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
      memoryUsedMB = (double)pmc.PeakWorkingSetSize / (1024.0 * 1024.0);
  }

  // print metrics (Standard Empirical Output)
  std::cout << "Algorithm: " << flags.sortAlgorithm << std::endl;
  std::cout << "Input File: " << flags.inputFile << std::endl;
  std::cout << "Elements: " << data.size() << std::endl;
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "Read Time: " << (endRead - startRead) << " microseconds" << std::endl;
  std::cout << "Sort Time (Computation): " << (endSort - startSort) << " microseconds" << std::endl;
  std::cout << "Peak Memory Consumption: " << memoryUsedMB << " MB" << std::endl;
  std::cout << "Write Time: " << (endWrite - startWrite) << " microseconds" << std::endl;
  std::cout << "Total Execution Time: " << (endTotal - startTotal) << " microseconds" << std::endl;
  std::cout << "------------------------------------------------" << std::endl;

  return 0;
}

