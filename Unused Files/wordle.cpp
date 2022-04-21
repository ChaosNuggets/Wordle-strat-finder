// // It doesn't tell you the index of the colored tiles but whatever

// #include <random>
// #include <iostream>
// #include <fstream>

// const int numberOfWords = 12947;

// void gotoLine(std::ifstream& fin, unsigned int num){
//     fin.seekg(std::ios::beg);
//     for(int i = 0; i < num - 1; i++){
//         fin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
//     }
// }

// bool isValid(std::ifstream& fin, std::string word) {
//     std::string currentWord;
//     fin.seekg(std::ios::beg);
//     for(int i = 0; i < numberOfWords - 1; i++){
//         fin >> currentWord;
//         if (word == currentWord)
//             return true;
//     }
//     return false;
// }

// int main() {
//     std::random_device device;
//     std::mt19937 generator(device());
//     std::uniform_int_distribution<int> distribution(1, numberOfWords);

//     std::string answer;
//     std::ifstream fin("words.txt");
//     if (fin.is_open()) {
//         gotoLine(fin, distribution(generator));
//         fin >> answer;
//         // answer = "faves";
//     } else
//         throw std::runtime_error("file is not open");
//     bool hasWon = false;
//     std::cout << "guess something\n";
//     for (int i = 0; i < 6; i++) {
//         std::string input;
//         while (true) {
//             getline(std::cin, input);
//             if (input == answer) {
//                 hasWon = true;
//                 break;
//             }
//             //Tests if it's a valid word
//             if (isValid(fin, input))
//                 break;
//             else
//                 std::cout << input << " is not a valid word\n";
//         }
//         if (hasWon)
//             break;
//         for (int j = 0; j < 5; j++) {
//             bool isOrange = false;
//             bool isGreen = false;
//             for (int k = 0; k < 5; k++) {
//                 if (input[j] == answer[k]) {
//                     if (j == k) {
//                         isGreen = true;
//                         break;
//                     } else {
//                         isOrange = true;
//                     }
//                 }
//             }
//             if (isGreen)
//                 std::cout << input[j] << " is green\n";
//             else if (isOrange)
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