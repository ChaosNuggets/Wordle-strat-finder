#ifndef SCORE_H
#define SCORE_H

#include <unordered_map>
#include <vector>
#include <string>

const extern std::unordered_map<char, std::vector<int>> matchingProbability;
int score(const std::string word);

#endif