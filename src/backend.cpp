#include "../include/backend.h"
#include "../include/quiz.h"
#include <fstream>
#include <vector>
#include <string>
#include <cstdint>

using namespace std;

void saveQuizAnswers(int id, vector<uint8_t> answers)
{
	ofstream file("progress.txt", ios::app);
	if (!file.is_open()) return;

	file << id;
	for (int i = 0; i < (int)answers.size(); i++)
	{
		file << " " << (int)answers[i];
	}
	file << endl;
}

