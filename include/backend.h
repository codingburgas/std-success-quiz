#ifndef BACKEND_H
#define BACKEND_H

#include <string>
#include <vector>
#include <array>
#include <cstdint>
using namespace std;

void saveQuizAnswers(int id, vector<uint8_t> answers);
vector<uint8_t> loadQuizAnswers(int id);
vector<int> getUncompletedTestList();
void removeQuizFromSave(int id);

struct TestQuestion
{
    string text;
    array<string, 4> options;
};

struct Test
{
    string name;
    vector<TestQuestion> questions;
};


string getTestName(int id);
TestQuestion getTestQuestion(int id, int index);
int getTotalQuizes();
int getTotalQuestions(int quizId);

#endif
