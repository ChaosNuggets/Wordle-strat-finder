// #include "words.h"
// #include <fstream>

// int main() {
//     std::ofstream file_out;

//     file_out.open("words.txt", std::ios_base::app);
//     file_out << '{';
//     for (auto& vec : words) {
//         for (auto& vec2 : vec) {
//             for (std::string word: vec2) {
//                 file_out << '"' << word << "\",";
//             }
//         }
//     }
//     file_out << '}';
//     file_out.close();
//     return 0;
// }