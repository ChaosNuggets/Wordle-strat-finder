// #include "possible_answers.h"
// #include "dynamic_words.h"
// #include "skip_helper.h"
// #include <algorithm>
// #include <fstream>
// // #include <iostream>

// int main() {
//     //Add missing words
//     for (std::string word : possibleAnswers) {
//         // std::cout << word;
//         int firstDimensionIndex = std::find(firstDimensionOrder.begin(), firstDimensionOrder.end(), word[0]) - firstDimensionOrder.begin();
//         int secondDimensionIndex = charToAlphaPlace(word[1]);
//         bool found = false;
//         for (int i = 0; i < dynamicWords[firstDimensionIndex][secondDimensionIndex].size(); i++) {
//             if (dynamicWords[firstDimensionIndex][secondDimensionIndex][i] == word)
//                 found = true;
//         }
//         if (!found) {
//             dynamicWords[firstDimensionIndex][secondDimensionIndex].push_back(word);
//         }
//         // std::cout << word;
//     }

//     //Sort each array and log it
//     std::ofstream fout;
//     fout.open("stupid.txt", std::ios_base::app);
//     fout << "{\n";
//     for (auto& vec : dynamicWords) {
//         fout << '{';
//         for (auto& innerVec : vec) {
//             fout << '{';
//             std::sort(innerVec.begin(), innerVec.end());
//             for (std::string word : innerVec) {
//                 fout << '"' << word << "\",";
//             }
//             fout << "},";
//         }
//         fout << "},\n";
//     }
//     fout << "};";
//     fout.close();
//     return 0;
// }