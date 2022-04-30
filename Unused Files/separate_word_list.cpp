// #include <algorithm>
// #include "words.h"
// #include <fstream>

// int main() {
//     std::ofstream fout;
//     fout.open("loggo.txt", std::ios_base::app);
//     std::sort(words.begin(), words.end());
//     fout << "{{";
//     char firstChar = 'a';
//     char secondChar = 'a';
//     for (std::string word : words) {
//         int firstDifference = word[0] - firstChar;
//         if (firstDifference > 0) {
//             for (int i = 0; i < firstDifference; i++) {
//                 fout << "}},\n{{";
//             }
//             firstChar = word[0];
//             secondChar = 'a';
//         }
//         int secondDifference = word[1] - secondChar;
//         if (secondDifference > 0) {
//             for (int i = 0; i < secondDifference; i++) {
//                 fout << "}, {";
//             }
//             secondChar = word[1];
//         }
//         fout << '\"' << word << "\",";
//     }
//     fout << "}}";
//     fout.close();
//     return 0;
// }