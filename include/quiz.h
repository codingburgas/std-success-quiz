#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <array>
#include <vector>
#include <cstdint>
using namespace std;

string testName(int id);
string testQuestionName(int id, int index);
array<string, 4> testQuestionOptions(int id, int index);
int testQuestionTotal(int id);
int testTotal();
uint8_t testProgressAnswer(int quizId, int questionId);
vector<int> testProgressUncompleted();

vector<int> searchQuizQuestions(int quizId, const char *text);
void testProgressSave(int id, vector<uint8_t> answers);
void testProgressRemove(int quizId);

#endif
