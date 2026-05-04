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
		Gtk::Box mainMenuBox;
		Gtk::ScrolledWindow listScroll;
		Glib::RefPtr<Gtk::SingleSelection> selectionModel;
		Glib::RefPtr<Gtk::StringList> quizStrings;

		void onItemSetup(const Glib::RefPtr<Gtk::ListItem>& listItem);
		void onItemBind(const Glib::RefPtr<Gtk::ListItem>& listItem);

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

		void initQuiz();
		void showMainMenu();
	private:
		int id;
		int current;
		int total;
		vector<uint8_t> answerIdsList;
};
#endif
