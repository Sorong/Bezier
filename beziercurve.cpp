#include "beziercurve.hpp"
#include "beziersurfacecalculator.hpp"


BezierCurve::BezierCurve(QMatrix4x4& model, const QVector4D pos): Model(model, pos) {
}

BezierCurve::BezierCurve(QMatrix4x4& model): Model(model) {
}

BezierCurve::~BezierCurve()
{
}

void BezierCurve::setBaseCoordinates(QVector<QVector4D>& coordinates) {
	if(this->vertices_.size() != coordinates.size()) {
		this->indices_.clear();
		if(!colors_.empty()) {
			auto color = this->colors_.at(0);
			this->colors_.clear();
			this->colors_.fill(color, coordinates.size());
		}
		for(int i = 0; i < coordinates.size(); i++) {
			this->indices_.push_back(i);
		}
	}
	this->vertices_ = coordinates;

}

void BezierCurve::addBaseCoordinates(QVector4D coordinate) {
	this->vertices_.push_back(coordinate);
}

QVector<QVector4D>& BezierCurve::getVertices() {
	return this->vertices_;
}

void BezierCurve::init(QVector4D* position) {
	if(this->vertices_.isEmpty()) {
		return;
	}
/*	for (auto& vertex : vertices_) {
		if (vertex.w() == 0) {
			vertex.setW(1);
		}
		else {
			vertex /= vertex.w();
		}
	}*/
	this->colors_.fill(this->colors_.at(0), this->vertices_.size());
	if(indices_.size() != this->vertices_.size()) {
		for (int i = 0; i < this->vertices_.size(); i++) {
			this->indices_.push_back(i);
		}
	}

	Model::initBuffer();
	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void BezierCurve::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view  * (this->model_);
	for(auto& program : programs_) {
		program->bind();
		program->setUniformValue("mvp", mvp);
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_LINE_STRIP, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	}
	
}

int BezierCurve::size() const {
	return this->vertices_.size();
}

void BezierCurve::setColor(QVector4D color) {
	this->colors_.fill(color, this->vertices_.size());
}
