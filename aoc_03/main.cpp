#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <algorithm>

#include "engine_schematic.hpp"

void parse_input(Engine_Schematic& es) {
    std::ifstream ifs{"input.txt"};
    if (!ifs.is_open()) {
        throw std::runtime_error{"Unable to open file"};
    }
    size_t index_y = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        auto pos = line.find('\r');
        if (pos != std::string::npos) line.erase(std::remove(line.begin(), line.end(), '\r'), line.cend());
        const auto new_size_x = std::max(es.size_x, line.length());
        const auto new_size_y = std::max(es.size_y, index_y + 1);
        if (new_size_x != es.size_x || new_size_y != es.size_y) es.resize(new_size_x, new_size_y);
        for (size_t size_x = 0; size_x < line.size(); ++size_x) {
            es.at(index_y, size_x) = line[size_x];
        }
        ++index_y;
    }
    es.resize(es.size_x, index_y);
}

int main() {
    Engine_Schematic es;
    parse_input(es);
    std::cout << es.at(0, 2) << std::endl;
    std::cout << es.size_x << std::endl;
    std::cout << es.size_y << std::endl;
    return 0;
}
