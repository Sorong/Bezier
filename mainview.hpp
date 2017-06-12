#ifndef BEZIER_H
#define BEZIER_H

#include <QtWidgets/QMainWindow>
#include "ui_bezier.h"

class MainView : public QMainWindow {
	Q_OBJECT

public:
	MainView(QWidget* parent = 0);
	~MainView();
public slots:
	void sliderToLabel(int i) const;
	void addCoordinates() const;
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void raiseElevation() const;
	void clickedVertex(QVector4D&);
private:
	void addToList(QVector4D coordinate) const;
	void reloadList() const;
	Ui::BezierClass ui;
};

#endif // BEZIER_H
