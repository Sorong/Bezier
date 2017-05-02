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
	void slider_to_label(int i) const;
	void add_coordinates() const;
	void keyPressEvent(QKeyEvent *event) override;
private:
	
	Ui::BezierClass ui;
};

#endif // BEZIER_H
