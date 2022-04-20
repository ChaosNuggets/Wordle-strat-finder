// #include <algorithm>
// #include "words.h"
// #include <fstream>

// int main() {
//     std::ofstream file_out;
//     file_out.open("log0.txt", std::ios_base::app);
//     std::sort(words[0].begin(), words[0].end());
//     file_out << "{{";
//     char secondChar = 'a';
//     for (auto word : words[0]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log1.txt", std::ios_base::app);
//     std::sort(words[1].begin(), words[1].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[1]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log2.txt", std::ios_base::app);
//     std::sort(words[2].begin(), words[2].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[2]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log3.txt", std::ios_base::app);
//     std::sort(words[3].begin(), words[3].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[3]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log4.txt", std::ios_base::app);
//     std::sort(words[4].begin(), words[4].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[4]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log5.txt", std::ios_base::app);
//     std::sort(words[5].begin(), words[5].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[5]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log6.txt", std::ios_base::app);
//     std::sort(words[6].begin(), words[6].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[6]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log7.txt", std::ios_base::app);
//     std::sort(words[7].begin(), words[7].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[7]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log8.txt", std::ios_base::app);
//     std::sort(words[8].begin(), words[8].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[8]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log9.txt", std::ios_base::app);
//     std::sort(words[9].begin(), words[9].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[9]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log10.txt", std::ios_base::app);
//     std::sort(words[10].begin(), words[10].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[10]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log11.txt", std::ios_base::app);
//     std::sort(words[11].begin(), words[11].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[11]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log12.txt", std::ios_base::app);
//     std::sort(words[12].begin(), words[12].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[12]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log13.txt", std::ios_base::app);
//     std::sort(words[13].begin(), words[13].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[13]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log14.txt", std::ios_base::app);
//     std::sort(words[14].begin(), words[14].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[14]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log15.txt", std::ios_base::app);
//     std::sort(words[15].begin(), words[15].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[15]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log16.txt", std::ios_base::app);
//     std::sort(words[16].begin(), words[16].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[16]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log17.txt", std::ios_base::app);
//     std::sort(words[17].begin(), words[17].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[17]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log18.txt", std::ios_base::app);
//     std::sort(words[18].begin(), words[18].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[18]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log19.txt", std::ios_base::app);
//     std::sort(words[19].begin(), words[19].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[19]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log20.txt", std::ios_base::app);
//     std::sort(words[20].begin(), words[20].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[20]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log21.txt", std::ios_base::app);
//     std::sort(words[21].begin(), words[21].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[21]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log22.txt", std::ios_base::app);
//     std::sort(words[22].begin(), words[22].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[22]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log23.txt", std::ios_base::app);
//     std::sort(words[23].begin(), words[23].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[23]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
    
//     file_out.open("log24.txt", std::ios_base::app);
//     std::sort(words[24].begin(), words[24].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[24]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();

//     file_out.open("log25.txt", std::ios_base::app);
//     std::sort(words[25].begin(), words[25].end());
//     file_out << "{{";
//     secondChar = 'a';
//     for (auto word : words[25]) {
//         int difference = word[1] - secondChar;
//         if (difference != 0) {
//             for (int i = 0; i < difference; i++) {
//                 file_out << "}, {";
//             }
//             secondChar = word[1];
//         }
//         file_out << '\"' << word << "\",";
//     }
//     file_out << "}}";
//     file_out.close();
//     return 0;
// }