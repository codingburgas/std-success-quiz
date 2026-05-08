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
		Gtk::Button startQuiz;
		Gtk::Entry quizSearchBar;
		Gtk::Box mainMenuBox;
		Gtk::ScrolledWindow listScroll;
		Glib::RefPtr<Gtk::SingleSelection> quizSelectionModel;
		Glib::RefPtr<Gtk::StringList> quizStrings;
		Glib::RefPtr<Gtk::EntryBuffer> quizSearchBuffer;

		void onItemSetup(const Glib::RefPtr<Gtk::ListItem>& listItem);
		void onMenuItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem);

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

		void onResultItemBind();

		// result view (choosing questions)

		Gtk::Box answerListBackBox;
		Gtk::Button answerBackButton;
		Gtk::ListView answerList;
		Gtk::ScrolledWindow answerScrolledWindow;
		Glib::RefPtr<Gtk::SingleSelection> answerSelectionModel;
		Glib::RefPtr<Gtk::StringList> answerStrings;

		void onAnswerItemBind();
		
		void openResultMenu(); // main -> result
		void openAnswerMenu(); // result/quiz -> answer
		void initQuiz(); // main -> quiz
		void showMainMenu(); // result/quiz -> main
	private:
		int id;
		int current;
		int total;
		vector<uint8_t> answerIdsList;
};
#endif
