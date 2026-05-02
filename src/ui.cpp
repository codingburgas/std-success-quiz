#include "../include/ui.h"
#include "../include/quiz.h"
#include "../include/utils.h"
#include <cstdint>
#include <iostream>
#include <string>

void quizWindow::updateContents()
{
	if (total==current)
	{
		std::cout << correct;
		close();
		return;
	}
	
	char *questionText, *optionsText[4];
	correctOption = getQuizQuestionContent(id, current, questionText, optionsText);

	progress.set_label(getProgressString(current, total));

	// set question
	question.set_label(questionText);
	delete questionText;

	// set button text
	for (int i = 0; i<4; ++i)
	{
		options[i].set_label(optionsText[i]);
		delete optionsText[i];
	}

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

quizWindow::quizWindow()
{
	// layout
	textButtonSplit = Gtk::Box(Gtk::Orientation::VERTICAL, 5);
	set_child(textButtonSplit);
	textButtonSplit.append(progress);
	progress.set_margin(15);
	textButtonSplit.append(question);
	question.set_margin(15);
	textButtonSplit.append(buttonGrid);
	for (int i = 0; i<4; ++i)
	{
		buttonGrid.attach(options[i], i/2, i%2);
		options[i].set_margin(15);
	}

	set_resizable(false);

	// click handlers
	options[0].signal_clicked().connect(sigc::mem_fun(*this, &quizWindow::handleButton1));
	options[1].signal_clicked().connect(sigc::mem_fun(*this, &quizWindow::handleButton2));
	options[2].signal_clicked().connect(sigc::mem_fun(*this, &quizWindow::handleButton3));
	options[3].signal_clicked().connect(sigc::mem_fun(*this, &quizWindow::handleButton4));

	// quiz parameter setup
	id = getQuizId();
	current = 0;
	correct = 0;
	set_title(getQuizName(id));
	total = getTotalQuestions(id);
	updateContents();
}

quizWindow::~quizWindow()
{
	cleanUpQuizData();
}
