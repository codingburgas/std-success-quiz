#ifndef QUIZ_H
#define QUIZ_H

#include <cstdint>
#include <vector>

// testing
#define getTotalQuestions(id) (2)
#define getQuizNameList(id) {"Testing 1", "Testing 2", "Testing 3", "Testing 4", "Testing 5", "Testing 6"}

<<<<<<< HEAD
void getQuizQuestionContent(int quizId, int questionId, char *&questionText, char *options[4]);
=======
uint8_t getQuizQuestionContent(int quizId, int questionId, char *&questionText, char *options[4]);
std::vector<int> searchQuizQuestions(int quizId, const char *text);
>>>>>>> 27e5683 (add quiz search function by question text)

#endif