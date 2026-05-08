#include "../include/backend.h"
#include "../include/quiz.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

void saveQuizAnswers(int id, vector<uint8_t> answers) {
	ofstream file("progress.txt", ios::app);
	if (!file.is_open()) return;

	file << id;
	for (int i = 0; i < (int)answers.size(); i++) {
		file << " " << (int)answers[i];
	}
	file << endl;
}

vector<int> getUncompletedTestList() {
    const char* names[] = getQuizNameList();
    int totalTests = sizeof(names) / sizeof(names[0]);
    vector<bool> isCompleted(totalTests, false);
    ifstream file("progress.txt");
    if (file.is_open()) {
        int testId;
        while (file >> testId) {
            if (testId >= 0 && testId < totalTests) {
                isCompleted[testId] = true;
            }
            file.ignore(10000, '\n');
        }
    }
	
    vector<int> uncompleted;
    for (int i = 0; i < totalTests; i++) {
        if (isCompleted[i] == false) {
            uncompleted.push_back(i);
        }
    }
    return uncompleted;
}