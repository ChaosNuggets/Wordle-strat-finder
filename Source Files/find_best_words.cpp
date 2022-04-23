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
#include "score.h"

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

// std::vector<std::string> bestWords;

// void saveWords(const std::vector<std::string> strings) {
//     bestWords.push_back(strings);
// }

void removeUnnecessaryWords(const std::vector<char>& usingLetters) {
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
}

std::vector<std::vector<std::string>> combinations;

void findCombinations(const std::vector<char>& usingLetters, const int lowerScore, const int upperScore) {
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
                                                    if (scoreD >= lowerScore && scoreD < upperScore) {
                                                        combinations.push_back({dynamicWords[aFirst][aSecond][ina], dynamicWords[bFirst][bSecond][inb], dynamicWords[cFirst][cSecond][inc], dynamicWords[dFirst][dSecond][ind]});
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

void testEveryPermutation() {
    for(auto& combination : combinations) {
        testPermutations(combination);
        if (lowestFailsAnswerList == 0 && lowestFailsNotAnswerList == 0)
            return;
    }
}

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
    removeUnnecessaryWords(usingLetters);
    auto startFinding = Clock::now();
    std::cout << '(' << std::chrono::duration_cast<std::chrono::microseconds>(startFinding - startRemoving).count() << "µs)\n";

    std::cout << "finding combinations ";
    findCombinations(usingLetters, 2700, 2800); //Finds all the combinations between upper and lower scores
    auto startTesting = Clock::now();
    std::cout << '(' << std::chrono::duration_cast<std::chrono::milliseconds>(startTesting - startFinding).count() << "ms)\n";
    std::cout << "combinations found: " << combinations.size() << '\n';

    std::cout << "testing permutations ";
    testEveryPermutation(); //Tests all the permutations of the combinations that were found using findCombinations()
    auto finishTesting = Clock::now();
    std::cout << '(' << std::chrono::duration_cast<std::chrono::milliseconds>(finishTesting - startTesting).count() << "s)\n";

    // for (std::vector<std::string>& vec : bestWords) {
    //     for (std::string word : vec) {
    //         std::cout << word << ' ';
    //     }
    //     std::cout << '\n';
    // }
    for (std::string word : bestPermutation)
        std::cout << word << ' ';
    std::cout << '\n';
    std::cout << "fails against answer list: " << lowestFailsAnswerList << '\n';
    std::cout << "fails against all words: " << lowestFailsAnswerList + lowestFailsNotAnswerList << '\n';
    std::cout << "number of permutations with the same number of fails: " << equivalentPermutations;

    std::ofstream fout("log.txt");
    for (std::string word : bestPermutation)
        fout << word << ' ';
    fout << '\n';
    fout << "fails against answer list: " << lowestFailsAnswerList << '\n';
    fout << "fails against all words: " << lowestFailsAnswerList + lowestFailsNotAnswerList << '\n';
    fout << "number of permutations with the same number of fails: " << equivalentPermutations;
    fout.close();
    std::cin.ignore();
    return 0;
}

//Best 4 words: