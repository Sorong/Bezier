#ifndef BEZIER_H
#define BEZIER_H

#include <QtWidgets/QMainWindow>
#include "ui_bezier.h"
#include "uicontroller.hpp"

class MainWindow : public QMainWindow {
	Q_OBJECT
		friend UIController;
public:
	MainWindow(QWidget* parent = 0);
	~MainWindow();
	void registerController(UIController &controller);
	void keyPressEvent(QKeyEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void addToList(QVector4D coordinate) const;
	void reloadList() const;
public slots:
	void sliderToLabel(int i) const;
	void addCoordinates() const;
	void raiseElevation() const;
private:
	Ui::BezierClass ui;
	UIController controller;
};

#endif // BEZIER_H
