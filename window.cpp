#include <QKeyEvent>
#include <QMessageBox>
#include "window.h"

Bezier::Bezier(QWidget* parent)
	: QMainWindow(parent) {
	ui.setupUi(this);
	this->setMinimumHeight(500);
	//this->setMaximumHeight(375);
	//QObject::connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), ui.openGLWidget, SLOT(setT(int)));
	QObject::connect(ui.t_slider_, SIGNAL(valueChanged(int)), this, SLOT(sliderToLabel(int)));
	QObject::connect(ui.add_button_, SIGNAL(pressed()), this, SLOT(addCoordinates()));
	QObject::connect(ui.show_sublines_, SIGNAL(toggled(bool)), ui.bezier, SLOT(toggleSublineMode()));
	QObject::connect(ui.raise_elevation_, SIGNAL(pressed()), this, SLOT(raiseElevation()));
	QObject::connect(ui.show_derivation_, SIGNAL(pressed()), this, SLOT(getHodograph()));
}

Bezier::~Bezier() {

}

void Bezier::sliderToLabel(int i) const {

	QString float_as_string;// = QString::number(i / 10.0f, 'g', 4);
	float_as_string.sprintf("%.2f", i / 10.0f);
	this->ui.t_label_->setText("t: " + float_as_string);
	this->ui.bezier->setT(i);
}

void Bezier::addCoordinates() const {
	QVector4D coords = {static_cast<float>(this->ui.x_coord_->value()), static_cast<float>(this->ui.y_coord_->value()), 0, 1};
	if(this->ui.bezier->addCoordinate(coords)) {
		this->addToList(coords);
	} else {
		QMessageBox messageBox;
		messageBox.critical(nullptr, "Error", QString("Korrekte Darstellung nicht möglich. Bitte löschen Sie Punkte"));
		messageBox.setFixedSize(500, 200);
	}
}

void Bezier::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Delete && !ui.list_widget_->selectedItems().isEmpty()) {
		auto selected = ui.list_widget_->selectionModel()->selectedIndexes();
		auto i = selected.at(0).row();
		ui.list_widget_->takeItem(i);
		ui.bezier->removeCoordinateByIndex(i);

	} else {
		this->ui.bezier->keyPressEvent(event);
	}
}

void Bezier::raiseElevation() const {
	this->ui.bezier->raiseElevation();
	reloadList();
}

void Bezier::getHodograph() const {
	this->ui.bezier->calculateHodograph();
	reloadList();
}

void Bezier::addToList(QVector4D coordinate) const {
	QString out;
	QTextStream stream(&out);
	stream.setRealNumberPrecision(2);
	stream.setRealNumberNotation(QTextStream::FixedNotation);
	stream << "( x: " << coordinate.x() << ", y: ";
	stream << coordinate.y() << ")";
	this->ui.list_widget_->addItem(out);
}

void Bezier::reloadList() const {
	auto points = this->ui.bezier->getBasePoints();
	this->ui.list_widget_->clear();
	for (auto point : points) {
		this->addToList(point);
	}
}
