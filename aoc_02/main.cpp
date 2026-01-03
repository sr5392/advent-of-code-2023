#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <string>

struct Game {
    std::size_t m_id;
    std::size_t m_max_red_cube;
    std::size_t m_max_green_cube;
    std::size_t m_max_blue_cube;

    Game() : m_id{0},
             m_max_red_cube{0},
             m_max_green_cube{0},
             m_max_blue_cube{0} {
    }

    explicit Game(const unsigned long id) : m_id{id},
                                            m_max_red_cube{0},
                                            m_max_green_cube{0},
                                            m_max_blue_cube{0} {
    }

    void print() const {
        std::cout << *this << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const Game& game);
};

std::ostream& operator<<(std::ostream& os, const Game& game) {
    return os << "Game - ID: " << game.m_id
           << ", Red: " << game.m_max_red_cube
           << ", Green: " << game.m_max_green_cube
           << ", Blue: " << game.m_max_blue_cube;
}

void parse_line(const std::string& line, Game& game) {
    auto curr = line.cbegin();
    const auto end = line.cend();

    if (line.compare(0, 4, "Game") != 0) {
        throw std::runtime_error("Invalid file format");
    }
    curr += 4;

    if (curr != end && !std::isspace(*curr)) {
        throw std::runtime_error("Invalid file format");
    }
    ++curr;

    std::size_t id = 0;
    while (curr != end && std::isdigit(*curr)) {
        id = id * 10 + (*curr - '0');
        ++curr;
    }
    game.m_id = id;

    if (curr != end && *curr != ':') {
        throw std::runtime_error("Invalid file format");
    }
    ++curr;

    while (curr != end) {
        while (curr != end && std::isspace(*curr)) {
            ++curr;
        }

        if (curr != end && !isdigit(*curr)) {
            throw std::runtime_error("Invalid file format");
        }
        size_t cube_count = 0;
        while (curr != end && std::isdigit(*curr)) {
            cube_count = cube_count * 10 + (*curr - '0');
            ++curr;
        }

        if (curr != end && !isspace(*curr)) {
            throw std::runtime_error("Invalid file format");
        }
        ++curr;

        if (curr != end && !isalpha(*curr)) {
            throw std::runtime_error("Invalid file format");
        }
        auto color_start = curr;
        while (curr != end && isalpha(*curr)) {
            ++curr;
        }
        std::string color{color_start, curr};
        if (color == "red") {
            if (cube_count > game.m_max_red_cube) game.m_max_red_cube = cube_count;
        } else if (color == "green") {
            if (cube_count > game.m_max_green_cube) game.m_max_green_cube = cube_count;
        } else if (color == "blue") {
            if (cube_count > game.m_max_blue_cube) game.m_max_blue_cube = cube_count;
        } else {
            throw std::runtime_error("Invalid file format");
        }

        if (curr != end && *curr != ';' && *curr != ',' && *curr != '\r') {
            throw std::runtime_error("Invalid file format");
        }
        if (curr != end) ++curr;
    }
}

std::istream& operator>>(std::istream& is, Game& game) {
    game = Game{};
    std::string line;
    if (!std::getline(is, line)) return is;
    parse_line(line, game);
    return is;
}

void parse_input(std::vector<Game>& games) {
    std::ifstream ifs{"input_test.txt"};
    if (!ifs.is_open()) {
        std::cerr << "Unable to open file";
        return;
    }
    Game game;
    while (ifs >> game) {
        games.push_back(game);
    }
}

unsigned long part_1() {
    std::vector<Game> games;
    parse_input(games);

    constexpr size_t max_red_cube = 12;
    constexpr size_t max_green_cube = 13;
    constexpr size_t max_blue_cube = 14;

    unsigned long sum_valid_ids = 0;
    for (const auto& game: games) {
        if (game.m_max_red_cube > max_red_cube) continue;
        if (game.m_max_green_cube > max_green_cube) continue;
        if (game.m_max_blue_cube > max_blue_cube) continue;
        sum_valid_ids += game.m_id;
    }
    return sum_valid_ids;
}

int main() {
    std::cout << part_1() << std::endl;
    return 0;
}
