#ifndef BEZIER_H
#define BEZIER_H

#include <QtWidgets/QMainWindow>
#include "ui_bezier.h"

class Bezier : public QMainWindow
{
	Q_OBJECT

public:
	Bezier(QWidget *parent = 0);
	~Bezier();
public slots:
	void slider_to_label(int i)
	{

		QString floatAsString = QString::number(i / 10.0f,'g', 2);
		this->ui.label->setText(floatAsString);
		this->ui.openGLWidget->set_t(i);
	}
private:
	
	Ui::BezierClass ui;
};

#endif // BEZIER_H
