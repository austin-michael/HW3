#include <iostream>
#include <bitset>
#include "hash.h"

uint64_t hash(std::string input_text) {
    // Initial values
    uint64_t A = 539958729876229229;
    uint64_t B = 881213617895827187;
    uint64_t C = 1619298787036835669;
    uint64_t D = 4571622384984713413;
    auto block_vec = extract_words(input_text);

    std::vector<uint64_t> blocks;

    if (block_vec.size() % 4 != 0) {
        for (int i = 0; i < (block_vec.size() % 4); i++) {
            block_vec.push_back((uint64_t) block_vec.size());
        }
    }

    for (int i = 0; i < 80 + block_vec.size(); i++) {
        auto iter = i % block_vec.size();
        blocks = operation(A, B, C, D, block_vec[iter]);

        A = blocks[0];
        B = blocks[1];
        C = blocks[2];
        D = blocks[3];
    }

    for (auto i : blocks) {
        std::cout << " " << i << " ";
    }
    std::cout << std::endl;
    return blocks[0];
};

std::vector<std::uint64_t> operation(uint64_t A, uint64_t B, uint64_t C, uint64_t D, uint64_t M_i) {
    std::vector<std::uint64_t> return_vec;

    uint64_t K = ((2926415965689092963) + ((A & ~B) ^ (C & D))) + ~A;

    A = A + M_i;

    C = C + D;

    B = f(A, B, C);

    A = rand_f(A, B, C);
    A = (A >> (64 - 23)) | (A << 23); // Barrel shift right 23 bits.
    uint64_t new_D = C;

    B = f_2(A, B, ((K ^ ~A) + A));

    D = D + B;

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
    // If we don't have anything (null string) push back a 0
    if (words.size() < 1) {
        words.push_back(0);
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
    return (A & B) ^ (A & C) ^ (B & C);
};

std::uint64_t f_2(uint64_t A, uint64_t B, uint64_t K) {
    return (A & B) ^ (~B & K);
};

std::uint64_t rand_f(uint64_t A, uint64_t B, uint64_t C) {
    switch (((A ^ ~B) & (C ^ B)) % 4) {
        case 0:
            return (A & B) ^ (~A & C);
        case 1:
            return (A & B) ^ (A & C) ^ (B & C);
        case 2:
            return (A >> 2) ^ (A >> 13) ^ (A >> 22);
        case 3:
            return (C >> 6) ^ (C >> 11) ^ (C >> 25);
    }
}

int bit_diff(uint64_t A, uint64_t B) {
    std::bitset<64> different = (A ^ B);

    return different.count();
};
