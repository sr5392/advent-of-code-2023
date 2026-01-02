#include <iostream>
#include <fstream>
#include <unordered_map>

int part_1() {
    int number = 0;
    std::ifstream fs{"input.txt"};
    if (!fs.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 0;
    }
    std::string line;
    while (std::getline(fs, line)) {
        char first = '\0';
        char last = '\0';
        for (const auto& c: line) {
            if (isdigit(c)) {
                if (first == '\0') first = c;
                last = c;
            }
        }
        if (!(first && last)) {
            std::cerr << "Invalid file format" << std::endl;
            return 0;
        }
        number += (first - '0') * 10 + (last - '0');
    }
    return number;
}

int part_2() {
    int number = 0;
    const std::unordered_map<std::string, char> map_word_digit = {
        {"one", '1'},
        {"two", '2'},
        {"three", '3'},
        {"four", '4'},
        {"five", '5'},
        {"six", '6'},
        {"seven", '7'},
        {"eight", '8'},
        {"nine", '9'}
    };
    std::string line;
    std::ifstream fs{"input.txt"};
    if (!fs.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 0;
    }
    while (std::getline(fs, line)) {
        char first = '\0';
        char last = '\0';
        for (std::size_t i = 0; i < line.size(); ++i) {
            const char& c = line[i];
            if (isdigit(c)) {
                if (first == '\0') first = c;
                last = c;
                continue;
            }
            for (const auto& [word, digit]: map_word_digit) {
                if (i + word.size() > line.size()) continue;
                if (line.compare(i, word.size(), word) == 0) {
                    if (first == '\0') first = digit;
                    last = digit;
                    i += word.size() - 2;
                    break;
                }
            }
        }
        if (!(first && last)) {
            std::cerr << "Invalid file format" << std::endl;
            return 0;
        }
        number += (first - '0') * 10 + (last - '0');
    }
    return number;
}

int main() {
    std::cout << part_1() << std::endl;
    std::cout << part_2() << std::endl;
    return 0;
}
