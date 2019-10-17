#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "hash.h"
#include "base64.cpp"

int main(int argc, char* argv[]) {
    std::vector <std::string> args;
    bool debug = false;

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


    unsigned char value[sizeof(a)];
    std::memcpy(value,&a,sizeof(a));
    std::cout << base64_encode(value, sizeof(value)) << std::endl;

    std::memcpy(value,&b,sizeof(b));
    std::cout << base64_encode(value, sizeof(value)) << std::endl;

    std::cout << "bit_diff = " << bit_diff(a, b) << std::endl;

    return 0; // Return 0 if everything works correctly
}