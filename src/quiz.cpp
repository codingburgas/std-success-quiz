#include "../include/backend.h"
#include "../include/quiz.h"
#include <cstdint>
#include <cstring>
#include <vector>
using namespace std;

vector<int> searchQuizQuestions(int quizId, const char *text)
{
	vector<int> matchingQuestions;
	string quizText = testName(quizId);
	if (text==nullptr)
	{
		return matchingQuestions;
	}

	for (int questionId = 0; questionId<getTotalQuestions(quizId); ++questionId)
	{
		string questionText = testQuestionName(quizId, );

		if ((questionText.find(text)!=-1)||(quizText.find(text)!=-1))
		{
			matchingQuestions.push_back(questionId);
			continue;
		}
	}

	return matchingQuestions;
}

string testName(int id)
{
	return getTestName(id);
}

string testQuestionName(int id, int index)
{
	return getTestQuestion(id, index).text;
}

array<string, 4> testQuestionOptions(int id, int index)
{
	return getTestQuestion(id, index).options;
}

int testTotal()
{
	return getTotalQuizes();
}
