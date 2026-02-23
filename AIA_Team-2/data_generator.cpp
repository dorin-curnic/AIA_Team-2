//
//  data_generator.cpp
//  AIA_Team-2
//
//  Created by Iustin on 14.02.2026.
//

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// Function to generate and save data
void generateAndSave(const std::string &filename, int size,
                     const std::string &type) {
  std::vector<int> data(size);

  // Initialize data
  if (type == "random") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (int i = 0; i < size; ++i) {
      data[i] = dis(gen);
    }
  } else if (type == "asc") {
    for (int i = 0; i < size; ++i) {
      data[i] = i + 1;
    }
  } else if (type == "desc") {
    for (int i = 0; i < size; ++i) {
      data[i] = size - i;
    }
  } else if (type == "half-sorted") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);
    for (int i = 0; i < size / 2; ++i) {
      data[i] = i + 1;
    }
    for (int i = size / 2; i < size; ++i) {
      data[i] = dis(gen);
    }
  } else if (type == "mixed") {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(-1000000, 1000000);
    for (int i = 0; i < size; ++i) {
      data[i] = dis(gen);
    }
  }

  // Write to file
  std::ofstream outFile(filename);
  if (!outFile) {
    std::cerr << "Error creating file: " << filename << std::endl;
    return;
  }

  for (int i = 0; i < size; ++i) {
    outFile << data[i] << (i == size - 1 ? "" : " ");
  }
  outFile << "\n";

  std::cout << "Generated: " << filename << " (" << size << " elements, "
            << type << ")" << std::endl;
}

int main() {
  // Sizes: 100, 1000, 10000, 100000, 1000000
  std::vector<int> sizes = {100, 1000, 10000, 100000, 1000000};

  // Types: random, asc, desc, half-sorted, mixed
  std::vector<std::string> types = {"random", "asc", "desc", "half-sorted", "mixed"};

  std::string outputDir = "data/";
  // Create directory if it doesn't exist (Windows command)
  system("if not exist data mkdir data");

  for (int size : sizes) {
    for (const auto &type : types) {
      std::stringstream ss;
      ss << outputDir << "input_" << size << "_" << type << ".txt";
      generateAndSave(ss.str(), size, type);
    }
  }

  return 0;
}
