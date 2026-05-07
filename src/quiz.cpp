#include "../include/quiz.h"
#include <cstdint>
#include <cstring>
#include <vector>

void getQuizQuestionContent(int quizId, int questionId, char *&questionText, char *options[4])
{
	// testing
	questionText = new char[5];
	strcpy(questionText, "Ques");
	for (int i = 0; i<4; ++i)
	{
		options[i] = new char[5];
		strcpy(options[i], "Test");
	}
}

std::vector<int> searchQuizQuestions(int quizId, const char *text)
{
	std::vector<int> matchingQuestions;
	if (text==nullptr)
	{
		return matchingQuestions;
	}

	for (int questionId = 0; questionId<getTotalQuestions(quizId); ++questionId)
	{
		char *questionText = nullptr;
		char *options[4] = {};
		getQuizQuestionContent(quizId, questionId, questionText, options);

		if (questionText!=nullptr && strstr(questionText, text)!=nullptr)
		{
			matchingQuestions.push_back(questionId);
		}

		delete[] questionText;
		for (int i = 0; i<4; ++i)
		{
			delete[] options[i];
		}
	}

	return matchingQuestions;
}
