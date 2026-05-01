#include "../include/ui.h"
#include <cstdint>

void quizWindow::updateContents()
{
	if (total==current)
	{
		// display results, close current window
		return;
	}
	
	char *questionText, *optionsText[4];
	correctOption = getQuizQuestionContent(id, current, questionText, optionsText);

	// set question
	question.set_label(questionText);

	// set button text
	for (int i = 0; i<4; ++i)
		options[i].set_label(optionsText[i]);
}

quizWindow::quizWindow()
{
	set_child(textButtonSplit);
	textButtonSplit.append(question);
	textButtonSplit.append(buttonGrid);
	for (int i = 0; i<4; ++i)
		buttonGrid.attach(options[i], i/2, i%2);

	options[0].signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &quizWindow::handleButton1)));
	options[1].signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &quizWindow::handleButton2)));
	options[2].signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &quizWindow::handleButton3)));
	options[3].signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &quizWindow::handleButton4)));

	id = getQuizId();
	current = 0;
	set_title(getQuizName(id))
	total = getTotalQuestion(id);
	updateContents();
}

void quizWindow::handleInput(uint8_t button)
{
	++current;
	if (button==correctOption) ++correct;
	updateContents();
}

void quizWindow::handleButton1()
{
	handleInput(0);
}

void quizWindow::handleButton2()
{
	handleInput(1);
}

void quizWindow::handleButton3()
{
	handleInput(2);
}

void quizWindow::handleButton4()
{
	handleInput(3);
}

quizWindow::~quizWindow()
{
	cleanUpQuizData();
}
