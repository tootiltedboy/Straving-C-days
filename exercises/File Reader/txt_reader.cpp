#include "txt_reader.h"
#include <iostream>
#include <fstream>

void readtxt(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::ios_base::failure("Error opening TXT file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();
}