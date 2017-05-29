#include <QtWidgets/QApplication>
#include "mainview.hpp"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainView w;
	w.show();
	return a.exec();
}
