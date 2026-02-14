//
//  utils.hpp
//  AIA_Team-2
//
//  Created by Iustin on 14.02.2026.
//

#ifndef utils_hpp
#define utils_hpp

#include <chrono>
#include <string>
#include <vector>


// File I/O
std::vector<int> readInput(const std::string &filepath);
void writeOutput(const std::string &filepath, const std::vector<int> &arr);
void printArray(const std::vector<int> &arr);

// Performance Metrics
size_t getPeakMemoryUsage();      // Returns peak working set size in bytes
long long getCurrentTimeMicros(); // Returns current time in microseconds

#endif /* utils_hpp */
