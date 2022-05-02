#include "score.h"
#include <iostream>

//matching probability*100
static const std::unordered_map<char, std::vector<int>> matchingProbability = {
    {'a', {109, 234, 237, 126,  49}},
    {'b', {133,  12,  44,  18,   8}},
    {'c', {153,  31,  43, 117,  24}},
    {'d', { 86,  15,  58,  53,  91}},
    {'e', { 55, 187, 136, 245, 327}},
    {'f', {105,   6,  19,  27,  20}},
    {'g', { 89,   9,  52,  59,  32}},
    {'h', { 53, 111,   7,  22, 107}},
    {'i', { 26, 156, 205, 122,   8}},
    {'j', { 15,   2,   2,   2,   0}},
    {'k', { 15,   8,   9,  42,  87}},
    {'l', { 68, 155,  86, 125, 120}},
    {'m', { 82,  29,  47,  52,  32}},
    {'n', { 29,  67, 107, 140, 100}},
    {'o', { 32, 215, 188, 102,  45}},
    {'p', {109,  47,  45,  39,  43}},
    {'q', { 18,   4,   1,   0,   0}},
    {'r', { 81, 206, 126, 117, 163}},
    {'s', {282,  12,  62, 132,  28}},
    {'t', {115,  59,  86, 107, 195}},
    {'u', { 25, 143, 127,  63,   1}},
    {'v', { 33,  12,  38,  35,   0}},
    {'w', { 64,  34,  20,  19,  13}},
    {'x', {  0,  11,   9,   2,   6}},
    {'y', {  5,  18,  22,   2, 281}},
    {'z', {  2,   2,   8,  15,   3}}
};

int score(const std::string word) {
    int currentScore = 0;
    for (int i = 0; i < 5; i++) {
        currentScore += matchingProbability.at(word[i])[i];
    }
    return currentScore;
}

// int main() {
//     const std::vector<std::string> wordsToScore = {"camps", "nudge", "forby", "thilk"};
//     int totalScore = 0;
//     for (std::string word : wordsToScore) {
//         totalScore += score(word);
//     }
//     std::cout << totalScore;
//     std::cin.ignore();
// }