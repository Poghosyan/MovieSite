#include <QApplication>
#include "mainwin.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);  

	MainWin window;

	window.setWindowTitle("Movie Rental");
	window.show();

	return app.exec();
}