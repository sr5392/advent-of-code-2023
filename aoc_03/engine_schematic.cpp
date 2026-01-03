#include "engine_schematic.hpp"
#include <algorithm>
#include <cstddef>

Engine_Schematic::Engine_Schematic() : size_x{10},
                                       size_y{10},
                                       data{new char[size_x * size_y]} {
}

Engine_Schematic::Engine_Schematic(const Engine_Schematic& other) : size_x{other.size_x},
                                                                    size_y{other.size_y},
                                                                    data{new char[size_x * size_y]()} {
    for (std::size_t y = 0; y < size_y; ++y) {
        for (std::size_t x = 0; x < size_x; ++x) {
            data[y * size_x + x] = other.data[y * size_x + x];
        }
    }
}

Engine_Schematic& Engine_Schematic::operator=(const Engine_Schematic& other) {
    if (this == &other) return *this;
    auto new_data = new char[other.size_x * other.size_y]();
    for (std::size_t y = 0; y < other.size_y; ++y) {
        for (std::size_t x = 0; x < other.size_x; ++x) {
            new_data[y * other.size_x + x] = other.data[y * other.size_x + x];
        }
    }
    delete[] data;
    data = new_data;
    size_x = other.size_x;
    size_y = other.size_y;
    return *this;
}

Engine_Schematic::Engine_Schematic(Engine_Schematic&& other) noexcept : size_x{other.size_x},
                                                                        size_y{other.size_y},
                                                                        data{other.data} {
    other.data = nullptr;
    other.size_x = 0;
    other.size_y = 0;
}

Engine_Schematic& Engine_Schematic::operator=(Engine_Schematic&& other) noexcept {
    if (this == &other) return *this;

    delete[] data;
    data = other.data;
    size_x = other.size_x;
    size_y = other.size_y;

    other.data = nullptr;
    other.size_x = 0;
    other.size_y = 0;

    return *this;
}

Engine_Schematic::~Engine_Schematic() noexcept {
    delete[] data;
}

void Engine_Schematic::resize(std::size_t new_size_x, std::size_t new_size_y) {
    if (new_size_x == 0 || new_size_y == 0) return;
    if (new_size_x == size_x && new_size_y == size_y) return;
    auto new_data = new char[new_size_x * new_size_y]();
    for (std::size_t y = 0; y < std::min(size_y, new_size_y); ++y) {
        for (std::size_t x = 0; x < std::min(size_x, new_size_x); ++x) {
            new_data[y * new_size_x + x] = data[y * size_x + x];
        }
    }
    delete[] data;
    size_x = new_size_x;
    size_y = new_size_y;
    data = new_data;
}

char& Engine_Schematic::at(size_t index_y, size_t index_x) {
    return data[index_y * size_x + index_x];
}
