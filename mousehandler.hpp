#pragma once
class QMouseEvent;

class MouseHandler
{
public:
	MouseHandler();
	~MouseHandler();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
};

