//
//  main.cpp
//  AIA_Team-2
//
//  Created by Dorin Curnic on 08.02.2026.
//  Modified by Iustin on 14.02.2026.
//

#include "main.hpp"

#include "insertion_sort.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>

// Usage: .\program_name <algorithm_name> <input_file> [output_file/stdout]
// Example: .\sorter.exe insertion_sort input_100_random.txt output.txt

int main(int argc, const char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0]
              << " <algorithm_name> <input_file> [output_file]" << std::endl;
    return 1;
  }

  std::string algorithmName = argv[1];
  std::string inputFile = argv[2];
  std::string outputFile = (argc >= 4) ? argv[3] : "";

  // Metrics
  long long startTotal = getCurrentTimeMicros();

  // Read Input
  long long startRead = getCurrentTimeMicros();
  std::vector<int> data;
  try {
    data = readInput(inputFile);
  } catch (const std::exception &e) {
    std::cerr << "Error reading file: " << e.what() << std::endl;
    return 1;
  }
  long long endRead = getCurrentTimeMicros();

  // Sort
  long long startSort = getCurrentTimeMicros();
  if (algorithmName == "insertion_sort") {
    insertionSort(data);
  } else {
    std::cerr << "Unknown algorithm: " << algorithmName << std::endl;
    return 1;
  }
  long long endSort = getCurrentTimeMicros();

  // Write Output
  long long startWrite = getCurrentTimeMicros();
  if (outputFile == "stdout") {
    printArray(data);
  } else if (!outputFile.empty()) {
    try {
      writeOutput(outputFile, data);
    } catch (const std::exception &e) {
      std::cerr << "Error writing file: " << e.what() << std::endl;
      return 1;
    }
  }
  long long endWrite = getCurrentTimeMicros();
  long long endTotal = getCurrentTimeMicros();

  // Memory Usage
  size_t peakMemory = getPeakMemoryUsage();

  // Print Results
  std::cout << "Algorithm: " << algorithmName << std::endl;
  std::cout << "Input File: " << inputFile << std::endl;
  std::cout << "Elements: " << data.size() << std::endl;
  std::cout << "------------------------------------------------" << std::endl;
  std::cout << "Read Time: " << (endRead - startRead) << " microseconds"
            << std::endl;
  std::cout << "Sort Time (Computation): " << (endSort - startSort)
            << " microseconds" << std::endl;
  std::cout << "Write Time: " << (endWrite - startWrite) << " microseconds"
            << std::endl;
  std::cout << "Total Execution Time: " << (endTotal - startTotal)
            << " microseconds" << std::endl;
  std::cout << "Peak Memory Usage: " << peakMemory << " bytes" << std::endl;
  std::cout << "------------------------------------------------" << std::endl;

  return 0;
}
