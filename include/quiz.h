#ifndef QUIZ_H
#define QUIZ_H

#include <cstdint>

// testing
#define getQuizId() (0) 
#define getQuizName(id) "Testing"
#define cleanUpQuizData()
#define getTotalQuestions(id) (2)

uint8_t getQuizQuestionContent(int quizId, int questionId, char *&questionText, char *options[4]);

#endif
