#include "../include/ui.h"
#include "../include/quiz.h"
#include "../include/utils.h"
#include <cstdint>
#include <string>
#include <algorithm>
#include <iostream>

#define MARGIN 10
#define WIDTH 250
#define HEIGHT 300

void mainWindow::onItemSetup(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	listItem->set_child(*Gtk::make_managed<Gtk::Label>(""));
}

void bindWithStrings(const Glib::RefPtr<Gtk::ListItem> listItem, Glib::RefPtr<Gtk::StringList> strings)
{
	auto position = listItem->get_position();
	if (position==GTK_INVALID_LIST_POSITION) return;
	((Gtk::Label*)listItem->get_child())->set_label(strings->get_string(position));
}

void mainWindow::onMenuItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	bindWithStrings(listItem, quizStrings);
}

void mainWindow::onResultItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	bindWithStrings(listItem, resultStrings);
}

void mainWindow::onQuestionItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	bindWithStrings(listItem, questionStrings);
}

void mainWindow::onAnswerItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	bindWithStrings(listItem, answerStrings);
}

void mainWindow::initQuiz()
{
	id = quizSelectionModel->get_selected();
	if (id==GTK_INVALID_LIST_POSITION) return;
	openQuizMenu();
}

void mainWindow::openQuizMenu()
{
	current = 0;
	total = testQuestionTotal(availableQuizes[id]);
	set_title(quizStrings->get_string(availableQuizes[id]));
	updateContents();

	set_child(textButtonSplit);
}

void mainWindow::restartQuiz()
{
	testProgressRemove(availableQuizes[id]);
	openQuizMenu();
}

void mainWindow::openResultMenu()
{
	id = 0;
	set_title("Results");
	updateResultMenuSearch();
	set_child(resultListButtonBox);
}

void mainWindow::openAnswerMenu()
{
	id = resultSelectionModel->get_selected();
	if (id==GTK_INVALID_LIST_POSITION) return;
	showAnswerMenu();
}

void mainWindow::showAnswerMenu()
{
	questionStrings->splice(0, questionStrings->get_n_items(), {});
	answerStrings->splice(0, answerStrings->get_n_items(), {});
	for (int i = 0; i<testQuestionTotal(availableQuizes[id]); ++i)
	{
		questionStrings->append(testQuestionName(availableQuizes[id], i));
		answerStrings->append(testQuestionOptions(availableQuizes[id], i)[testProgressAnswer(availableQuizes[id], i)]);
	}
	set_title("Result View");
	set_child(answerListBackBox);
}

void mainWindow::showMainMenu()
{
	id = 0;
	set_title("Main Menu");
	updateMainMenuSearch();
	set_child(mainMenuBox);
}

void mainWindow::updateContents()
{
	if (total==current)
	{
		testProgressSave(availableQuizes[id], answerIdsList);
		answerIdsList.clear();
		showAnswerMenu();
		return;
	}
	
	string questionText;
	array<string, 4> optionsText;
	questionText = testQuestionName(availableQuizes[id], current);
	optionsText = testQuestionOptions(availableQuizes[id], current);

	progress.set_label(getProgressString(current, total));

	// set question
	question.set_label(questionText);

	// set button text
	for (int i = 0; i<4; ++i)
		options[i].set_label(optionsText[i]);
}

void mainWindow::updateMainMenuSearch()
{
	quizStrings->splice(0, quizStrings->get_n_items(), {});
	vector<int> uncompletedTests = testProgressUncompleted();
	availableQuizes.clear();
	for (size_t i = 0; i<uncompletedTests.size(); ++i)
	{
		if (searchQuizQuestions(uncompletedTests[i], quizSearchBuffer->get_text().c_str()).size()) // TEMP
		{
			availableQuizes.push_back(i);
			quizStrings->append(testName(uncompletedTests[i]));
		}
	}
}

void mainWindow::updateResultMenuSearch()
{
	resultStrings->splice(0, resultStrings->get_n_items(), {});
	vector<int> uncompletedTests = testProgressUncompleted();
	availableQuizes.clear();
	for (int i = 0; i<testTotal(); ++i)
	{
		if (find(uncompletedTests.begin(), uncompletedTests.end(), i)==uncompletedTests.end())
		{
			if (searchQuizQuestions(i, resultSearchBuffer->get_text().c_str()).size())
			{
				availableQuizes.push_back(i);
				resultStrings->append(testName(i));
			}
		}
	}
}

void mainWindow::handleInput(uint8_t button)
{
	++current;
	answerIdsList.push_back(button);
	updateContents();
}

void mainWindow::handleButton1()
{
	handleInput(0);
}

void mainWindow::handleButton2()
{
	handleInput(1);
}

void mainWindow::handleButton3()
{
	handleInput(2);
}

void mainWindow::handleButton4()
{
	handleInput(3);
}

mainWindow::mainWindow() : resultButton("View results"), startQuiz("Start quiz"), mainMenuBox(Gtk::Orientation::VERTICAL, 5), textButtonSplit(Gtk::Orientation::VERTICAL, 5), resultListButtonBox(Gtk::Orientation::VERTICAL, 5), resultBackButton("Back"), selectQuiz("View answers"), answerListBackBox(Gtk::Orientation::VERTICAL, 5), questionAnswerBox(Gtk::Orientation::HORIZONTAL, 5), answerBackButton("Back"), restartQuizButton("Restart quiz")
{
	// MAIN WINDOW

	// layout
	listScroll.set_child(quizList);
	listScroll.set_margin(MARGIN);
	listScroll.set_expand();

	quizSearchBar.set_placeholder_text("Search for questions");
	quizSearchBuffer = quizSearchBar.get_buffer();
	resultButton.set_margin(MARGIN);
	mainMenuBox.append(resultButton);
	quizSearchBar.set_margin(MARGIN);
	mainMenuBox.append(quizSearchBar);
	mainMenuBox.append(listScroll);
	mainMenuBox.append(startQuiz);
	startQuiz.set_expand();
	startQuiz.set_margin(MARGIN);
	set_child(mainMenuBox);

	startQuiz.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::initQuiz));
	quizSearchBar.signal_changed().connect(sigc::mem_fun(*this, &mainWindow::updateMainMenuSearch));
	resultButton.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::openResultMenu));

	// list
	
	quizStrings = Gtk::StringList::create({});
	quizSelectionModel = Gtk::SingleSelection::create(quizStrings);
	quizSelectionModel->set_autoselect(true);
	quizList.set_model(quizSelectionModel);
	
	auto quizFactory = Gtk::SignalListItemFactory::create();
	quizFactory->signal_setup().connect(sigc::mem_fun(*this, &mainWindow::onItemSetup));
	quizFactory->signal_bind().connect(sigc::mem_fun(*this, &mainWindow::onMenuItemBind));	
	quizList.set_factory(quizFactory);

	updateMainMenuSearch();

	// content
	set_title("Main Menu");
	set_default_size(WIDTH, HEIGHT);

	// QUIZ WINDOW
	
	// layout
	textButtonSplit.append(progress);
	progress.set_margin(MARGIN);
	progress.set_expand();
	textButtonSplit.append(question);
	question.set_expand();
	question.set_margin(MARGIN);
	textButtonSplit.append(buttonGrid);
	for (int i = 0; i<4; ++i)
	{
		buttonGrid.attach(options[i], i/2, i%2);
		options[i].set_expand();
		options[i].set_margin(MARGIN);
	}

	set_resizable(false);

	// click handlers
	options[0].signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::handleButton1));
	options[1].signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::handleButton2));
	options[2].signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::handleButton3));
	options[3].signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::handleButton4));

	// results (select quiz)
	// layout
	
	resultBackButton.set_expand();
	resultListButtonBox.append(resultBackButton);
	resultBackButton.set_margin(MARGIN);

	resultSearchBar.set_placeholder_text("Search");
	resultSearchBuffer = resultSearchBar.get_buffer();
	resultSearchBar.set_expand();
	resultSearchBar.set_margin(MARGIN);
	resultListButtonBox.append(resultSearchBar);

	selectQuiz.set_expand();
	selectQuiz.set_margin(MARGIN);
	
	resultListScroll.set_expand();
	resultListScroll.set_margin(MARGIN);
	resultListScroll.set_child(resultQuizList);

	// list

	resultStrings = Gtk::StringList::create({});
	resultSelectionModel = Gtk::SingleSelection::create(resultStrings);
	resultSelectionModel->set_autoselect(true);
	resultQuizList.set_model(resultSelectionModel);

	auto resultFactory = Gtk::SignalListItemFactory::create();
	resultFactory->signal_setup().connect(sigc::mem_fun(*this, &mainWindow::onItemSetup));
	resultFactory->signal_bind().connect(sigc::mem_fun(*this, &mainWindow::onResultItemBind));
	resultQuizList.set_factory(resultFactory);

	resultListButtonBox.append(resultListScroll);
	resultListButtonBox.append(selectQuiz);

	resultBackButton.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::showMainMenu));
	selectQuiz.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::openAnswerMenu));
	resultSearchBar.signal_changed().connect(sigc::mem_fun(*this, &mainWindow::updateResultMenuSearch));

	// results (answers)
	
	answerBackButton.set_margin(MARGIN);
	answerBackButton.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::openResultMenu));
	answerBackButton.set_expand();
	answerListBackBox.append(answerBackButton);

	// list

	questionStrings = Gtk::StringList::create({});
	questionSelectionModel = Gtk::NoSelection::create(questionStrings);
	questionList.set_model(questionSelectionModel);

	auto questionFactory = Gtk::SignalListItemFactory::create();
	questionFactory->signal_setup().connect(sigc::mem_fun(*this, &mainWindow::onItemSetup));
	questionFactory->signal_bind().connect(sigc::mem_fun(*this, &mainWindow::onQuestionItemBind));
	questionList.set_factory(questionFactory);
	
	answerStrings = Gtk::StringList::create({});
	answerSelectionModel = Gtk::NoSelection::create(answerStrings);
	answerList.set_model(answerSelectionModel);

	auto answerFactory = Gtk::SignalListItemFactory::create();
	answerFactory->signal_setup().connect(sigc::mem_fun(*this, &mainWindow::onItemSetup));
	answerFactory->signal_bind().connect(sigc::mem_fun(*this, &mainWindow::onAnswerItemBind));
	answerList.set_factory(answerFactory);

	questionAnswerBox.append(questionList);
	questionAnswerBox.append(answerList);

	questionAnswerScrolledWindow.set_child(questionAnswerBox);
	questionAnswerScrolledWindow.set_margin(MARGIN);
	questionAnswerScrolledWindow.set_expand();
	answerListBackBox.append(questionAnswerScrolledWindow);

	restartQuizButton.set_margin(MARGIN);
	restartQuizButton.set_expand();
	restartQuizButton.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::restartQuiz));
	answerListBackBox.append(restartQuizButton);
}

mainWindow::~mainWindow()
{

}
