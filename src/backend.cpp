#include "../include/backend.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>
#include <sstream>
#include <unordered_map>

using namespace std;

void saveQuizAnswers(int id, vector<uint8_t> answers) {
	ofstream file("progress.txt", ios::app);
	if (!file.is_open()) return;

	file << id;
	for (int i = 0; i < (int)answers.size(); i++) {
		file << " " << (int)answers[i];
	}
	file << endl;
	file.close();
}

vector<uint8_t> loadQuizAnswers(int id){
	ifstream file("progress.txt");
	if (!file.is_open()) return vector<uint8_t>();

	int testId;
	while (file >> testId) {
		if (testId == id) {
			vector<uint8_t> answers;
			int ans;
			while (file.peek() != '\n' && file.peek() != EOF && file >> ans) {
				answers.push_back((uint8_t)ans);
			}
			file.close();
			return answers;
		}
		file.ignore(10000, '\n');
	}
	file.close();
	return vector<uint8_t>();
}

vector<int> getUncompletedTestList() {
    int totalTests = getTotalQuizes();
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

void removeQuizFromSave(int id) {
    ifstream inFile("progress.txt");
    if (!inFile.is_open()) return;

    vector<string> lines;
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        int testId;
        if (ss >> testId) {
            if (testId != id) {
                lines.push_back(line);
            }
        }
    }
    inFile.close();

    ofstream outFile("progress.txt");
    if (!outFile.is_open()) return;

    for (const auto& l : lines) {
        outFile << l << endl;
    }
    outFile.close();
}

static vector<Test> g_tests = {
    {
        "Safety Basics",
        {
            { "What is the first step in safety?", { "Stop", "Think", "Run", "Hide" } },
            { "Who to call in emergency?", { "Friend", "Supervisor", "Nobody", "Mail" } }
        }
    },
    {
        "Protocol Quiz",
        {
            { "What is protocol A?", { "Option1", "Option2", "Option3", "Option4" } },
            { "How often to check logs?", { "Daily", "Weekly", "Monthly", "Never" } }
        }
    }
};

string getTestName(int id)
{
    if (id < 0 || id >= static_cast<int>(g_tests.size())) return string();
    return g_tests[id].name;
}

TestQuestion getTestQuestion(int id, int index)
{
    TestQuestion empty;
    if (id < 0 || id >= static_cast<int>(g_tests.size())) return empty;
    const auto& qs = g_tests[id].questions;
    if (index < 0 || index >= static_cast<int>(qs.size())) return empty;
    return qs[index];
}

int getTotalQuizes()
{
    return static_cast<int>(g_tests.size());
}

int getTotalQuestions(int quizId)
{
	return (int)g_tests[quizId].questions.size();
}
