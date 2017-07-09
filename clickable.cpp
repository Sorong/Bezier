#include "clickable.hpp"


Clickable::Clickable(QVector4D& reference_vertex):
	reference_vertex_(&reference_vertex) {
	
}

Clickable::~Clickable() {
}

QVector4D& Clickable::getReference() const {
	return *this->reference_vertex_;
}

void Clickable::setReference(QVector4D& reference) {
	this->reference_vertex_ = &reference;
}
