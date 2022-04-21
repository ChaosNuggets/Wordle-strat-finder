#include <random>
#include <iostream>
#include <fstream>
#include <algorithm>

void gotoLine(std::ifstream& fin, unsigned int num){
    fin.seekg(std::ios::beg);
    for(int i = 0; i < num - 1; i++){
        fin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
}

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

int main() {
    const int numberOfWords = 12947;
    // const std::vector<std::string> firstWords = {"soily", "prude", "chant"};
    const std::vector<std::string> firstWords = {"brame", "flint", "podgy", "shuck"};
    // const std::vector<std::string> firstWords = {"glent", "brick", "jumpy", "vozhd", "waqfs"};
    int numberOfFails = 0;

    std::ifstream fin1("words.txt");
    if (!fin1.is_open())
        throw std::runtime_error("fin1 could not open file");
    for (int h = 0; h < numberOfWords - 1; h++) {
        std::string answer;
        fin1 >> answer;
        
        bool hasWon = false;
        int numberOfWordsTested = 0;
        //char = letter, int = index
        std::vector<char> grays;
        std::vector<std::pair<char, int>> greens;
        std::vector<std::pair<char, int>> oranges;
        std::vector<std::string> wordsGuessed;
        for (int i = 0; i < firstWords.size(); i++) {
            std::string input = firstWords[i];
            numberOfWordsTested++;
            wordsGuessed.push_back(input);
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
        int allCluesReached = wordsGuessed.size();
        std::vector<char> firstWordsGreens;
        for (auto& [letter, index] : greens) {
            firstWordsGreens.emplace_back(letter);
        }
        std::vector<char> firstWordsOranges;
        for (auto& [letter, index] : oranges) {
            firstWordsOranges.emplace_back(letter);
        }
        std::string input;
        std::ifstream fin2("words.txt");
        for (int i = 0; i < numberOfWords-1; i++) {
            if (numberOfWordsTested >= 6) {
                break;
            }
            //Determine input
            fin2 >> input;
            bool isGoodInput = true;
            //Test grays
            for (char letter : input) {
                if (std::find(grays.begin(), grays.end(), letter) != grays.end()) {
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
                auto found = input.find(letter);
                if (found == index || found == std::string::npos) {
                    isGoodInput = false;
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
                break;
            }
            determineColors(grays, greens, oranges, input, answer);
        }
        if (!hasWon) {
            // using std::cout;
            // // cout << "failed on " << answer << " (";
            // // for (int i = allCluesReached; i < wordsGuessed.size(); i++)
            // //     cout << wordsGuessed[i] << ' ';
            // // cout << ", greens:";
            // for (char letter : firstWordsGreens)
            //     cout << ' ' << letter;
            // // cout << ", oranges:";
            // cout << ',';
            // for (char letter : firstWordsOranges)
            //     cout << ' ' << letter;
            // // cout << ")\n";
            // cout << '\n';
            numberOfFails++;
        }
    }
    std::cout << "number of fails: " << numberOfFails;
    std::cin.ignore();
    return 0;
}