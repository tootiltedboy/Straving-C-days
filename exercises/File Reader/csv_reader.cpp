#include "csv_reader.h"
#include <iostream>
#include <fstream>
#include <sstream>

void readcsv(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::ios_base::failure("Error opening CSV file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string cell;
        while (std::getline(lineStream, cell, ',')) {
            std::cout << cell << " ";
        }
        std::cout << std::endl;
    }
    file.close();
}