#ifndef TEST_WORDS_H
#define TEST_WORDS_H

#include <vector>
#include <string>

// extern int lowestFailsAll;
extern int lowestFailsNotAnswerList;
extern int lowestFailsAnswerList;
extern int equivalentPermutations;
extern std::vector</*std::vector<*/std::string>/*>*/ bestPermutation;

void testPermutations(std::vector<std::string> firstWords);

#endif