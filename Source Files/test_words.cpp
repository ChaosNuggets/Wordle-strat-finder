#include <iostream>
#include "const_words.h"
#include "skip_helper.h"
#include <algorithm>
#include "test_words.h"
#include <thread>
#include <future>
#include <chrono>
#include "possible_answers.h"
#include "not_answers.h"

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

// int lowestFailsAll = 12953;
int lowestFailsAnswerList = 2119;
int lowestFailsNotAnswerList = 10834;
int equivalentPermutations = 0;

bool doWordsWork(const std::string answer, const std::vector<std::string> firstWords) {
    int numberOfWordsGuessed = 0;
    //char = letter, int = index
    std::vector<char> grays;
    std::vector<std::pair<char, int>> greens;
    std::vector<std::pair<char, int>> oranges;
    // std::vector<std::string> wordsGuessed;

    //Use first words
    for (int i = 0; i < firstWords.size(); i++) {
        std::string input = firstWords[i];
        numberOfWordsGuessed++;
        if (input == answer) {
            return true;
        }
        determineColors(grays, greens, oranges, input, answer);
        if (greens.size() + oranges.size() == 5)
            break;
    }

    //Guess based on possible words
    //First 2 for loops are for skipping over the impossible words
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
                // wordsGuessed.push_back(input);
                if (input == answer) {
                    return true;
                }
                if (numberOfWordsGuessed >= 6) {
                    return false;
                }
                determineColors(grays, greens, oranges, input, answer);
            }
        }
    }
    throw std::runtime_error(std::string("the answer ") + answer + std::string(" is invalid"));
}

// int testWordsAgainstAll(const std::vector<std::string> firstWords) {
//     int numberOfFails = 0;
//     for (auto& answerFirst : constWords) {
//         for (auto& answerSecond : answerFirst) {
//             for (std::string answer : answerSecond) {
//                 if (!doWordsWork(answer, firstWords))
//                     numberOfFails++;
//                 //We can return early because we don't care about the answers that are above the lowest fails
//                 if (numberOfFails > lowestFailsAll)
//                     return numberOfFails;
//             }
//         }
//     }
//     return numberOfFails;
// }

int testWordsAgainstNotAnswerList(const std::vector<std::string> firstWords) {
    int numberOfFails = 0;
    for (std::string answer : notAnswers1) {
        if (!doWordsWork(answer, firstWords))
            numberOfFails++;
        //We can return early because we don't care about the answers that are above the lowest fails
        if (numberOfFails > lowestFailsNotAnswerList)
            return numberOfFails;
    }
    for (std::string answer : notAnswers2) {
        if (!doWordsWork(answer, firstWords))
            numberOfFails++;
        //We can return early because we don't care about the answers that are above the lowest fails
        if (numberOfFails > lowestFailsNotAnswerList)
            return numberOfFails;
    }
    return numberOfFails;
}

int testWordsAgainstAnswerList(const std::vector<std::string> firstWords) {
    int numberOfFails = 0;
    for (std::string answer : possibleAnswers) {
        if (!doWordsWork(answer, firstWords))
            numberOfFails++;
        //We can return early because we don't care about the answers that are above the lowest fails
        if (numberOfFails > lowestFailsAnswerList)
            return numberOfFails;
    }
    return numberOfFails;
}

std::vector</*std::vector<*/std::string>/*>*/ bestPermutation;

/*TODO:
have the computer determine how many tests it's going to run beforehand
*/

/**
 * @brief tries all permutations and returns the number of fails on the answer list, the number of fails on all the words, and the best permutation
 * 
 * @param firstWords 
 * @return std::tuple<int, int, std::vector<std::vector<std::string>>> 
 */
void testPermutations(std::vector<std::string> firstWords) {
    //test against answer list
    std::sort(firstWords.begin(), firstWords.end());
    std::vector<std::future<int>> answerFutures;
    std::vector<std::vector<std::string>> permutations;
    do {
        answerFutures.emplace_back(std::async(testWordsAgainstAnswerList, firstWords));
        permutations.emplace_back(firstWords);
    } while (std::next_permutation(firstWords.begin(), firstWords.end()));

    //Decide whether it should keep testing each permutation
    int j = 0; //the index of the permutation the answerFuture corresponds to
    for (int i = 0; i < answerFutures.size(); i++) {
        int numberOfFails = answerFutures[i].get();
        if (numberOfFails < lowestFailsAnswerList) {
            lowestFailsAnswerList = numberOfFails;
            //get rid of the permutations before the good one
            permutations.erase(permutations.begin(), permutations.begin() + j);
            //permutations now serves as the list of permutations to keep testing
            bestPermutation = permutations[0];
            j = 1;
            //Reset this now that we've found a better solution
            lowestFailsNotAnswerList = 10834;
        } else if (numberOfFails > lowestFailsAnswerList) {
            //If bad then get rid of the permutation
            permutations.erase(permutations.begin() + j);
            //j doesn't change
        } else
            //If it's equal increment j
            j++;
    }

    //Test each remaining permutation
    std::vector<std::future<int>> notAnswerFutures;
    for (auto& permutation : permutations) {
        notAnswerFutures.emplace_back(std::async(testWordsAgainstNotAnswerList, permutation));
    }

    //get the results for the remaining permutations (all the remaining permutations have the same value for lowestFailsAnswerList)
    for (int i = 0; i < notAnswerFutures.size(); i++) {
        int numberOfFails = notAnswerFutures[i].get();
        if (numberOfFails < lowestFailsNotAnswerList) {
            //You have just found the best permutation so far
            lowestFailsNotAnswerList = numberOfFails;
            bestPermutation = permutations[i];
            equivalentPermutations = 1;
        } else if (numberOfFails == lowestFailsNotAnswerList) {
            equivalentPermutations++;
        }
    }
}

// int main() {
//     auto startTesting = Clock::now();
//     std::cout << "running ";
//     // std::vector<std::string> firstWords = {"soily", "prude", "chant"}; //Highest scoring 3
//     // std::vector<std::string> firstWords = {"fitly", "paned", "smock", "burgh"}; //Best I could find for all answers
//     std::vector<std::string> firstWords = {"brogh", "safed", "tumpy", "clink"}; //Best I could find for wordle answer list
//     // std::vector<std::string> firstWords = {"stare", "doing", "lucky"}; //Buzzfeed suggestion
//     // std::vector<std::string> firstWords = {"redub", "oflag", "ticks", "nymph"}; //Lowest scoring 4
//     // std::vector<std::string> firstWords = {"glent", "brick", "jumpy", "vozhd", "waqfs"}; //Popular tiktok strategy
//     testPermutations(firstWords);
//     auto finishTesting = Clock::now();
//     std::cout << '(' << std::chrono::duration_cast<std::chrono::milliseconds>(finishTesting-startTesting).count() << "ms)\n";
//     // for (auto& set : bestPermutation) {
//     //     for (std::string word : set) {
//     //         std::cout << word << ' ';
//     //     }
//     //     std::cout << '\n';
//     // }
//     for (std::string word : bestPermutation) {
//         std::cout << word << ' ';
//     }
//     std::cout << '\n';
//     std::cout << "fails against answer list: " << lowestFailsAnswerList << '\n';
//     std::cout << "fails against all words: " << lowestFailsAnswerList + lowestFailsNotAnswerList;
//     std::cin.ignore();
//     return 0;
// }