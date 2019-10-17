#include <iostream>
#include "hash.h"

std::string hash(std::string input_text) {
    auto block_vec = extract_words(input_text);

    if (block_vec.size() % 4 != 0) {
        for (int i = 0; i < (block_vec.size() % 4); i++) {
            block_vec.push_back((uint64_t) block_vec.size());
        }
    }

    for (auto i : block_vec) {
        std::cout << i << std::endl;
    }

    // uint64_t A = 0;
    // uint64_t B = 0;
    // uint64_t C = 0;
    // uint64_t D = 0;

    uint64_t A = 539958729876229229;
    uint64_t B = 881213617895827187;
    uint64_t C = 1619298787036835669;
    uint64_t D = 4571622384984713413;

    std::vector<uint64_t> blocks;

    for (int i = 0; i < 32; i+=4) {
        auto iter = i % block_vec.size();
        blocks = operation(A, B, C, D, block_vec[i]);
        // for (auto i : blocks) {
        //     std::cout << " " << i << " ";
        // }
        A = blocks[iter];
        B = blocks[iter + 1];
        C = blocks[iter + 2];
        D = blocks[iter + 3];
        // std::cout << std::endl;
    }

    for (auto i : blocks) {
        std::cout << " " << i << " ";
    }
    return "";
};

std::vector<std::uint64_t> operation(uint64_t A, uint64_t B, uint64_t C, uint64_t D, uint64_t M_i) {
    std::vector<std::uint64_t> return_vec;

    //uint64_t K = 2926415965689092963;
    uint64_t K = 7;

    A = A ^ M_i;

    C = C ^ D;

    B = f(A, B, C);

    A = (A >> (64 - 23)) | (A << 23); // Barrel shift right 23 bits.
    uint64_t new_D = C;

    B = f_2(A, B, ((K & ~A) ^ A));

    D = D ^ B;

    uint64_t new_A = D;
    uint64_t new_B = A;
    uint64_t new_C = B;

    return_vec.push_back(new_A);
    return_vec.push_back(new_B);
    return_vec.push_back(new_C);
    return_vec.push_back(new_D);

    return return_vec;
};

// Extract words (64 bit chunks) from a string for use in hashing algorithm
std::vector<std::uint64_t> extract_words(std::string input) {
    std::vector<std::uint64_t> words;
    std::uint64_t word = 0;
    int shifts = 0;
    for (std::uint8_t c : input) {
        word = (word << 8) | c; // Bit shift left existing characters by 8 (shift one character) and bitwise or (|) with the next character.
        if (shifts % 8 == 7) {
            words.push_back(word);
            word = 0;
        }
        shifts++;
    }
    // Push back zeros to pad out the end of the last block of the data.
    if (shifts % 8 != 0) {
        while (shifts % 8 != 0) {
            std::uint8_t zero = 0;
            word = (word << 8) | zero;
            shifts++;
        }
        words.push_back(word);
    }
    return words;
};

std::uint64_t f(uint64_t A, uint64_t B, uint64_t C) {
    return (~A | C) ^ (B & C);
};

std::uint64_t f_2(uint64_t A, uint64_t B, uint64_t K) {
    return (A & B) ^ (~B & K);
};