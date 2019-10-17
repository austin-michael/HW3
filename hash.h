#include <string>
#include <bitset>
#include <vector>
#include <cstdint> // include this header for uint64_t

uint64_t hash(std::string);
std::vector<std::uint64_t> operation(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
std::vector<std::uint64_t> extract_words(std::string);
std::uint64_t f(uint64_t A, uint64_t B, uint64_t C);
std::uint64_t f_2(uint64_t A, uint64_t B, uint64_t K);
int bit_diff(uint64_t, uint64_t);
std::uint64_t rand_f(uint64_t A, uint64_t B, uint64_t C);