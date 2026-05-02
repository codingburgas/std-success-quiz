#include <cstdint>
#include <cstring>

uint8_t getQuizQuestionContent(int quizId, int questionId, char *&questionText, char *options[4])
{
	// testing
	questionText = new char[5];
	strcpy(questionText, "Ques");
	for (int i = 0; i<4; ++i)
	{
		options[i] = new char[5];
		strcpy(options[i], "Test");
	}
	return 1;
}
