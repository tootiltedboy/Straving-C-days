#include "xml_reader.h"
#include <iostream>
#include <fstream>
#include <pugixml.hpp> // External library: pugixml

void reaxml(const std::string &filePath) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(filePath.c_str());

    if (!result) {
        throw std::runtime_error("Error parsing XML file: " + std::string(result.description()));
    }

    doc.print(std::cout, "  ");
}
