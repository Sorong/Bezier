#pragma once
#include "clickable.hpp"
#include <QVector>
#include <memory>
#include "model.hpp"
#include "beziersurface.hpp"

class QMouseEvent;
class GLView;

typedef enum {
	SELECT = 0, DRAWCURVE = 1, DRAWSURFACE = 2, DRAWCOONS = 4, C0 = 8
} Mode;

typedef enum {
	NONE = 0, CASTELJAU = 1, DERIVATE = 2
} DrawMode;

typedef struct {
	Clickable *clickable_;
	Model *model_;
	QVector4D *reference_;
	QVector3D offset_;
	int row_index_ = -1;
	int col_index_ = -1;
} ClickedModel;

inline DrawMode operator|(DrawMode a, DrawMode b) {
	return static_cast<DrawMode>(static_cast<int>(a) | static_cast<int>(b));
}

inline DrawMode operator&(DrawMode a, DrawMode b) {
	return static_cast<DrawMode>(static_cast<int>(a) & static_cast<int>(b));
}
inline DrawMode operator^(DrawMode a, DrawMode b) {
	return static_cast<DrawMode>(static_cast<int>(a) ^ static_cast<int>(b));
}


class GLViewController {
public:
	GLViewController(GLView* view);
	void setView(GLView* view);
	void setDrawMode(DrawMode mode);
	void setMode(Mode mode);
	void setClickAmount(int amount);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void clearClicked();
private:
	void pressSelectHandler(QMouseEvent* event);
	void pressDrawCurveHandler(QMouseEvent* event);
	void pressDrawSurfaceHandler(QMouseEvent* event);
	void pressDrawCoonspatchHandler(QMouseEvent* event);
	void moveSelectHandler(QMouseEvent* event);
	void moveDrawSurfaceHandler(QMouseEvent* event);
	void setCurrentUnclicked();
	bool checkClicked(BezierSurface& surface, const QVector3D& begin, const QVector3D& direction, const float radius);
<<<<<<< HEAD
	GLView* view_;
=======
	GLView* glview_;
>>>>>>> 9d71dd988663019e6bc14f872f8e9ce384796ff9
	Mode mode_;
	DrawMode draw_mode_;
	int click_amount_;
	float clamped_z_;
	QVector<ClickedModel> clicked_;
	ClickedModel *current_selected_;
	QVector4D unclick_color_, click_color_;
<<<<<<< HEAD
	QVector<std::shared_ptr<BezierSurface>> surfaces_;
	QVector<std::shared_ptr<BezierSurface>> curves_;
=======

>>>>>>> 9d71dd988663019e6bc14f872f8e9ce384796ff9
};
