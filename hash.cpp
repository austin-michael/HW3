#include <iostream>
#include "hash.h"

std::string hash(std::string input_text) {
    for (auto i : extract_words("Do hash ")) {
        std::cout << " " << i << " ";
    }
    std::cout << std::endl;
    return "Do hash ";
};

// Extract words (64 bit chunks) from a string for use in hashing algorithm
std::vector<std::uint64_t> extract_words(std::string input) {
    std::vector<std::uint64_t> words;
    std::uint64_t word = 0;
    int shifts = 0;
    for (std::uint8_t c : input) {
        word = (word << 8) | c;
        if (shifts % 8 == 7) {
            words.push_back(word);
            word = 0;
        }
        shifts++;
    }
    // Push back zeros to pad out the end of the last block of the data.
    while (shifts % 8 != 0) {
        std::uint8_t zero = 0;
        word = (word << 8) | zero;
        shifts++;
    }
    words.push_back(word);
    return words;
};
