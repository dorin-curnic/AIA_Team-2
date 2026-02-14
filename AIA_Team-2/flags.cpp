//
//  flags.cpp
//  AIA_Team-2
//
//  Created by Dorin Curnic on 14.02.2026.
//

#include "flags.hpp"
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

static void printHelpHint() {
    cerr << "to get a help use -h or --help flag for more details" << endl;
}

static bool isFlag(const char* s) {
    return s && s[0] == '-';
}

static bool isPositiveIntString(const string& s) {
    if (s.empty()) return false;
    for (char ch : s) {
        if (!isdigit(static_cast<unsigned char>(ch))) return false;
    }
    return true;
}

void printErrorNoArgs() {
    cerr << "main: No option and object" << endl;
    printHelpHint();
}

void printErrorTooManyArgs() {
    cerr << "main: Too many arguments" << endl;
    printHelpHint();
}

void printErrorIllegalOption(const string& badOption) {
    cerr << "main: illegal option: " << badOption << endl;
    printHelpHint();
}

void printErrorMissingValue(const string& flagName) {
    cerr << "main: option requires an object: " << flagName << endl;
    printHelpHint();
}

void printErrorMissingRequired(const string& flagName) {
    cerr << "main: missing required option: " << flagName << endl;
    printHelpHint();
}

void printErrorBadSize(const string& value) {
    cerr << "main: invalid value for --size: " << value << endl;
    printHelpHint();
}

void printErrorHelpMustBeAlone() {
    cerr << "main: -h/--help must be used alone" << endl;
    printHelpHint();
}

void printErrorMutualExclusive(const string& a, const string& b) {
    cerr << "main: options are mutually exclusive: " << a << " and " << b << endl;
    printHelpHint();
}

void printHelp(const char* programName) {
    cout
      << "Usage:\n"
      << "  " << programName << " -h | --help\n"
      << "  " << programName << " -a <alg> -s <N> -i <in.txt> [-o <out.txt> | -c]\n\n"
      << "Options:\n"
      << "  -a, --sortAlgorithm <alg>   Algorithm name (e.g., mergeSort, quickSort, ...)\n"
      << "  -s, --size <N>              Positive integer size (e.g., 100, 100000, ...)\n"
      << "  -i, --inputFile <file>      Input file\n"
      << "  -o, --outputFile <file>     Output file\n"
      << "  -c, --stdout                Print result to stdout\n"
      << "  -h, --help                  Show this help\n\n"
      << "Example:\n"
      << "  " << programName << " -a merge -s 1000 -i in.txt -o out.txt\n";
}

int parseFlags(int argc, const char* argv[], Flags& flags) {
  flags = Flags{};

  if (argc <= 1) {
    printErrorNoArgs();
    return 2;
  }

  if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
    flags.help = true;
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printErrorHelpMustBeAlone();
      return 3;
    }
  }

  if (argc > 9) {
    printErrorTooManyArgs();
    return 4;
  }

  for (int i = 1; i < argc; i++) {
    const char* a = argv[i];

    // flags with value
    if (strcmp(a, "-a") == 0 || strcmp(a, "--sortAlgorithm") == 0) {
      if (i + 1 >= argc || isFlag(argv[i + 1])) {
        printErrorMissingValue("--sortAlgorithm");
        return 5;
      }
      flags.hasSortAlgorithm = true;
      flags.sortAlgorithm = argv[++i];

    } else if (strcmp(a, "-s") == 0 || strcmp(a, "--size") == 0) {
      if (i + 1 >= argc || isFlag(argv[i + 1])) {
        printErrorMissingValue("--size");
        return 5;
      }
      string v = argv[++i];
      if (!isPositiveIntString(v)) {
        printErrorBadSize(v);
        return 6;
      }
      flags.hasSize = true;
      flags.size = stoi(v);
      if (flags.size <= 0) {
        printErrorBadSize(v);
        return 6;
      }

    } else if (strcmp(a, "-i") == 0 || strcmp(a, "--inputFile") == 0) {
      if (i + 1 >= argc || isFlag(argv[i + 1])) {
        printErrorMissingValue("--inputFile");
        return 5;
      }
      flags.hasInputFile = true;
      flags.inputFile = argv[++i];
    
    } else if (strcmp(a, "-o") == 0 || strcmp(a, "--outputFile") == 0) {
      if (i + 1 >= argc || isFlag(argv[i + 1])) {
        printErrorMissingValue("--outputFile");
        return 5;
      }
      flags.hasOutputFile = true;
      flags.outputFile = argv[++i];
    
    // flags without value
    } else if (strcmp(a, "-c") == 0 || strcmp(a, "--stdout") == 0) {
      flags.stdoutMode = true;
    
    // unknown flag
    } else if (isFlag(a)) {
      printErrorIllegalOption(a);
      return 7;
    
    } else {
      printErrorIllegalOption(a);
      return 7;
    }
  }

  // Required flags
  if (!flags.hasSortAlgorithm) {
    printErrorMissingRequired("--sortAlgorithm");
    return 8;
  }

  if (!flags.hasSize) {
    printErrorMissingRequired("--size");
    return 8;
  }

  if (!flags.hasInputFile) {
    printErrorMissingRequired("--inputFile");
    return 8;
  }

  // Output flags rule
  if (flags.stdoutMode && flags.hasOutputFile) {
    printErrorMutualExclusive("--stdout", "--outputFile");
    return 9;
  }

  return 0;
}
