// #include <iostream>
// #include "words.h"
// // #include <vector>
// // #include <string>
// #include <algorithm>
// #include <unordered_map>

// std::vector<std::vector<std::string>> bestWords;

// bool removeUsedLetters(std::vector<char>& unusedLetters, std::string word) {
//     for (char letter : word) {                        
//         auto it = std::find(unusedLetters.begin(), unusedLetters.end(), letter);
//         //If letter is in the list
//         if (it != unusedLetters.end()) {
//             unusedLetters.erase(it);
//         } else
//             return false;
//     }
//     return true;
// }

// //matching probability*100
// const std::unordered_map<char, std::vector<int>> matchingProbability = {
//     {'a', {109, 234, 237, 126,  49}},

//     {'c', {153,  31,  43, 117,  24}},
//     {'d', { 86,  15,  58,  53,  91}},
//     {'e', { 55, 187, 136, 245, 327}},


//     {'h', { 53, 111,   7,  22, 107}},
//     {'i', { 26, 156, 205, 122,   8}},


//     {'l', { 68, 155,  86, 125, 120}},

//     {'n', { 29,  67, 107, 140, 100}},
//     {'o', { 32, 215, 188, 102,  45}},
//     {'p', {109,  47,  45,  39,  43}},

//     {'r', { 81, 206, 126, 117, 163}},
//     {'s', {282,  12,  62, 132,  28}},
//     {'t', {115,  59,  86, 107, 195}},
//     {'u', { 25, 143, 127,  63,   1}},



//     {'y', {  5,  18,  22,   2, 281}},

// };

// int score(std::string word) {
//     int currentScore = 0;
//     for (int i = 0; i < 5; i++) {
//         currentScore += matchingProbability.at(word[i])[i];
//     }
//     return currentScore;
// }

// void saveWords(std::string word1, std::string word2, std::string word3) {
//     std::vector<std::string> goodSet;
//     goodSet.push_back(word1);
//     goodSet.push_back(word2);
//     goodSet.push_back(word3);
//     bestWords.push_back(goodSet);
// }

// int main() {
//     std::vector<char> usingLetters = {
//         'e', 'a', 'r', 'o', 't',
//         'l', 'i', 's', 'n', 'u',
//         'c', 'y', 'h', 'd', 'p',
//         // 'g', 'm', 'b', 'f', 'k',
//         // 'w', 'v', 'x', 'z', 'q',
//         // 'j'
//     };

//     std::cout << "removing unnecessary words\n";
//     for (int i = 0; i < words.size(); i++) {
//         std::vector<std::string> currentWords = words[i];
//         for (int j = 0; j < currentWords.size(); j++) {
//             for (int k = 0; k < currentWords[j].size(); k++) {
//                 //Remove if one of the letters isn't in the usingLetters list
//                 if (std::find(usingLetters.begin(), usingLetters.end(), currentWords[j][k]) == usingLetters.end()) {
//                     currentWords.erase(currentWords.begin() + j);
//                     j--;
//                     break;
//                 }
//                 //Remove if it has repeated letters
//                 bool shouldBreak = false;
//                 for (int l = k+1; l < currentWords[j].size(); l++) {
//                     if (currentWords[j][k] == currentWords[j][l]) {
//                         currentWords.erase(currentWords.begin() + j);
//                         j--;
//                         shouldBreak = true;
//                         break;
//                     }
//                 }
//                 if (shouldBreak)
//                     break;
//             }
//         }
//         words[i] = currentWords;
//     }

//     std::cout << "testing combinations\n";
//     int highestScore = 0;
//     for (int a = 0; a < words.size()-2; a++) {
//         for (int ina = 0; ina < words[a].size(); ina++) {
//             //This list is in order of most common -> least common
//             std::vector<char> unusedLettersA = usingLetters;
//             if (!removeUsedLetters(unusedLettersA, words[a][ina])) //If not in list of unused letters
//                 continue;
//             int scoreA = score(words[a][ina]);
//             for (int b = a+1; b < words.size()-1; b++) {
//                 for (int inb = 0; inb < words[b].size(); inb++) {
//                     std::vector<char> unusedLettersB = unusedLettersA;
//                     if (!removeUsedLetters(unusedLettersB, words[b][inb]))
//                         continue;
//                     int scoreB = scoreA + score(words[b][inb]);
//                     for (int c = b+1; c < words.size(); c++) {
//                         for (int inc = 0; inc < words[c].size(); inc++) {
//                             std::vector<char> unusedLettersC = unusedLettersB;
//                             if (!removeUsedLetters(unusedLettersC, words[c][inc]))
//                                 continue;
//                             int scoreC = scoreB + score(words[c][inc]);
//                             if (scoreC > highestScore) {
//                                 highestScore = scoreC;
//                                 bestWords.clear();
//                                 //Save these words
//                                 saveWords(words[a][ina], words[b][inb], words[c][inc]);
//                             } else if (scoreC == highestScore)
//                                 saveWords(words[a][ina], words[b][inb], words[c][inc]);
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     for (std::vector<std::string>& vec : bestWords) {
//         for (std::string word : vec) {
//             std::cout << word << '\n';
//         }
//         std::cout << '\n';
//     }
//     std::cin.ignore();
//     return 0;
// }

// //Best 2 words: 
// //Best 3 words: soily, prude, chant / shady, crine, poult / shaly, coude, print / shaly, count, pride / shaly, crude, point / shule, coady, print / shunt, coaly, pride / shale, crudy, point
// //Best 4 words: 