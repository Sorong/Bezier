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
	void sliderToTLabel(int i) const;
	void sliderToSLabel(int i) const;
	void deCasteljau(bool state) const;
	void derivate(bool state) const;
	void addCoordinates() const;
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void degreeElevation() const;
	void degreeElevationT() const;
	void degreeElevationS() const;
	void clickedVertex(QVector4D*);
	void editClickedVertex();
private:
	void toggleSlider() const;
	QVector4D *clicked;
	Ui::BezierClass ui;
};

#endif // BEZIER_H
