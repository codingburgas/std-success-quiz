#ifndef QUIZ_H
#define QUIZ_H

#include <string>
#include <array>
#include <vector>
using namespace std;

string testName(int id);
string testQuestionName(int id, int index);
array<string, 4> testQuestionOptions(int id, int index);
int testTotal();

#endif