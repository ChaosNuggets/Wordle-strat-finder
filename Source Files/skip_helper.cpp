#include "skip_helper.h"

//This list is in order of most common -> least common
const std::vector<char> firstDimensionOrder = {
    'e', 'a', 'r', 'o', 't',
    'l', 'i', 's', 'n', 'u',
    'c', 'y', 'h', 'd', 'p',
    'g', 'm', 'b', 'f', 'k',
    'w', 'v', 'x', 'z', 'q',
    'j'
};

char alphaPlaceToChar(const int place) {
    return char(place + 97);
}

// int charToAlphaPlace(const char letter) {
//     return int(letter) - 97;
// }