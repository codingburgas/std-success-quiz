#ifndef BACKEND_H
#define BACKEND_H

#include <string>
#include <vector>
#include <array>
using namespace std;

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
int getTotalQuestions(); 


void saveQuizAnswers(int id, const vector<uint8_t>& answers);
bool loadQuizAnswers(int id, vector<uint8_t>& answers);

#endif