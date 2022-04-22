#include <iostream>
#include "const_words.h"
#include "skip_helper.h"
#include <algorithm>
#include "test_words.h"
#include <thread>
#include <mutex>
#include <chrono>
// #include "possible_answers.h"

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

int lowestFails = 12947;

bool doWordsFail(const std::string answer, const std::vector<std::string> firstWords) {
    
}

int testWords(const std::vector<std::string> firstWords) {
    int numberOfFails = 0;
    for (auto& answerFirst : constWords) {
        for (auto& answerSecond : answerFirst) {
            for (std::string answer : answerSecond) {
            // for (std::string answer : possibleAnswers) {
                bool hasWon = false;
                int numberOfWordsGuessed = 0;
                //char = letter, int = index
                std::vector<char> grays;
                std::vector<std::pair<char, int>> greens;
                std::vector<std::pair<char, int>> oranges;
                std::vector<std::string> wordsGuessed;

                //Use first words
                for (int i = 0; i < firstWords.size(); i++) {
                    std::string input = firstWords[i];
                    numberOfWordsGuessed++;
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
                            numberOfWordsGuessed++;
                            wordsGuessed.push_back(input);
                            if (input == answer) {
                                hasWon = true;
                                shouldCompletelyBreak = true;
                                break;
                            }
                            if (numberOfWordsGuessed >= 6) {
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
                    //lowestFails is only going to go down so it's fine if this reads from an old lowestFails
                    if (numberOfFails > lowestFails) {
                        //We can return early if it goes over lowestFails
                        return numberOfFails;
                    }
                }
            }
        }
    }
    return numberOfFails;
}

std::vector</*std::vector<*/std::string>/*>*/ bestPermutations;
std::mutex mtx;

void compareFails(const std::vector<std::string> firstWords) {
    int numberOfFails = testWords(firstWords);
    if (numberOfFails < lowestFails) {
        mtx.lock();
        lowestFails = numberOfFails;
        bestPermutations = firstWords;
        // bestPermutations.clear();
        // bestPermutations.push_back(firstWords);
        mtx.unlock();
    } /*else if (numberOfFails == lowestFails) {
        mtx.lock();
        bestPermutations.push_back(firstWords);
        mtx.unlock();
    }*/
}

/*TODO:
remove unnecessary saved permutations
have the computer determine how many tests it's going to run beforehand
test against wordle answers before testing against all words
*/

/**
 * @brief tries all permutations and returns the best permutations along with the number of fails
 * 
 * @param firstWords 
 * @return std::pair<int, std::vector<std::vector<std::string>>> 
 */
std::pair<int, std::vector</*std::vector<*/std::string>>/*>*/ testPermutations(std::vector<std::string> firstWords) {
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

int main() {
    auto startTesting = Clock::now();
    std::cout << "running ";
    // std::vector<std::string> firstWords = {"soily", "prude", "chant"}; //Highest scoring 3
    std::vector<std::string> firstWords = {"fitly", "paned", "smock", "burgh"}; //Best I could find for all answers
    // std::vector<std::string> firstWords = {"brogh", "safed", "tumpy", "clink"}; //Best I could find for wordle answer list
    // std::vector<std::string> firstWords = {"stare", "doing", "lucky"}; //Buzzfeed suggestion
    // std::vector<std::string> firstWords = {"redub", "oflag", "ticks", "nymph"}; //Lowest scoring 4
    // std::vector<std::string> firstWords = {"glent", "brick", "jumpy", "vozhd", "waqfs"}; //Popular tiktok strategy
    auto [lowestFails, bestPermutations] = testPermutations(firstWords);
    auto finishTesting = Clock::now();
    std::cout << '(' << std::chrono::duration_cast<std::chrono::milliseconds>(finishTesting-startTesting).count() << "ms)\n";
    // for (auto& set : bestPermutations) {
    //     for (std::string word : set) {
    //         std::cout << word << ' ';
    //     }
    //     std::cout << '\n';
    // }
    for (std::string word : bestPermutations) {
        std::cout << word << ' ';
    }
    std::cout << '\n';
    std::cout << "lowest fails: " << lowestFails;
    std::cin.ignore();
    return 0;
}