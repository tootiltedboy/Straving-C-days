#include <iostream>
#include <string>
#include <filesystem>
#include "txt_reader.h"
#include "csv_reader.h"
#include "json_reader.h"
#include "xml_reader.h"

void handleFile(const std::string &filePath) {
    if (!std::filesystem::exists(filePath)) {
        throw std::invalid_argument("Error: File does not exist.");
    }

    std::string extension = std::filesystem::path(filePath).extension().string();
    if (extension == ".txt") {
        readtxt(filePath);
    } else if (extension == ".csv") {
        readcsv(filePath);
    } else if (extension == ".json") {
        readjson(filePath);
    } else if (extension == ".xml") {
        readxml(filePath);
    } else {
        throw std::invalid_argument("Error: Unsupported file format.");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    try {
        handleFile(filePath);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}