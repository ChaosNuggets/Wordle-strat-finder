// #include "const_words.h"
// #include "possible_answers.h"
// // #include <iostream>
// #include <fstream>
// #include <algorithm>

// int main() {
//     std::ofstream fout;
//     fout.open("not answers.txt", std::ios_base::app);
//     for (auto& vec : constWords) {
//         for (auto& vecvec : vec) {
//             for (std::string word : vecvec) {
//                 if (std::find(possibleAnswers.begin(), possibleAnswers.end(), word) == possibleAnswers.end())
//                     fout << '"' << word << "\",\n";
//             }
//         }
//     }
//     fout.close();
//     // std::cout << total;
// }