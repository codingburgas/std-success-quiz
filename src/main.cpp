#include <gtkmm/application.h>
#include "../include/ui.h"

int main(int argc, char **argv)
{
	auto app = Gtk::Application::create("std.success.quiz");

	return app->make_window_and_run<mainWindow>(argc, argv);
}
