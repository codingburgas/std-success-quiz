#include "../include/ui.h"
#include "../include/quiz.h"
#include "../include/utils.h"
#include "../include/backend.h"
#include <cstdint>
#include <string>

#define MARGIN 10
#define WIDTH 250
#define HEIGHT 300

void mainWindow::onItemSetup(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	listItem->set_child(*Gtk::make_managed<Gtk::Label>(""));
}

void bindWithStrings(const Glib::RefPtr<Gtk::ListItem> *listItem, Glib::RefPtr<Gtk::StringList> strings)
{
	auto position = listItem.get_position();
	if (position==GTK_INVALID_POSITION) return;
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

void mainWindow::onAnswerItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem)
{
	bindWithStrings(listItem, answerStrings);
}

void mainWindow::initQuiz()
{
	id = quizSelectionModel->get_selected();
	current = 0;
	total = getTotalQuestions(id);
	set_title(quizStrings->get_string(id));
	updateContents();

	set_child(textButtonSplit);
}

void mainWindow::openResultMenu()
{
	id = 0;
	set_title("Results");
	set_child(resultListButtonBox);
}

void mainWindow::openAnswerMenu()
{
	id = resultSelectionModel->get_selected();
	//answerStrings TODO implement strings for answers
	set_title("Answers"); // TODO change?
	set_child(answerListBackBox);
}

void mainWindow::showMainMenu()
{
	saveQuizAnswers(id, answerIdsList);
	id = 0;
	set_title("Main Menu");
	set_child(mainMenuBox);
}

void mainWindow::updateContents()
{
	if (total==current)
	{
		showMainMenu(); // TODO show result screen
		return;
	}
	
	char *questionText, *optionsText[4];
	getQuizQuestionContent(id, current, questionText, optionsText);

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

void mainWindow::searchText()
{
	quizStrings = findTextInQuizQuestions(quizSearchBuffer.get_text());
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

mainWindow::mainWindow() : startQuiz("Start quiz"), mainMenuBox(Gtk::Orientation::VERTICAL, 5), textButtonSplit(Gtk::Orientation::VERTICAL, 5), resultListButtonBox(Gtk::Orientation::VERTICAL, 5), resultBackButton("Back"), selectQuiz("View answers"), resultViewListBackBox(Gtk::Orientation::VERTICAL, 5), answerBackButton("Back")
{
	// MAIN WINDOW

	// layout
	listScroll.set_child(quizList);
	listScroll.set_margin(MARGIN);
	listScroll.set_expand();

	quizSearchBar.set_placeholder_text("Search for questions");
	quizSearchBuffer = quizSearchBar.get_buffer();
	mainMenuBox.append(quizSearchBar);
	mainMenuBox.append(listScroll);
	mainMenuBox.append(startQuiz);
	startQuiz.set_expand();
	startQuiz.set_margin(MARGIN);
	set_child(mainMenuBox);

	startQuiz.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::initQuiz));
	quizSearchBar.signal_changed().connect(sigc::mem_fun(*this, &mainWindow::searchText));

	// list
	
	quizStrings = Gtk::StringList::create(getQuizNameList());
	quizSelectionModel = Gtk::SingleSelection::create(quizStrings);
	quizSelectionModel->set_autoselect(true);
	quizList.set_model(quizSelectionModel);
	
	auto quizFactory = Gtk::SignalListItemFactory::create();
	quizFactory->signal_setup().connect(sigc::mem_fun(*this, &mainWindow::onItemSetup));
	quizFactory->signal_bind().connect(sigc::mem_fun(*this, &mainWindow::onMenuItemBind));	
	quizList.set_factory(quizFactory);

	// content
	set_title("Main Menu");
	set_default_size(WIDTH, HEIGHT);

	// QUIZ WINDOW
	
	// layout
	textButtonSplit.append(progress);
	progress.set_margin(MARGIN);
	textButtonSplit.append(question);
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

	resultSearchBar.set_placeholder_text("Search for questions");
	resultSearchBuffer = resultSearchBar.get_buffer();
	resultSearchBar.set_expand();
	resultListButtonBox.append(resultSearchBar);

	selectQuiz.set_expand();
	
	resultListScroll.set_expand();
	resultListScroll.set_margin(MARGIN);
	resultListScroll.set_child(resultQuizList);

	// list

	resultStrings = Gtk::StringList::create({}); // TODO implement for only completed tests
	resultSelectionModel = Gtk::SingleSelection::create(resultStrings);
	resultSelectionModel->set_autoselect(true);
	resultQuizList.set_model(resultSelectionModel);

	auto resultFactory = Gtk::SignalListItemFactory::create();
	resultFactory->signal_setup().connect(sigc::mem_fun(*this, &mainWindow::onResultItemSetup));
	resultFactory->signal_bind().connect(sigc::mem_fun(*this, &mainWindow::onResultItemBind));
	resultQuizList.set_factory(resultFactory);

	resultButtonListBox.append(resultListScroll);
	resultButtonListBox.append(selectQuiz);

	selectQuiz.signal_clicked().connect(sigc::mem_fun(*this, &mainWindow::openResultMenu));

	// results (answers)
	
	resultViewListBackBox.append(answerBackButton);

	// list
	
	answerStrings = Gtk::StringList::create({}); // TODO when backend is ready
	answerSelectionModel = Gtk::NoSelection::create(answerStrings);
	answerSelectionModel->set_autoselect(true);
	answerList.set_model(answerSelectionModel);

	auto answerFactory = Gtk::SignalListItemFactory::create();
	answerFactory->signal_setup().connect(sigc::mem_fun(*this, &mainWindow::onAnswerItemSetup));
	answerFactory->signal_bind().connect(sigc::mem_fun(*this, &mainWindow::onAnswerItemBind));
	answerList.set_factory(resultFactory);
}

mainWindow::~mainWindow()
{

}
