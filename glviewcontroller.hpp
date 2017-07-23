#pragma once
#include "clickable.hpp"
#include <QVector>
#include <memory>
#include "model.hpp"
#include "beziersurface.hpp"
#include "coonspatch.hpp"

class QMouseEvent;
class GLView;

typedef enum {
	SELECT = 0, DRAWCURVE = 1, DRAWSURFACE = 2, DRAWCOONS = 4, C0 = 8
} Mode;

typedef enum {
	NONE = 0, CASTELJAU = 1, DERIVATE = 2
} DrawMode;

typedef enum {
	UNKNOWN, SURFACE, COONS
} ModelType;

typedef struct Clicked {
	ModelType type;
	Clickable *clickable_;
	Model *model_;
	QVector4D *reference_;
	QVector3D offset_;
	int row_index_ = -1;
	int col_index_ = -1;
	Clicked(): type(UNKNOWN), clickable_(nullptr), model_(nullptr), reference_(nullptr) {
	}

	Clicked(BezierSurface& surface, int i)
		: type(SURFACE) {
		clickable_ = &surface.getClicked(i, &row_index_, &col_index_);
		reference_ = &surface.getClicked(i).getReference();
		model_ = &surface;
	}
	Clicked(CoonsPatch& patch, int i) : type(COONS) {
		clickable_ = &patch.getClicked(i);
		reference_ = &patch.getClicked(i).getReference();
		model_ = &patch;
	}
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
	void mouseMoveEvent(QMouseEvent* event) const;
	void mouseReleaseEvent(QMouseEvent* event);
	void clearClicked();
	void setClampedZ(float f);
	BezierSurface* getSelectedSurface();
private:
	void pressSelectHandler(QMouseEvent* event);
	void pressDrawCurveHandler(QMouseEvent* event);
	void pressDrawSurfaceHandler(QMouseEvent* event);
	void pressDrawCoonspatchHandler(QMouseEvent* event);
	void pressC0Handler(QMouseEvent* event);
	void moveSelectHandler(QMouseEvent* event) const;
	void moveC0Handler(QMouseEvent* event) const;
	void moveDrawSurfaceHandler(QMouseEvent* event) const;
	void addClicked(ClickedModel *clicked);
	void setCurrentUnclicked();
	bool checkClicked(BezierSurface& surface, const QVector3D& begin, const QVector3D& direction, const float radius);
	bool checkClicked(CoonsPatch& patch, const QVector3D& begin, const QVector3D& direction, const float radius);
	void projectMouseEvent(QMouseEvent* event, QVector3D *begin, QVector3D *end, QVector3D *direction) const;
	void projectMouseEvent(QMouseEvent* event, const QMatrix4x4 model, QVector3D *begin, QVector3D *end, QVector3D * direction) const;
	GLView* glview_;
	Mode mode_;
	DrawMode draw_mode_;
	int click_amount_;
	float clamped_z_;
	QVector<ClickedModel> clicked_;
	ClickedModel *current_selected_;
	QVector4D unclick_color_, click_color_;

};
