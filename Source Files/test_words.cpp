#include <iostream>
#include "const_words.h"
#include "skip_helper.h"
#include <algorithm>
#include "test_words.h"
#include <thread>
#include <mutex>

void determineColors(std::vector<char>& grays, std::vector<std::pair<char, int>>& greens, std::vector<std::pair<char, int>>& oranges, std::string input, std::string answer) {
    for (int j = 0; j < 5; j++) {
        bool isOrange = false;
        bool isGreen = false;
        for (int k = 0; k < 5; k++) {
            if (input[j] == answer[k]) {
                if (j == k) {
                    isGreen = true;
                    break;
                } else {
                    isOrange = true;
                }
            }
        }
        if (isGreen)
            greens.push_back({input[j], j});
        else if (isOrange)
            oranges.push_back({input[j], j});
        else
            grays.push_back(input[j]);
    }
}

std::vector<std::pair<char, int>>::iterator findPair(const std::vector<std::pair<char, int>>::iterator first, const std::vector<std::pair<char, int>>::iterator last, const std::pair<char, int>& item) {
    for (auto it = first; it != last; it++) {
        if (*it == item)
            return it;
    }
    return last;
}

std::vector<std::pair<char, int>>::iterator findSecond(const std::vector<std::pair<char, int>>::iterator first, const std::vector<std::pair<char, int>>::iterator last, const int item) {
    for (auto it = first; it != last; it++) {
        if (it->second == item)
            return it;
    }
    return last;
}

int testWords(const std::vector<std::string> firstWords) {
    int numberOfFails = 0;
    for (auto& answerFirst : constWords) {
        for (auto& answerSecond : answerFirst) {
            for (std::string answer : answerSecond) {
                bool hasWon = false;
                int numberOfWordsTested = 0;
                //char = letter, int = index
                std::vector<char> grays;
                std::vector<std::pair<char, int>> greens;
                std::vector<std::pair<char, int>> oranges;
                std::vector<std::string> wordsGuessed;

                //Use first words
                for (int i = 0; i < firstWords.size(); i++) {
                    std::string input = firstWords[i];
                    numberOfWordsTested++;
                    if (input == answer) {
                        hasWon = true;
                        break;
                    }
                    determineColors(grays, greens, oranges, input, answer);
                    if (greens.size() + oranges.size() == 5)
                        break;
                }
                if (hasWon)
                    continue;

                //Guess based on possible words
                //First 2 for loops are for skipping over the impossible words
                bool shouldCompletelyBreak = false;
                for (int inputFirst = 0; inputFirst < constWords.size(); inputFirst++) {
                    char firstLetter = firstDimensionOrder[inputFirst];
                    //Test grays (if it finds the letter in grays continue)
                    if (std::find(grays.begin(), grays.end(), firstLetter) != grays.end())
                        continue;
                    //Test greens (if there is a green with index 0 and it's not equal to the first letter continue)
                    {
                        auto it = findSecond(greens.begin(), greens.end(), 0);
                        if (it != greens.end())
                            if (it->first != firstLetter)
                                continue;
                    }
                    //Test oranges (if it finds the same letter in the same index that is orange, continue)
                    if (findPair(oranges.begin(), oranges.end(), {firstLetter, 0}) != oranges.end())
                        continue;
                    for (int inputSecond = 0; inputSecond < constWords[inputFirst].size(); inputSecond++) {
                        char secondLetter = alphaPlaceToChar(inputSecond);
                        if (std::find(grays.begin(), grays.end(), secondLetter) != grays.end())
                            continue;
                        //Test greens (if it doesn't find the pair inside greens continue)
                        {
                            auto it = findSecond(greens.begin(), greens.end(), 1);
                            if (it != greens.end())
                                if (it->first != secondLetter)
                                    continue;
                        }
                        //Test oranges (if it finds the same letter in the same index that is orange, continue)
                        if (findPair(oranges.begin(), oranges.end(), {secondLetter, 1}) != oranges.end())
                            continue;
                        for (std::string input : constWords[inputFirst][inputSecond]) {
                            bool isGoodInput = true;
                            //Test grays (we only need to test the last 3 letters since we already tested the first 2 above)
                            for (int i = 2; i < 5; i++) {
                                if (std::find(grays.begin(), grays.end(), input[i]) != grays.end()) {
                                    isGoodInput = false;
                                    break;
                                }
                            }
                            if (!isGoodInput)
                                continue;
                            //Test greens
                            for (auto& [letter, index] : greens) {
                                if (input[index] != letter) {
                                    isGoodInput = false;
                                    break;
                                }
                            }
                            if (!isGoodInput)
                                continue;
                            //Test oranges
                            for (auto& [letter, index] : oranges) {
                                std::size_t startLooking = 0;
                                bool hasBeenFound = false;
                                while (true) {
                                    auto found = input.find(letter, startLooking);
                                    if (found == std::string::npos)
                                        break;
                                    else
                                        hasBeenFound = true;
                                    if (found == index) {
                                        isGoodInput = false;
                                        break;
                                    }
                                    startLooking = found+1;
                                }
                                if (!hasBeenFound) {
                                    isGoodInput = false;
                                }
                                if (!isGoodInput) {
                                    break;
                                }
                            }
                            if (!isGoodInput)
                                continue;
                            //If the code reaches here, the input is good, so try it
                            numberOfWordsTested++;
                            wordsGuessed.push_back(input);
                            if (input == answer) {
                                hasWon = true;
                                shouldCompletelyBreak = true;
                                break;
                            }
                            if (numberOfWordsTested >= 6) {
                                shouldCompletelyBreak = true;
                                break;
                            }
                            determineColors(grays, greens, oranges, input, answer);
                        }
                        if (shouldCompletelyBreak)
                            break;
                    }
                    if (shouldCompletelyBreak)
                        break;
                }
                if (!hasWon) {
                    // using std::cout;
                    // cout << "failed on " << answer << " (";
                    // for (std::string word : wordsGuessed)
                    //     cout << word << ' ';
                    // cout << ')';
                    // cout << '\n';
                    numberOfFails++;
                }
            }
        }
    }
    return numberOfFails;
}

int lowestFails = 12947;
std::vector<std::vector<std::string>> bestPermutations;
std::mutex mtx;

void compareFails(const std::vector<std::string> firstWords) {
    int numberOfFails = testWords(firstWords);
    if (numberOfFails < lowestFails) {
        mtx.lock();
        lowestFails = numberOfFails;
        bestPermutations.clear();
        bestPermutations.push_back(firstWords);
        mtx.unlock();
    } else if (numberOfFails == lowestFails) {
        mtx.lock();
        bestPermutations.push_back(firstWords);
        mtx.unlock();
    }
}

/**
 * @brief tries all permutations and returns the best permutations along with the number of fails
 * 
 * @param firstWords 
 * @return std::pair<int, std::vector<std::vector<std::string>>> 
 */
std::pair<int, std::vector<std::vector<std::string>>> testPermutations(std::vector<std::string> firstWords) {
    //test all permutations
    std::sort(firstWords.begin(), firstWords.end());
    std::vector<std::thread> threads;
    do {
        threads.emplace_back(std::thread(compareFails, firstWords));
    } while (std::next_permutation(firstWords.begin(), firstWords.end()));
    for (std::thread& thread : threads) {
        thread.join();
    }
    return {lowestFails, bestPermutations};
}

// int main() {
//     std::cout << "running\n";
//     // const std::vector<std::string> firstWords = {"soily", "prude", "chant"};
//     // std::vector<std::string> firstWords = {"brame", "flint", "shuck", "podgy"};
//     // std::vector<std::string> firstWords = {"redub", "oflag", "ticks", "nymph"};
//     std::vector<std::string> firstWords = {"shame", "podgy", "brunt", "flick"};
//     // const std::vector<std::string> firstWords = {"glent", "brick", "jumpy", "vozhd", "waqfs"};
    
//     auto [lowestFails, bestPermutations] = testPermutations(firstWords);
//     for (auto& set : bestPermutations) {
//         for (std::string word : set) {
//             std::cout << word << ' ';
//         }
//         std::cout << '\n';
//     }
//     std::cout << "lowest fails: " << lowestFails << '\n';
//     std::cin.ignore();
//     return 0;
// }