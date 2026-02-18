//
//  flags.hpp
//  AIA_Team-2
//
//  Created by Dorin Curnic on 14.02.2026.
//

#ifndef flags_hpp
#define flags_hpp

#include <string>

struct Flags {
  bool help = false;

  bool hasSortAlgorithm = false;
  std::string sortAlgorithm;

  bool hasSize = false;
  int size = 0;

  bool hasInputFile = false;
  std::string inputFile;

  bool hasOutputFile = false;
  std::string outputFile;

  bool stdoutMode = false;
};

int parseFlags(int argc, const char* argv[], Flags& flags);

void printHelp(const char* programName);

void printErrorNoArgs();
void printErrorTooManyArgs();
void printErrorIllegalOption(const std::string& badOption);
void printErrorMissingValue(const std::string& flagName);
void printErrorMissingRequired(const std::string& flagName);
void printErrorBadSize(const std::string& value);
void printErrorHelpMustBeAlone();
void printErrorMutualExclusive(const std::string& a, const std::string& b);

#endif /* flags_hpp */
