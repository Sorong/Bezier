#include <QKeyEvent>
#include <QMessageBox>
#include <qtextstream.h>
#include <QVector4D>
#include "mainwindow.hpp"


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent) {
	ui.setupUi(this);
	this->setMinimumHeight(500);
	//this->setMaximumHeight(375);
	//QObject::connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), ui.openGLWidget, SLOT(setT(int)));
	QObject::connect(ui.t_slider_, SIGNAL(valueChanged(int)), this->controller, SLOT(sliderToLabel(int)));
	QObject::connect(ui.add_button_, SIGNAL(pressed()), this, SLOT(addCoordinates()));
	QObject::connect(ui.show_sublines_, SIGNAL(toggled(bool)), ui.bezier, SLOT(toggleSublineMode(bool)));
	QObject::connect(ui.show_derivation_, SIGNAL(toggled(bool)), ui.bezier, SLOT(toggleDerivateMode(bool)));
	QObject::connect(ui.raise_elevation_, SIGNAL(pressed()), this, SLOT(raiseElevation()));
}

MainWindow::~MainWindow() {

}

//void MainWindow::registerController(Controller& controller) {
//	this->controller = controller;
//}

void MainWindow::sliderToLabel(int i) const {
	const float paramToFloat = i/100.0f;
	QString float_as_string;// = QString::number(i / 10.0f, 'g', 4);
	float_as_string.sprintf("%.2f", paramToFloat);
	this->ui.t_label_->setText("t: " + float_as_string);
	this->ui.bezier->setT(paramToFloat);
}

void MainWindow::addCoordinates() const {
	QVector4D coords = { static_cast<float>(this->ui.x_coord_->value()), static_cast<float>(this->ui.y_coord_->value()), 0, 1};
	coords *= this->ui.weight_->value();
	if(this->ui.bezier->addCoordinate(coords)) {
		this->addToList(coords);
	} else {
		QMessageBox messageBox;
		messageBox.critical(nullptr, "Error", QString("Korrekte Darstellung nicht m�glich. Bitte l�schen Sie Punkte"));
		messageBox.setFixedSize(500, 200);
	}
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Delete && !ui.list_widget_->selectedItems().isEmpty()) {
		auto selected = ui.list_widget_->selectionModel()->selectedIndexes();
		auto i = selected.at(0).row();
		ui.list_widget_->takeItem(i);
		ui.bezier->removeCoordinateByIndex(i);

	} else {
		this->ui.bezier->keyPressEvent(event);
	}
}

void MainWindow::raiseElevation() const {
	this->ui.bezier->raiseElevation();
	reloadList();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event) {

	reloadList();
}

void MainWindow::addToList(QVector4D coordinate) const {
	QString out;
	QTextStream stream(&out);
	stream.setRealNumberPrecision(2);
	stream.setRealNumberNotation(QTextStream::FixedNotation);
	auto w = coordinate.w();
	if(coordinate.w() != 0) {
		coordinate /= coordinate.w();
	}
	stream << "( x: " << coordinate.x() << ", y: " << coordinate.y() << ", Gewichtung: " << w << ")";
	this->ui.list_widget_->addItem(out);
}

void MainWindow::reloadList() const {
	auto points = this->ui.bezier->getBasePoints();
	this->ui.list_widget_->clear();
	for (auto point : points) {
		this->addToList(point);
	}
}
