// #include <vector>
// #include <string>
// #include <unordered_map>
// #include <algorithm>
// #include <iostream>

// std::vector<std::vector<std::string>> bestWords = {
//     {"shack", "podgy", "brume", "flint"},
//     {"shame", "podgy", "brunt", "flick"},
//     {"shuck", "podgy", "brame", "flint"},
//     {"shuck", "print", "bodge", "flamy"},
//     {"shunt", "podge", "blimy", "frack"},
//     {"shunt", "podge", "brick", "flamy"},
//     {"shunt", "podgy", "brame", "flick"},
//     {"shunt", "podgy", "brick", "flame"},
//     {"shunt", "prick", "bodge", "flamy"},
//     {"shunt", "primy", "bodge", "flack"}
// };

// std::unordered_map<char, int> letterOccurences = {
//     {'e', 814}, {'a', 701}, {'r', 645}, {'o', 519}, {'t', 514},
//     {'l', 499}, {'i', 499}, {'s', 476}, {'n', 424}, {'u', 352},
//     {'c', 345}, {'y', 321}, {'h', 292}, {'d', 285}, {'p', 267},
//     {'g', 231}, {'m', 230}, {'b', 206}, {'f', 160}, {'k', 156},
//     {'w', 150}, {'v', 115}, {'x',  29}, {'z',  27}, {'q',  22},
//     {'j',  21}
// };

// int score(const std::string word) {
//     int returnScoreThingNum;
//     for (char letter : word) {
//         returnScoreThingNum += letterOccurences.at(letter);
//     }
//     return returnScoreThingNum;
// }

// /**
//  * @brief choose list of words that has a single word with the lowest score
//  * 
//  * @return int 
//  */
// int main() {
//     std::vector<std::vector<std::string>> savedWords;
//     int lowestMinScore = 99999;
//     for (auto& set : bestWords) {
//         //Sorts the scores from highest to lowest
//         std::sort(set.begin(), set.end(), [](const std::string& a, const std::string& b) -> bool { 
//             return score(a) > score(b);
//         });
//         int minScore = score(set[3]);
//         if (minScore < lowestMinScore) {
//             lowestMinScore = minScore;
//             savedWords.clear();
//             //Save these words
//             savedWords.push_back(set);
//         } else if (minScore == lowestMinScore)
//             savedWords.push_back(set);
//     }
//     for (std::vector<std::string>& vec : savedWords) {
//         for (std::string word : vec) {
//             std::cout << word << ' ';
//         }
//         std::cout << '\n';
//     }
//     std::cin.ignore();
//     return 0;
// }

// //Best 4 letter words in order: brame -> flint -> podgy -> shuck