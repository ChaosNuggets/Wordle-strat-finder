#include <random>
#include <iostream>
#include "words.h"
#include "skip_helper.h"
#include <algorithm>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

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

int main() {
    std::cout << "running ";
    auto startRunning = Clock::now();
    // const std::vector<std::string> firstWords = {"soily", "prude", "chant"};
    std::vector<std::string> firstWords = {"brame", "flint", "podgy", "shuck"};
    // const std::vector<std::string> firstWords = {"glent", "brick", "jumpy", "vozhd", "waqfs"};

    int lowestFails = 12947;
    int highestFails = 0;
    std::vector<std::vector<std::string>> bestPermutations;
    //test all permutations
    std::sort(firstWords.begin(), firstWords.end());
    do {
        int numberOfFails = 0;
        for (auto& answerFirst : words) {
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
                    for (int inputFirst = 0; inputFirst < words.size(); inputFirst++) {
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
                        for (int inputSecond = 0; inputSecond < words[inputFirst].size(); inputSecond++) {
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
                            for (std::string input : words[inputFirst][inputSecond]) {
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
        if (numberOfFails < lowestFails) {
            bestPermutations.clear();
            lowestFails = numberOfFails;
            bestPermutations.push_back(firstWords);
        } else if (numberOfFails == lowestFails) {
            bestPermutations.push_back(firstWords);
        }
        if (numberOfFails > highestFails)
            highestFails = numberOfFails;
    } while (std::next_permutation(firstWords.begin(), firstWords.end()));
    auto finishRunning = Clock::now();
    std::cout << '(' << std::chrono::duration_cast<std::chrono::milliseconds>(finishRunning - startRunning).count() << "ms)\n";
    for (auto& set : bestPermutations) {
        for (std::string word : set) {
            std::cout << word << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "lowest fails: " << lowestFails << '\n';
    std::cout << "highest fails: " << highestFails;
    std::cin.ignore();
    return 0;
}