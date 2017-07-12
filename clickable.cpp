#include "clickable.hpp"


Clickable::Clickable(QVector4D& reference_vertex)
	: click_shader_(nullptr),
	  reference_vertex_(&reference_vertex) {

}

Clickable::~Clickable() {
}

QVector4D& Clickable::getReference() const {
	return *this->reference_vertex_;
}

void Clickable::setClickShader(QOpenGLShaderProgram& shader) {
	this->click_shader_ = &shader;
}

void Clickable::setReference(QVector4D& reference) {
	this->reference_vertex_ = &reference;
}
