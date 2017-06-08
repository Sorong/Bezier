#include <QKeyEvent>
#include <QMessageBox>
#include <qtextstream.h>
#include "mainview.hpp"



MainView::MainView(QWidget* parent)
	: QMainWindow(parent) {
	ui.setupUi(this);
	this->setMinimumHeight(500);
	//this->setMaximumHeight(375);
	//QObject::connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), ui.openGLWidget, SLOT(setT(int)));
	QObject::connect(ui.t_slider_, SIGNAL(valueChanged(int)), this, SLOT(sliderToLabel(int)));
	QObject::connect(ui.add_button_, SIGNAL(pressed()), this, SLOT(addCoordinates()));
	QObject::connect(ui.show_sublines_, SIGNAL(toggled(bool)), ui.glview, SLOT(toggleSublineMode(bool)));
	QObject::connect(ui.show_derivation_, SIGNAL(toggled(bool)), ui.glview, SLOT(toggleDerivateMode(bool)));
	QObject::connect(ui.raise_elevation_, SIGNAL(pressed()), this, SLOT(raiseElevation()));
	QObject::connect(ui.glview, SIGNAL(clickedVertex()), this, SLOT(clickedVertex()));
	menuBar()->addMenu("Ansicht");
}

MainView::~MainView() {

}

void MainView::sliderToLabel(int i) const {
	const float paramToFloat = i/100.0f;
	QString float_as_string;// = QString::number(i / 10.0f, 'g', 4);
	float_as_string.sprintf("%.2f", paramToFloat);
	this->ui.t_label_->setText("t: " + float_as_string);
	this->ui.glview->setT(paramToFloat);
}

void MainView::addCoordinates() const {
	QVector4D coordinates = { static_cast<float>(this->ui.x_coord_->value()), static_cast<float>(this->ui.y_coord_->value()), 0, 1};
	coordinates *= this->ui.weight_->value();
	if(this->ui.glview->addCoordinate(coordinates)) {
		this->addToList(coordinates);
	} else {
		QMessageBox messageBox;
		messageBox.critical(nullptr, "Error", QString("Korrekte Darstellung nicht möglich. Bitte löschen Sie Punkte"));
		messageBox.setFixedSize(500, 200);
	}
}

void MainView::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Delete && !ui.list_widget_->selectedItems().isEmpty()) {
		auto selected = ui.list_widget_->selectionModel()->selectedIndexes();
		auto i = selected.at(0).row();
		ui.list_widget_->takeItem(i);
		ui.glview->removeCoordinateByIndex(i);

	} else {
		this->ui.glview->keyPressEvent(event);
	}
}

void MainView::mousePressEvent(QMouseEvent* event) {
	qDebug() << "mainviewmousepress";
}

void MainView::mouseMoveEvent(QMouseEvent* event) {
	qDebug() << "mainviewmousemove";
}

void MainView::mouseReleaseEvent(QMouseEvent* event) {
	qDebug() << "mainviewmousepress";
}

void MainView::raiseElevation() const {
	this->ui.glview->raiseElevation();
	reloadList();
}

void MainView::clickedVertex() {
	qDebug() << "clicked";
}

void MainView::addToList(QVector4D coordinate) const {
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

void MainView::reloadList() const {
	auto points = this->ui.glview->getBasePoints();
	this->ui.list_widget_->clear();
	for (auto point : points) {
		this->addToList(point);
	}
}
