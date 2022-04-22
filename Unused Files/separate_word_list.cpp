// #include <fstream>
// #include "const_words.h"
// #include <algorithm>

// int main() {
//     std::sort(constWords.begin(), constWords.end());
//     std::ofstream file_out;
//     file_out.open("a.txt", std::ios_base::app);
//     int i = 0;
//     char secondChar;
//     file_out << "{{";
//     secondChar = 'a';
//     for (; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'a') {
//             int difference = constWords[i][1] - secondChar;
//             if (difference != 0) {
//                 for (int i = 0; i < difference; i++) {
//                     file_out << "}, {";
//                 }
//                 secondChar = constWords[i][1];
//             }
//             file_out << '\"' << constWords[i] << "\",";
//         }
//         else
//             break;
//     }
//     file_out << "}},";
//     file_out.close();
//     file_out.open("b.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'b')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("c.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'c')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
    
//     file_out.open("d.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'd')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("e.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'e')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("f.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'f')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("g.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'g')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("h.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'h')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("i.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'i')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("j.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'j')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("k.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'k')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("l.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'l')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("m.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'm')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("n.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'n')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("o.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'o')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("p.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'p')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("q.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'q')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("r.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'r')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("s.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 's')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("t.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 't')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("u.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'u')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("v.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'v')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("w.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'w')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("x.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'x')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("y.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'y')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     file_out.open("z.txt", std::ios_base::app);
//     for (int i = 0; i < constWords.size(); i++) {
//         if (constWords[i][0] == 'z')
//             file_out << '\"' << constWords[i] << "\",";
//     }
//     file_out.close();
//     return 0;
// }