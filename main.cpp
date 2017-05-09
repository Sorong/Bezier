#include <QtWidgets/QApplication>
#include "window.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Bezier w;
	w.show();
	return a.exec();
}
