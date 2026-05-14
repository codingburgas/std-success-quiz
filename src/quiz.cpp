#include "../include/backend.h"
#include "../include/quiz.h"
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstring>
#include <vector>
using namespace std;

static string toLowercase(string text)
{
	transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
		return static_cast<char>(tolower(c));
	});
	return text;
}

vector<int> searchQuizQuestions(int quizId, const char *text)
{
	vector<int> matchingQuestions;
	if (text==nullptr)
	{
		return matchingQuestions;
	}

	string searchText = toLowercase(text);
	string quizText = toLowercase(testName(quizId));

	for (int questionId = 0; questionId<getTotalQuestions(quizId); ++questionId)
	{
		string questionText = toLowercase(testQuestionName(quizId, questionId));

		if ((questionText.find(searchText)!=string::npos)||(quizText.find(searchText)!=string::npos))
		{
			matchingQuestions.push_back(questionId);
			continue;
		}
	}

	return matchingQuestions;
}

vector<int> testProgressUncompleted()
{
	return getUncompletedTestList();
}

void testProgressSave(int id, vector<uint8_t> answers)
{
	saveQuizAnswers(id, answers);
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

int testQuestionTotal(int id)
{
	return getTotalQuestions(id);
}

int testTotal()
{
	return getTotalQuizes();
}

uint8_t testProgressAnswer(int quizId, int questionId)
{
	vector<uint8_t> answers = loadQuizAnswers(quizId);
	return answers.size()<questionId?0:answers[questionId];
}
