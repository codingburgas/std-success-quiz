#ifndef UI_H
#define UI_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>
#include <gtkmm/grid.h>
#include <gtkmm/box.h>
#include <cstdint>

class quizWindow : public Gtk::Window
{
	public:
		quizWindow();
		~quizWindow();

	protected:
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

	private:
		uint8_t correctOption;
		int correct;
		int id;
		int current;
		int total;
};

#endif
