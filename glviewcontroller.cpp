#include "glviewcontroller.hpp"
#include "glview.hpp"
#include <QKeyEvent>
#define INITPOS 0.0f, 0.0f, -10.0f, 1.0f

GLViewController::GLViewController(GLView* view) : view_(view), mode_(SELECT), draw_mode_(NONE), click_amount_(0), current_selected_(nullptr) {
	this->click_color_ = { 1,0,0,1 };
	this->unclick_color_ = { 1,1,1,1 };
}

void GLViewController::setView(GLView* view) {
	this->view_ = view;
}

void GLViewController::setDrawMode(DrawMode mode) {
	this->draw_mode_ = this->draw_mode_ ^ mode;
}

void GLViewController::setMode(Mode mode) {
	if (mode_ == SELECT && mode != SELECT) {
		setCurrentUnclicked();
	}
	this->mode_ = mode;
}

void GLViewController::setClickAmount(int amount) {
	this->click_amount_ = amount;
	this->clicked_.resize(amount);
}

void GLViewController::mousePressEvent(QMouseEvent* event) {
	setCurrentUnclicked();
	switch (mode_) {
		case SELECT:
			pressSelectHandler(event);
			break;
		case DRAWCURVE:
			pressDrawCurveHandler(event);
			break;
		case DRAWSURFACE:
			pressDrawSurfaceHandler(event);
			break;
		case DRAWCOONS:
			pressDrawCoonspatchHandler(event);
			break;
		default:
			break;
	}
}

void GLViewController::mouseMoveEvent(QMouseEvent* event) {
	switch (mode_) {
		case SELECT:
			moveSelectHandler(event);
			break;
		case DRAWSURFACE:
			moveDrawSurfaceHandler(event);
			break;
		default:
			break;
	}
}

void GLViewController::mouseReleaseEvent(QMouseEvent* event) {
	setCurrentUnclicked();
}

void GLViewController::pressSelectHandler(QMouseEvent* event) {
	QVector2D pos(event->pos());
	QRect viewp(0, 0, view_->width(), view_->height());
	view_->click_model_.setColumn(3, {INITPOS});
	auto begin = QVector3D(pos, -10.0f).unproject(this->view_->view_ * view_->click_model_, view_->projection_, viewp);
	auto end = QVector3D(pos.x(), view_->height() - pos.y(), 1.0f).unproject(this->view_->view_ * view_->click_model_, view_->projection_, viewp);
	QVector3D direction = (end - begin).normalized();
	float radius = 0.2f;
	float radius2 = radius * radius;
	for (auto& current : surfaces_) {
		if (checkClicked(*current, begin, direction, radius2)) {
			return;
		}
	}
	for (auto& current : curves_) {
		if (checkClicked(*current, begin, direction, radius2)) {
			return;
		}
	}
	if (checkClicked(*view_->surface_, begin, direction, radius2));

}

void GLViewController::pressDrawCurveHandler(QMouseEvent* event) {
}

void GLViewController::pressDrawSurfaceHandler(QMouseEvent* event) {
}

void GLViewController::pressDrawCoonspatchHandler(QMouseEvent* event) {
}

void GLViewController::moveSelectHandler(QMouseEvent* event) {
	if (current_selected_ == nullptr) {
		return;
	}
	QVector2D pos(event->pos());
	QRect viewp(0, 0, view_->width(), view_->height());
	view_->click_model_.setColumn(3, { INITPOS });
	auto begin = QVector3D(pos, -10.0f).unproject(this->view_->view_ * view_->click_model_, view_->projection_, viewp);
	auto end = QVector3D(pos.x(), view_->height() - pos.y(), 1.0f).unproject(this->view_->view_ * view_->click_model_, view_->projection_, viewp);
	QVector4D direction = (end - begin).normalized();
	auto length = current_selected_->offset_.length();
	float w = current_selected_->reference_->w();
	*current_selected_->reference_ = (begin + length * direction);
	current_selected_->reference_->setW(1);
	*current_selected_->reference_ *= w;
	view_->makeCurrent();
	emit view_->clickedVertex(current_selected_->reference_);
	current_selected_->model_->reinit();
}

void GLViewController::moveDrawSurfaceHandler(QMouseEvent* event) {
	
}

void GLViewController::setCurrentUnclicked() {
	if (current_selected_ != nullptr) {
		current_selected_->clickable_->setUnclicked(unclick_color_);
		current_selected_ = nullptr;
	}
}

bool GLViewController::checkClicked(BezierSurface& surface, const QVector3D& begin, const QVector3D& direction, const float radius) {
	for (auto i = 0; i < surface.size(); i++) {
		QVector4D& coord = surface.get(i);
		QVector3D L = (coord.toVector3DAffine() - begin);
		float tca = QVector3D::dotProduct(L, direction);
		if (tca < 0) {
			continue;
		}
		float d2 = QVector3D::dotProduct(L, L) - tca * tca;
		if (d2 > radius) {
			continue;
		}
		//float thc = sqrt(radius2 - d2);
		//auto t_drag = tca - thc;
		ClickedModel clicked;
		clicked.clickable_ = &surface.getClicked(i);
		clicked.reference_ = &surface.getClicked(i).getReference();
		clicked.model_ = &surface;
		clicked.offset_ = coord.toVector3DAffine() - begin;
		clicked_.push_back(clicked);
		this->current_selected_ = &clicked_[clicked_.size() - 1];
		this->current_selected_->clickable_->setClicked(click_color_);
		/*	intersect_to_center_ = coord.toVector3DAffine() - begin;
			qDebug() << "clicked:" << coord;
			qDebug() << intersect_to_center_;*/
		emit view_->clickedVertex(clicked.reference_);
		return true;
	}
	return false;
}
