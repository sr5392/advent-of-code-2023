#ifndef AOC_03_ENGINE_SCHEMATIC_HPP
#define AOC_03_ENGINE_SCHEMATIC_HPP

#include <cstddef>

struct Engine_Schematic {
    std::size_t size_x;
    std::size_t size_y;
private:
    char* data;
public:
    Engine_Schematic();
    Engine_Schematic(const Engine_Schematic& other);
    Engine_Schematic(Engine_Schematic&& other) noexcept;
    ~Engine_Schematic() noexcept;
    Engine_Schematic& operator=(const Engine_Schematic& other);
    Engine_Schematic& operator=(Engine_Schematic&& other) noexcept;

    void resize(std::size_t new_size_x, std::size_t new_size_y);
    char& at(size_t index_y, size_t index_x);
};
#endif //AOC_03_ENGINE_SCHEMATIC_HPP