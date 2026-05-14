#include <gtkmm/application.h>
#include "../include/ui.h"

#ifdef _WIN32 // WinMain
#include <windows.h>
#endif

#ifndef _WIN32
int main(int argc, char **argv)
#else
int WinMain(HINSTANCE hInstance, HINSTANCE hprevInstance, PSTR cmdline, int cmdshow) // used to hide console
#endif
{
	auto app = Gtk::Application::create("std.success.quiz");

	return app->make_window_and_run<mainWindow>(0, 0);
}
