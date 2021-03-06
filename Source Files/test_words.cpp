#include <iostream>
#include "const_words.h"
#include "skip_helper.h"
#include <algorithm>
#include <thread>
#include <future>
#include <chrono>
#include "possible_answers.h"
#include "test_words.h"
#include "not_answers.h"
// #include <vector>

// typedef std::chrono::high_resolution_clock Clock;

static void determineColors(std::vector<char>& grays, std::vector<std::pair<char, int>>& greens, std::vector<std::pair<char, int>>& oranges, const std::string input, const std::string answer) {
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

static std::vector<std::pair<char, int>>::iterator findPair(const std::vector<std::pair<char, int>>::iterator first, const std::vector<std::pair<char, int>>::iterator last, const std::pair<char, int>& item) {
    for (auto it = first; it != last; it++) {
        if (*it == item)
            return it;
    }
    return last;
}

static std::vector<std::pair<char, int>>::iterator findSecond(const std::vector<std::pair<char, int>>::iterator first, const std::vector<std::pair<char, int>>::iterator last, const int item) {
    for (auto it = first; it != last; it++) {
        if (it->second == item)
            return it;
    }
    return last;
}

static bool doesWordMatchClues(const std::vector<char>& grays, const std::vector<std::pair<char, int>>& greens, const std::vector<std::pair<char, int>>& oranges, const std::string input, const bool skipFirst2Letters) {
    //Test grays (we only need to test the last 3 letters since we already tested the first 2 above)
    int i;
    if (skipFirst2Letters)
        i = 2;
    else
        i = 0;
    for (; i < 5; i++) {
        if (std::find(grays.begin(), grays.end(), input[i]) != grays.end()) {
            return false;
        }
    }
    //Test greens
    for (auto& [letter, index] : greens) {
        if (input[index] != letter) {
            return false;
        }
    }
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
                return false;
            }
            startLooking = found+1;
        }
        if (!hasBeenFound)
            return false;
    }
    return true;
}

static bool doWordsEliminateEachOther(const std::vector<char>& grays, const std::vector<std::pair<char, int>>& greens, const std::vector<std::pair<char, int>>& oranges, std::vector<std::string> possibleInputs, const std::string answer, const int freeSpots) {
    for (int i = 0; i < possibleInputs.size(); i++) {
        if (possibleInputs.size() <= freeSpots)
            return true;
        if (freeSpots > 0) {
            if (possibleInputs[i] == answer)
                continue;
            if (doesWordMatchClues(grays, greens, oranges, possibleInputs[i], false)) {
                std::vector<char> newGrays = grays;
                std::vector<std::pair<char, int>> newGreens = greens;
                std::vector<std::pair<char, int>> newOranges = oranges;
                std::vector<std::string> newPossibleInputs = possibleInputs;
                determineColors(newGrays, newGreens, newOranges, possibleInputs[i], answer);
                newPossibleInputs.erase(newPossibleInputs.begin() + i);
                if (doWordsEliminateEachOther(newGrays, newGreens, newOranges, newPossibleInputs, answer, freeSpots-1))
                    continue;
                else
                    return false;
            } else {
                possibleInputs.erase(possibleInputs.begin() + i);
                i--;
                continue;
            }
        } else
            return false;
    }
    return true;
}

//1st dim = different answers 2nd dim is for separating the answers from the possible guesses
// std::vector<std::vector<std::string>> wordsThatFail;

static bool doWordsWork(const std::string answer, const std::vector<std::string> firstWords) {
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
    std::vector<std::string> possibleInputs;
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
                if (doesWordMatchClues(grays, greens, oranges, input, true))
                    possibleInputs.push_back(input);
                // numberOfWordsGuessed++;
                // wordsGuessed.push_back(input);
                // if (input == answer) {
                //     return true;
                // }
                // if (numberOfWordsGuessed >= 7) {
                //     return false;
                // }
                // determineColors(grays, greens, oranges, input, answer);
            }
        }
    }

    //Test each possible input to see if they eliminate each other
    return doWordsEliminateEachOther(grays, greens, oranges, possibleInputs, answer, 6-numberOfWordsGuessed);
    // if (doWordsEliminateEachOther(grays, greens, oranges, possibleInputs, answer, 6-numberOfWordsGuessed))
    //     return true;
    // else {
    //     std::vector<std::string> vectorThatsGoingToBePushedBackVerySoon;
    //     vectorThatsGoingToBePushedBackVerySoon.emplace_back(answer);
    //     for (std::string input : possibleInputs) {
    //         vectorThatsGoingToBePushedBackVerySoon.emplace_back(input);
    //     }
    //     wordsThatFail.push_back(vectorThatsGoingToBePushedBackVerySoon);
    //     return false;
    // }
    // throw std::runtime_error(std::string("the answer ") + answer + std::string(" is invalid"));
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

// int lowestFailsAll = 12974;
int lowestFailsAnswerList = 2309;
int lowestFailsNotAnswerList = 10665;
int equivalentPermutations = 0;

static int testWordsAgainstNotAnswerList(const std::vector<std::string> firstWords) {
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

static int testWordsAgainstAnswerList(const std::vector<std::string> firstWords) {
    int numberOfFails = 0;
    for (std::string answer : possibleAnswers) {
        if (!doWordsWork(answer, firstWords)) {
            numberOfFails++;
            // std::cout << answer << '\n';
        }
        //We can return early because we don't care about the answers that are above the lowest fails
        if (numberOfFails > lowestFailsAnswerList)
            return numberOfFails;
    }
    return numberOfFails;
}

std::vector</*std::vector<*/std::string>/*>*/ bestPermutation;

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
            //permutations now serves as the list of permutations to keep testing
            //get rid of the permutations before the good one
            permutations.erase(permutations.begin(), permutations.begin() + j);
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
            // for (std::string word : permutations[i]) {
            //     std::cout << word << ' ';
            // }
            // std::cout << numberOfFails << " \n";
        } else if (numberOfFails == lowestFailsNotAnswerList) {
            equivalentPermutations++;
            // for (std::string word : permutations[i]) {
            //     std::cout << word << ' ';
            // }
            // std::cout << numberOfFails << " \n";
        }
    }
}

// int main() {
//     auto startTesting = Clock::now();
//     std::cout << "running ";
//     // std::vector<std::string> firstWords = {"flame", "shunt", "brick", "podgy"}; //Pokecheese's strategy
//     std::vector<std::string> firstWords = {"kings", "ralph", "tubed", "comfy"}; //Most guaranteed answers (best for no memorization)
//     // std::vector<std::string> firstWords = {"stare", "doing", "lucky"}; //Buzzfeed suggestion
//     // std::vector<std::string> firstWords = {"redub", "oflag", "ticks", "nymph"}; //Lowest scoring 4
//     // std::vector<std::string> firstWords = {"glent", "brick", "jumpy", "vozhd", "waqfs"}; //Popular tiktok strategy
//     // testPermutations(firstWords);
//     lowestFailsAnswerList = testWordsAgainstAnswerList(firstWords);
//     auto finishTesting = Clock::now();
//     std::cout << '(' << std::chrono::duration_cast<std::chrono::milliseconds>(finishTesting-startTesting).count() << "ms)\n";
//     // for (auto& set : bestPermutation) {
//     //     for (std::string word : set) {
//     //         std::cout << word << ' ';
//     //     }
//     //     std::cout << '\n';
//     // }
//     // for (std::string word : bestPermutation) {
//     //     std::cout << word << ' ';
//     // }
//     // std::cout << '\n';
//     std::sort(wordsThatFail.begin(), wordsThatFail.end());
//     for (auto& set : wordsThatFail) {
//         std::cout << '"' << set[0] << "\" fails (possible guesses:";
//         for (int i = 1; i < set.size(); i++) {
//             std::cout << ' ' << set[i];
//         }
//         std::cout << ")\n";
//     }
//     std::cout << "fails against answer list: " << lowestFailsAnswerList << " / 2309\n";
//     std::cout << "fails against all words: " << lowestFailsAnswerList + lowestFailsNotAnswerList << " / 12974\n";
//     std::cout << "equivalent permutations: " << equivalentPermutations;
//     std::cin.ignore();
//     return 0;
// }

// int main() {
//     std::vector<char> grays = {'f', 'l', 'm', 'e', 's', 'h', 'b', 'r', 'i', 'c', 'k', 'p', 'o', 'd', 'g', 'y'};
//     std::vector<std::pair<char, int>> greens = {{'u', 2}, {'n', 3}, {'t', 4}};
//     std::vector<std::pair<char, int>> oranges = {{'a', 2}};
//     std::vector<std::string> possibleInputs = {"taunt", "naunt", "vaunt", "jaunt"};
//     std::cout << doWordsEliminateEachOther(grays, greens, oranges, possibleInputs, "jaunt", possibleInputs.size() - 1);
//     return 0;
// }