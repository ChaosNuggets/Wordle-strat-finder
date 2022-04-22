#include <iostream>
#include "dynamic_words.h"
// #include <vector>
// #include <string>
#include <algorithm>
#include <unordered_map>
#include "skip_helper.h"
#include "test_words.h"
#include <chrono>
#include <fstream>

// std::vector<std::vector<std::vector<std::string>>> dynamicWords = {
//     {{}},
//     {{}},
//     {{}},
//     {{}},
//     {{}},

//     {{}},
//     {{}},
//     {{},{},{},{},{},{},{},{"shuck"}},
//     {{}},
//     {{}},

//     {{}},
//     {{}},
//     {{}},
//     {{}},
//     {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{"podgy"}},

//     {{}},
//     {{}},
//     {{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{"brame"}},
//     {{},{},{},{},{},{},{},{},{},{},{},{"flint"}}
// };

typedef std::chrono::high_resolution_clock Clock;

bool removeUsedLetters(std::vector<char>& unusedLetters, const std::string word) {
    for (char letter : word) {
        auto it = std::find(unusedLetters.begin(), unusedLetters.end(), letter);
        //If letter is in the list
        if (it != unusedLetters.end()) {
            unusedLetters.erase(it);
        } else
            return false;
    }
    return true;
}

bool testUsedLetters(const std::vector<char>& unusedLetters, const std::string word) {
    for (char letter : word) {                        
        //If letter is in the list
        if (std::find(unusedLetters.begin(), unusedLetters.end(), letter) == unusedLetters.end())
            return false;
    }
    return true;
}

//matching probability*100
const std::unordered_map<char, std::vector<int>> matchingProbability = {
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

std::vector<std::string> bestWords;

// void saveWords(const std::vector<std::string> strings) {
//     bestWords.push_back(strings);
// }

int main() {
    const std::vector<char> usingLetters = {
        'e', 'a', 'r', 'o', 't',
        'l', 'i', 's', 'n', 'u',
        'c', 'y', 'h', 'd', 'p',
        'g', 'm', 'b', 'f', 'k',
        // 'w', 'v', 'x', 'z', 'q',
        // 'j'
    };

    auto startRemoving = Clock::now();
    std::cout << "removing unnecessary words ";
    for (int h = 0; h < dynamicWords.size(); h++) {
        for (int i = 0; i < dynamicWords[h].size(); i++) {
            std::vector<std::string> currentWords = dynamicWords[h][i];
            for (int j = 0; j < currentWords.size(); j++) {
                for (int k = 0; k < currentWords[j].size(); k++) {
                    //Remove if one of the letters isn't in the usingLetters list
                    if (std::find(usingLetters.begin(), usingLetters.end(), currentWords[j][k]) == usingLetters.end()) {
                        currentWords.erase(currentWords.begin() + j);
                        j--;
                        break;
                    }
                    //Remove if it has repeated letters
                    bool shouldBreak = false;
                    for (int l = k+1; l < currentWords[j].size(); l++) {
                        if (currentWords[j][k] == currentWords[j][l]) {
                            currentWords.erase(currentWords.begin() + j);
                            j--;
                            shouldBreak = true;
                            break;
                        }
                    }
                    if (shouldBreak)
                        break;
                }
            }
            dynamicWords[h][i] = currentWords;
        }
    }
    auto startTesting = Clock::now();
    std::cout << '(' << std::chrono::duration_cast<std::chrono::milliseconds>(startTesting - startRemoving).count() << "ms)\n";

    std::cout << "testing permutations ";
    int lowestFails = 12947;
    const int scoreToBeat = 2900; //score to beat or equal
    int possiblePermutations = 0;
    std::vector<char> skipChars;
    skipChars.resize(17);
    for (int aFirst = 0; aFirst < dynamicWords.size()-2; aFirst++) {
        //I hate this but it works since this is how the words vector is already sorted
        skipChars[0] = firstDimensionOrder[aFirst];
        for (int aSecond = 0; aSecond < dynamicWords[aFirst].size(); aSecond++) {
            skipChars[1] = alphaPlaceToChar(aSecond);
            for (int ina = 0; ina < dynamicWords[aFirst][aSecond].size(); ina++) {
                // std::cout << "A: " << dynamicWords[aFirst][aSecond][ina] << '\n';
                std::vector<char> unusedLettersA = usingLetters;
                if (!removeUsedLetters(unusedLettersA, dynamicWords[aFirst][aSecond][ina])) //If the word has a letter that's not in unusedLetters
                    continue;
                skipChars[2] = dynamicWords[aFirst][aSecond][ina][2];
                skipChars[3] = dynamicWords[aFirst][aSecond][ina][3];
                skipChars[4] = dynamicWords[aFirst][aSecond][ina][4];
                int scoreA = score(dynamicWords[aFirst][aSecond][ina]);
                for (int bFirst = aFirst+1; bFirst < dynamicWords.size()-1; bFirst++) {
                    //I hate this but it works since this is how the words vector is already sorted
                    if (std::find(skipChars.begin(), skipChars.begin() + 5, firstDimensionOrder[bFirst]) != skipChars.begin() + 5)
                        continue;
                    skipChars[5] = firstDimensionOrder[bFirst];
                    for (int bSecond = 0; bSecond < dynamicWords[bFirst].size(); bSecond++) {
                        if (std::find(skipChars.begin(), skipChars.begin() + 6, alphaPlaceToChar(bSecond)) != skipChars.begin() + 6)
                            continue;
                        skipChars[6] = alphaPlaceToChar(bSecond);
                        for (int inb = 0; inb < dynamicWords[bFirst][bSecond].size(); inb++) {
                            // std::cout << "B: " << dynamicWords[bFirst][bSecond][inb] << '\n';
                            std::vector<char> unusedLettersB = unusedLettersA;
                            if (!removeUsedLetters(unusedLettersB, dynamicWords[bFirst][bSecond][inb]))
                                continue;
                            skipChars[7] = dynamicWords[bFirst][bSecond][inb][2];
                            skipChars[8] = dynamicWords[bFirst][bSecond][inb][3];
                            skipChars[9] = dynamicWords[bFirst][bSecond][inb][4];
                            int scoreB = scoreA + score(dynamicWords[bFirst][bSecond][inb]);
                            for (int cFirst = bFirst+1; cFirst < dynamicWords.size(); cFirst++) {
                                if (std::find(skipChars.begin(), skipChars.begin() + 10, firstDimensionOrder[cFirst]) != skipChars.begin() + 10)
                                    continue;
                                skipChars[10] = firstDimensionOrder[cFirst];
                                for (int cSecond = 0; cSecond < dynamicWords[cFirst].size(); cSecond++) {
                                    if (std::find(skipChars.begin(), skipChars.begin() + 11, alphaPlaceToChar(cSecond)) != skipChars.begin() + 11)
                                        continue;
                                    skipChars[11] = alphaPlaceToChar(cSecond);
                                    for (int inc = 0; inc < dynamicWords[cFirst][cSecond].size(); inc++) {
                                        // std::cout << "C: " << dynamicWords[cFirst][cSecond][inc] << '\n';
                                        std::vector<char> unusedLettersC = unusedLettersB;
                                        if (!removeUsedLetters(unusedLettersC, dynamicWords[cFirst][cSecond][inc]))
                                            continue;
                                        skipChars[12] = dynamicWords[cFirst][cSecond][inc][2];
                                        skipChars[13] = dynamicWords[cFirst][cSecond][inc][3];
                                        skipChars[14] = dynamicWords[cFirst][cSecond][inc][4];
                                        int scoreC = scoreB + score(dynamicWords[cFirst][cSecond][inc]);
                                        for (int dFirst = cFirst+1; dFirst < dynamicWords.size(); dFirst++) {
                                            if (std::find(skipChars.begin(), skipChars.begin() + 15, firstDimensionOrder[dFirst]) != skipChars.begin() + 15)
                                                continue;
                                            skipChars[15] = firstDimensionOrder[dFirst];
                                            for (int dSecond = 0; dSecond < dynamicWords[dFirst].size(); dSecond++) {
                                                if (std::find(skipChars.begin(), skipChars.begin() + 16, alphaPlaceToChar(dSecond)) != skipChars.begin() + 16)
                                                    continue;
                                                skipChars[16] = alphaPlaceToChar(dSecond);
                                                for (int ind = 0; ind < dynamicWords[dFirst][dSecond].size(); ind++) {
                                                    // std::cout << "D: " << dynamicWords[dFirst][dSecond][ind] << '\n';
                                                    std::vector<char> unusedLettersD = unusedLettersC;
                                                    if (!testUsedLetters(unusedLettersD, dynamicWords[dFirst][dSecond][ind]))
                                                        continue;
                                                    int scoreD = scoreC + score(dynamicWords[dFirst][dSecond][ind]);
                                                    // if (scoreD > highestScore) {
                                                    //     highestScore = scoreD;
                                                    //     bestWords.clear();
                                                    //     //Save these words
                                                    //     saveWords({dynamicWords[aFirst][aSecond][ina], dynamicWords[bFirst][bSecond][inb], dynamicWords[cFirst][cSecond][inc], dynamicWords[dFirst][dSecond][ind]});
                                                    // } else if (scoreD == highestScore)
                                                    //     saveWords({dynamicWords[aFirst][aSecond][ina], dynamicWords[bFirst][bSecond][inb], dynamicWords[cFirst][cSecond][inc], dynamicWords[dFirst][dSecond][ind]});
                                                    if (scoreD >= scoreToBeat) {
                                                        auto [fails, bestPermutations] = testPermutations({dynamicWords[aFirst][aSecond][ina], dynamicWords[bFirst][bSecond][inb], dynamicWords[cFirst][cSecond][inc], dynamicWords[dFirst][dSecond][ind]});
                                                        if (fails < lowestFails) {
                                                            lowestFails = fails;
                                                            possiblePermutations = bestPermutations.size();
                                                            bestWords.empty();
                                                            bestWords = bestPermutations[0];
                                                        } else if (fails == lowestFails) {
                                                            possiblePermutations += bestPermutations.size();
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    auto finishTesting = Clock::now();
    std::cout << '(' << std::chrono::duration_cast<std::chrono::milliseconds>(finishTesting - startTesting).count() << "ms)\n";

    // for (std::vector<std::string>& vec : bestWords) {
    //     for (std::string word : vec) {
    //         std::cout << word << ' ';
    //     }
    //     std::cout << '\n';
    // }
    for (std::string word : bestWords)
        std::cout << word << ' ';
    std::cout << '\n';
    std::cout << "lowest fails: " << lowestFails << '\n';
    std::cout << "number of permutations with the same number of fails: " << possiblePermutations;
    // std::cout << "Possible combinations: " << possibleCombinations;

    std::ofstream fout("log.txt");
    for (std::string word : bestWords)
        fout << word << ' ';
    fout << '\n';
    fout << "lowest fails: " << lowestFails << '\n';
    fout << "number of permutations with the same number of fails: " << possiblePermutations;
    fout.close();
    std::cin.ignore();
    return 0;
}

//Best 2 words: 
//Best 3 words: soily prude chant / shady crine poult / shaly coude print / shaly count pride / shaly crude point / shule coady print / shunt coaly pride / shale crudy point
//Best 4 words: shack podgy brume flint / shame podgy brunt flick / shuck podgy brame flint / shuck print bodge flamy / shunt podge blimy frack / shunt podge brick flamy / shunt podgy brame flick / shunt podgy brick flame / shunt prick bodge flamy / shunt primy bodge flack