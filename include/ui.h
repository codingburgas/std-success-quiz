#ifndef UI_H
#define UI_H

#include <cstdint>
#include <vector>
#include <gtkmm.h>

using namespace std;

class mainWindow : public Gtk::Window
{
	public:
		mainWindow();
		~mainWindow();

	protected:
		// main menu window
		Gtk::ListView quizList;
		Gtk::Button resultButton;
		Gtk::Button startQuiz;
		Gtk::Entry quizSearchBar;
		Gtk::Box mainMenuBox;
		Gtk::ScrolledWindow listScroll;
		Glib::RefPtr<Gtk::SingleSelection> quizSelectionModel;
		Glib::RefPtr<Gtk::StringList> quizStrings;
		Glib::RefPtr<Gtk::EntryBuffer> quizSearchBuffer;

		void onItemSetup(const Glib::RefPtr<Gtk::ListItem>& listItem);
		void onMenuItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem);
		
		void updateMainMenuSearch();

		// quiz window

		Gtk::Box textButtonSplit;
		Gtk::Grid buttonGrid;
		Gtk::Label question;
		Gtk::Label progress;
		Gtk::Button options[4];

		void handleButton1();
		void handleButton2();
		void handleButton3();
		void handleButton4();
		void handleInput(uint8_t button);

		void updateContents();

		// result view (choosing test)

		Gtk::Box resultListButtonBox;
		Gtk::Button resultBackButton;
		Gtk::Entry resultSearchBar;
		Gtk::ListView resultQuizList;
		Gtk::ScrolledWindow resultListScroll;
		Gtk::Button selectQuiz;
		Glib::RefPtr<Gtk::SingleSelection> resultSelectionModel;
		Glib::RefPtr<Gtk::StringList> resultStrings;
		Glib::RefPtr<Gtk::EntryBuffer> resultSearchBuffer;

		void onResultItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem);
		void updateResultMenuSearch();

		// result view (choosing questions)

		Gtk::Box answerListBackBox;
		Gtk::Box questionAnswerBox;
		Gtk::Button answerBackButton;
		Gtk::ListView questionList;
		Gtk::ListView answerList;
		Gtk::ScrolledWindow questionAnswerScrolledWindow;
		Glib::RefPtr<Gtk::NoSelection> questionSelectionModel;
		Glib::RefPtr<Gtk::NoSelection> answerSelectionModel;
		Glib::RefPtr<Gtk::StringList> questionStrings;
		Glib::RefPtr<Gtk::StringList> answerStrings;
		Gtk::Button restartQuizButton;

		void onQuestionItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem);
		void onAnswerItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem);
		void restartQuiz();
		
		void openResultMenu(); // main -> result
		void openAnswerMenu(); // result/quiz -> answer
		void initQuiz(); // callback to get id
		void openQuizMenu(); // main -> quiz
		void showMainMenu(); // result/quiz -> main
		void showAnswerMenu(); // for saving id
	private:
		guint id;
		int current;
		int total;
		vector<uint8_t> answerIdsList;
		vector<int> availableQuizes;
};
#endif
