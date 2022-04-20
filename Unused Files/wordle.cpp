// #include "words.h"
// #include <random>
// #include <iostream>

// int main() {
//     std::random_device device;
//     std::mt19937 generator(device());
//     std::uniform_int_distribution<int> distribution(0, numberOfWords-1);

//     std::string answer = words[distribution(generator)];
//     bool hasWon = false;
//     std::cout << "running\n";
//     for (int i = 0; i < 6; i++) {
//         bool isValid = false;
//         std::string input;
//         while (isValid) {
//             getline(std::cin, input);
//             if (input == answer) {
//                 hasWon = true;
//                 break;
//             }
//             //Tests if it's a valid word
//             for (int i = 0; i < numberOfWords; i++) {
//                 if (input == words[i]) {
//                     isValid = true;
//                     break;
//                 }
//             }
//             if (!isValid)
//                 std::cout << input << " is not a valid word\n";
//         }
//         if (hasWon)
//             break;
//         for (int j = 0; j < 5; j++) {
//             bool isOrange = false;
//             for (int k = 0; k < 5; k++) {
//                 if (input[j] == answer[k]) {
//                     if (j == k) {
//                         std::cout << input[j] << " is green\n";
//                         break;
//                     } else {
//                         isOrange = true;
//                     }
//                 }
//             }
//             if (isOrange)
//                 std::cout << input[j] << " is orange\n";
//         }
//     }
//     if (hasWon)
//         std::cout << "you won!";
//     else
//         std::cout << "the correct word was " << answer;
//     std::cin.ignore();
//     return 0;
// }