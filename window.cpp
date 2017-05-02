#include "window.h"
#include <QKeyEvent>
Bezier::Bezier(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setMinimumHeight(500);
	//this->setMaximumHeight(375);
	//QObject::connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), ui.openGLWidget, SLOT(set_t(int)));
	QObject::connect(ui.tSlider, SIGNAL(valueChanged(int)), this, SLOT(slider_to_label(int)));
	QObject::connect(ui.addButton, SIGNAL(pressed()), this, SLOT(add_coordinates()));
}

Bezier::~Bezier()
{

}

void Bezier::slider_to_label(int i) const
{

	QString floatAsString;// = QString::number(i / 10.0f, 'g', 4);
	floatAsString.sprintf("%.2f", i / 10.0f);
	this->ui.tLabel->setText("t: " + floatAsString);
	this->ui.bezier->set_t(i);
}

void Bezier::add_coordinates() const
{
	XY coords = { static_cast<float>(this->ui.xCoord->value()), static_cast<float>(this->ui.yCoord->value()) };
	this->ui.bezier->addCoordinate(coords);
	this->ui.listWidget->addItem(QString("(" + QString::number(coords.x) + "," + QString::number(coords.y) + ")"));
}

void Bezier::keyPressEvent(QKeyEvent* event)
{
	if(event->key() == Qt::Key_Delete && !ui.listWidget->selectedItems().isEmpty())
	{
		auto selected = ui.listWidget->selectionModel()->selectedIndexes();
		auto i = selected.at(0).row();
		ui.listWidget->takeItem(i);
		ui.bezier->removeCoordinateByIndex(i);
		
	} else
	{
		this->ui.bezier->keyPressEvent(event);
	}
}
