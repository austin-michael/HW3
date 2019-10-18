#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <cctype>

#include "hash.h"

bool n_digits_0(std::string hash, int n);
bool is_number(const std::string &s);

int main(int argc, char* argv[]) {
    std::vector <std::string> args;
    bool debug = false;
    int num_zeros = 0;

    std::string input_text;   

    // Remember argv[0] is the path to the program, we want from argv[1] onwards
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    // Handle various arguments to the program
    for (int i = 0; i < args.size(); i++) {
        if (args[i] == "-p") {
            input_text = args[i + 1];
        }
        if (args[i] == "-n") {
            if (is_number(args[i+1])) {
                num_zeros = std::stoi(args[i+1]);
            }
        }
        if (args[i] == "-d") {
            debug = true;
        }
    }


    std::cout << "INPUT: " + input_text << std::endl;
    auto a = hash(input_text);
    if (input_text.size() > 0) {
        input_text[0] += 1;
    }
    std::cout << "INPUT: " + input_text << std::endl;
    auto b = hash(input_text);

    std::cout << get_base64_string(a) << std::endl;
    std::cout << get_base64_string(b) << std::endl;

    int differences = 0;
    for (int i = 0; i < a.size(); i++) {
        differences += bit_diff(a[i], b[i]);
    }

    std::cout << "bit_diff = " << differences << std::endl;

    // Just for fun (Find a hash with num_zeros of 0's at the front)
    if (num_zeros) {
        std::string nonce_hash = 0;
        std::string next_input = "";
        std::bitset<256> tmp;

        while (!n_digits_0(nonce_hash, 4)) {
            next_input = random_string();
            auto hash_vec = hash(next_input);
            unsigned char value[hash_vec.size() * sizeof(hash_vec[0])];
            tmp = (std::bitset<256>)get_raw_hash(hash_vec, value);
            nonce_hash = tmp.to_string();
        }

        std::cout << "nonce :" << next_input << std::endl;
        std::cout << "hash :" << nonce_hash << std::endl;
    }

    return 0; // Return 0 if everything works correctly
}

bool n_digits_0(std::string hash, int n) {
    if (hash.size() < n)
        return false;
    for (int i = 0; i < n; i++) {
        if (hash[i] != '0') {
            return false;
        }
    }
    return true;
}

bool is_number(const std::string &s) {
  return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}