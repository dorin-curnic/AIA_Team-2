#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include "utils.hpp"
#include "radix.hpp"

using namespace std;

void searchFile(const string& currentDir, const string& targetFileName, string& foundPath) {
    if (!foundPath.empty()) return;

    DIR* dir = opendir(currentDir.c_str());
    if (dir == nullptr) return;

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string name = entry->d_name;
        if (name == "." || name == "..") continue;

        string fullPath = currentDir + "\\" + name;
        
        struct stat info;
        if (stat(fullPath.c_str(), &info) != 0) continue;

        if (info.st_mode & S_IFDIR) {
            searchFile(fullPath, targetFileName, foundPath);
        } else if (name == targetFileName) {
            foundPath = fullPath;
            break;
        }
    }
    closedir(dir);
}

int main(int argc, char* argv[]) {
    // we check parameters
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <input_file> [stdout|output_file]" << endl;
        return 1;
    }

    string targetFileName = argv[1];
    string outputDest = (argc >= 3) ? argv[2] : "";

    long long startTotal = getCurrentTimeMicros();

    // we search for the input file in the current directory and subdirectories
    string inputFilePath = "";
    string startDir = "."; // start from current directory
    searchFile(startDir, targetFileName, inputFilePath);

    if (inputFilePath.empty()) {
        cerr << "Error: Input file '" << targetFileName << "' not found in the project directory." << endl;
        return 1;
    }

    // we read the data
    long long startRead = getCurrentTimeMicros();
    vector<int> data;
    try {
        data = readInput(inputFilePath);
    } catch (const exception& e) {
        cerr << "Error reading file: " << e.what() << endl;
        return 1;
    }
    long long endRead = getCurrentTimeMicros();

    // sort
    long long startSort = getCurrentTimeMicros();
    radixSort(data);
    long long endSort = getCurrentTimeMicros();

    // output
    long long startWrite = getCurrentTimeMicros();
    if (!outputDest.empty()) {
        if (outputDest == "stdout") {
            printArray(data);
        } else {
            try {
                writeOutput(outputDest, data);
            } catch (const exception& e) {
                cerr << "Error writing file: " << e.what() << endl;
                return 1;
            }
        }
    }
    long long endWrite = getCurrentTimeMicros();
    long long endTotal = getCurrentTimeMicros();

    // profiling memory usage
    double memoryUsedMB = (double)getPeakMemoryUsage() / (1024.0 * 1024.0);

    // performance metrics output similar to sorter
    cout << "Algorithm: Radix Sort (Competition)" << endl;
    cout << "Input File: " << inputFilePath << endl;
    cout << "Elements: " << data.size() << endl;
    cout << "------------------------------------------------" << endl;
    cout << "Read Time: " << (endRead - startRead) << " microseconds" << endl;
    cout << "Sort Time (Computation): " << (endSort - startSort) << " microseconds" << endl;
    cout << "Peak Memory Consumption: " << memoryUsedMB << " MB" << endl;
    cout << "Write Time: " << (endWrite - startWrite) << " microseconds" << endl;
    cout << "Total Execution Time: " << (endTotal - startTotal) << " microseconds" << endl;
    cout << "------------------------------------------------" << endl;
    
    // additional requested metrics
    cout << "1. Computation time = sorting time only: " << (endSort - startSort) << " microseconds" << endl;
    cout << "2. Computation time = sorting time + file output time: " << ((endSort - startSort) + (endWrite - startWrite)) << " microseconds" << endl;
    cout << "------------------------------------------------" << endl;

    return 0;
}