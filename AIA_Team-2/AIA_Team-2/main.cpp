//
//  main.cpp
//  AIA_Team-2
//
//  Created by Dorin Curnic on 08.02.2026.
//

#include "flags.hpp"
#include <string>

using namespace std;

int main(int argc, const char* argv[]) {
  Flags flags;
  int flagsReturnCode = parseFlags(argc, argv, flags);

  if (flagsReturnCode == 1) {
    printHelp(argv[0]);
    return 0;
  }

  if (flagsReturnCode != 0) {
    return flagsReturnCode;
  }

  // Get the input file
  // readInputFile(flags.inputFile);

  /*
   * There you can call your sort functions
   */
  switch (flags.size) {
    case 100:
      // insertionSort();
      break;
    case 1000:
      // shellSort();
      break;
    case 10000:
      // introSort();
      break;
    case 100000:
      // mergeSort();
      break;
    case 1000000:
      // radixSort();
      break;
    default:
      printErrorBadSize(to_string(flags.size));
      return 6;
  }

  // Optional Output Method
  if (flags.hasOutputFile) {
    // writeOutputFile(flags.outputFile)
  } else if (flags.stdoutMode) {
    // printStdout();
  }

  return 0;
}

