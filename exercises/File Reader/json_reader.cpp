#include "json_reader.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp> // External library: JSON for Modern C++

void readjson(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file) {
        throw std::ios_base::failure("Error opening JSON file.");
    }

    try {
        nlohmann::json jsonData;
        file >> jsonData;
        std::cout << jsonData.dump(4) << std::endl; // Pretty-print with 4-space indent
    } catch (const std::exception &e) {
        throw std::runtime_error("Error parsing JSON file: " + std::string(e.what()));
    }
    file.close();
}