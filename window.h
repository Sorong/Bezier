#ifndef BEZIER_H
#define BEZIER_H

#include <QtWidgets/QMainWindow>
#include "ui_bezier.h"

class Bezier : public QMainWindow {
	Q_OBJECT

public:
	Bezier(QWidget* parent = 0);
	~Bezier();
public slots:
	void sliderToLabel(int i) const;
	void addCoordinates() const;
	void keyPressEvent(QKeyEvent* event) override;
	void raiseElevation() const;
	void getHodograph() const;
private:
	void addToList(QVector4D coordinate) const;
	void reloadList() const;
	Ui::BezierClass ui;
};

#endif // BEZIER_H
