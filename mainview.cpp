#include <QKeyEvent>
#include <QMessageBox>
#include <qtextstream.h>
#include "mainview.hpp"



MainView::MainView(QWidget* parent)
	: QMainWindow(parent), clicked(nullptr) {
	ui.setupUi(this);
	this->setMinimumHeight(500);
	QObject::connect(ui.t_slider_, SIGNAL(valueChanged(int)), this, SLOT(sliderToTLabel(int)));
	QObject::connect(ui.s_slider_, SIGNAL(valueChanged(int)), this, SLOT(sliderToSLabel(int)));
	QObject::connect(ui.show_sublines_, SIGNAL(toggled(bool)), this, SLOT(deCasteljau(bool)));
	QObject::connect(ui.show_derivation_, SIGNAL(toggled(bool)), this, SLOT(derivate(bool)));
	QObject::connect(ui.raise_elevation_, SIGNAL(pressed()), this, SLOT(raiseElevation()));
	QObject::connect(ui.glview_, SIGNAL(clickedVertex(QVector4D*)), this, SLOT(clickedVertex(QVector4D*)));
	QObject::connect(ui.surface_data_content_, SIGNAL(visibilityChanged(bool)), ui.show_surface_data_, SLOT(setChecked(bool)));
	QObject::connect(ui.dock_surface_data_, SIGNAL(closed()), ui.show_surface_data_, SLOT(toggle()));
	QObject::connect(ui.show_surface_data_, SIGNAL(toggled(bool)), ui.dock_surface_data_, SLOT(setVisible(bool)));
	QObject::connect(ui.dock_vertex_data_, SIGNAL(closed()), ui.show_vertex_data_, SLOT(toggle()));
	QObject::connect(ui.show_vertex_data_, SIGNAL(toggled(bool)), ui.dock_vertex_data_, SLOT(setVisible(bool)));
	QObject::connect(ui.x_coordinate_, SIGNAL(valueChanged(double)), this, SLOT(editClickedVertex()));
	QObject::connect(ui.y_coordinate_, SIGNAL(valueChanged(double)), this, SLOT(editClickedVertex()));
	QObject::connect(ui.z_coordinate_, SIGNAL(valueChanged(double)), this, SLOT(editClickedVertex()));
	QObject::connect(ui.weight_, SIGNAL(valueChanged(double)), this, SLOT(editClickedVertex()));
	ui.dock_vertex_data_->hide();
}

MainView::~MainView() {

}

void MainView::sliderToTLabel(int i) const {
	const float paramToFloat = i/100.0f;
	QString float_as_string;// = QString::number(i / 10.0f, 'g', 4);
	float_as_string.sprintf("%.2f", paramToFloat);
	this->ui.t_label_->setText("t: " + float_as_string);
	this->ui.glview_->setT(paramToFloat);
}

void MainView::sliderToSLabel(int i) const {
	const float paramToFloat = i / 100.0f;
	QString float_as_string;// = QString::number(i / 10.0f, 'g', 4);
	float_as_string.sprintf("%.2f", paramToFloat);
	this->ui.s_label_->setText("s: " + float_as_string);
	this->ui.glview_->setS(paramToFloat);
}

void MainView::deCasteljau(bool state) const {
	this->ui.glview_->toggleSublineMode(state);
	toggleSlider();
	
}

void MainView::derivate(bool state) const {
	this->ui.glview_->toggleDerivateMode(state);
	toggleSlider();
}

//Todo: Remove?
void MainView::addCoordinates() const {
/*	QVector4D coordinates = { static_cast<float>(this->ui.x_coord_->value()), static_cast<float>(this->ui.y_coord_->value()), 0, 1};
	coordinates *= this->ui.weight_->value();
	if(this->ui.glview->addCoordinate(coordinates)) {
		this->addToList(coordinates);
	} else {
		QMessageBox messageBox;
		messageBox.critical(nullptr, "Error", QString("Korrekte Darstellung nicht möglich. Bitte löschen Sie Punkte"));
		messageBox.setFixedSize(500, 200);
	}*/
}

void MainView::keyPressEvent(QKeyEvent* event) {
	/*if (event->key() == Qt::Key_Delete && !ui.list_widget_->selectedItems().isEmpty()) {
		auto selected = ui.list_widget_->selectionModel()->selectedIndexes();
		auto i = selected.at(0).row();
		ui.list_widget_->takeItem(i);
		ui.glview->removeCoordinateByIndex(i);

	} else {
		this->ui.glview->keyPressEvent(event);
	}*/

	this->ui.glview_->keyPressEvent(event);
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
	this->ui.glview_->raiseElevation();
	this->ui.show_vertex_data_->setChecked(false);
	this->ui.show_vertex_data_->setEnabled(false);
	
}

void MainView::clickedVertex(QVector4D* coordinate) {
	this->clicked = coordinate;
	this->ui.show_vertex_data_->setEnabled(true);
	this->ui.dock_vertex_data_->setVisible(true);
	float w = clicked->w();
	this->ui.x_coordinate_->blockSignals(true);
	this->ui.y_coordinate_->blockSignals(true);
	this->ui.z_coordinate_->blockSignals(true);
	this->ui.weight_->blockSignals(true);
	this->ui.x_coordinate_->setValue(clicked->x()/w);
	this->ui.y_coordinate_->setValue(clicked->y()/w);
	this->ui.z_coordinate_->setValue(clicked->z()/w);
	this->ui.weight_->setValue(clicked->w());

	this->ui.x_coordinate_->blockSignals(false);
	this->ui.y_coordinate_->blockSignals(false);
	this->ui.z_coordinate_->blockSignals(false);
	this->ui.weight_->blockSignals(false);

	qDebug() << "clicked";
}

void MainView::editClickedVertex() {
	if(clicked == nullptr) {
		return;
	}
	float w = ui.weight_->value();
	this->clicked->setX(ui.x_coordinate_->value() * w);
	this->clicked->setY(ui.y_coordinate_->value() * w);
	this->clicked->setZ(ui.z_coordinate_->value() * w);
	this->clicked->setW(w);
	this->ui.glview_->editClickedVertex();
}

void MainView::toggleSlider() const {
	bool state = ui.show_sublines_->isChecked() || ui.show_derivation_->isChecked();
	this->ui.s_label_->setEnabled(state);
	this->ui.t_label_->setEnabled(state);
	this->ui.s_slider_->setEnabled(state);
	this->ui.t_slider_->setEnabled(state);
	if (!state) {
		this->ui.s_slider_->setValue(0);
		this->ui.t_slider_->setValue(0);
	}
}

