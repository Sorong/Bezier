#include "glviewcontroller.hpp"
#include "glview.hpp"


GLViewController::GLViewController(GLView* view)  {
}

void GLViewController::setView(GLView* view) {
	this->view_ = view;
	this->view_->makeCurrent();
}
