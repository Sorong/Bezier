#include "glviewcontroller.hpp"
#include "glview.hpp"


GLViewController::GLViewController(GLView* view): view_(view), mode_(SELECT), draw_mode_(NONE) {
}

void GLViewController::setView(GLView* view) {
	this->view_ = view;
}

void GLViewController::setDrawMode(DrawMode mode) {
	this->draw_mode_ = this->draw_mode_ ^ mode;
}

void GLViewController::setMode(Mode mode) {
	if(mode_ == SELECT && mode != SELECT) {
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
	default: break;
	}
}

void GLViewController::mouseMoveEvent(QMouseEvent* event) {
}

void GLViewController::mouseReleaseEvent(QMouseEvent* event) {}

void GLViewController::pressSelectHandler(QMouseEvent* event) {
	
}

void GLViewController::pressDrawCurveHandler(QMouseEvent* event) {}

void GLViewController::pressDrawSurfaceHandler(QMouseEvent* event) {}

void GLViewController::pressDrawCoonspatchHandler(QMouseEvent* event) {}

void GLViewController::moveSelectHandler(QMouseEvent* event) {}

void GLViewController::moveDrawSurfaceHandler(QMouseEvent* event) {}

void GLViewController::setCurrentUnclicked() {
	if (current_selected != nullptr) {
		current_selected->clickable_->setUnclicked(unclick_color_);
	}
}
