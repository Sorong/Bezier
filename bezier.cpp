#include "bezier.h"

Bezier::Bezier(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setMinimumHeight(500);
	//this->setMaximumHeight(375);
	//QObject::connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), ui.openGLWidget, SLOT(set_t(int)));
	QObject::connect(ui.horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(slider_to_label(int)));
}

Bezier::~Bezier()
{

}


