#ifndef BACKEND_H
#define BACKEND_H

#include <vector>
#include <cstdint>

using namespace std;

void saveQuizAnswers(int id, vector<uint8_t> answers);
vector<uint8_t> loadQuizAnswers(int id);
vector<int> getUncompletedTestList();

#endif
