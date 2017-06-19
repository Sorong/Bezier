#include "line.hpp"


Line::Line(QMatrix4x4& model, QVector4D position) : Model(model, position) {
}

void Line::init(QVector4D* position) {
	if (programs_.isEmpty() ||this->vertices_.isEmpty()) {
		return;
	}
	if(position) {
		this->setPosition(*position);
	}
	for(int i = 0; i < vertices_.size(); i++) {
		this->indices_.push_back(i);
	}
	if(this->colors_.isEmpty()) {
		this->colors_.push_back({ 0,0,0,1 });
	}
	if (this->vertices_.size() == 1) {
		this->colors_.fill({ 1,1,1,1 }, 1);
	} else {
		this->colors_.fill(this->colors_.at(0), this->vertices_.size());
	}
	

	Model::initBuffer();
	glBindVertexArray(0);
}

void Line::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view * model_;
	for(auto& prog : programs_) {
		prog->bind();
		prog->setUniformValue("mvp", mvp);
		glBindVertexArray(this->vertexarrayobject_);
		if(this->vertices_.size() > 1) {
			glDrawElements(GL_LINE_STRIP, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		} else {
			glDrawElements(GL_POINTS, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		}
	
		glBindVertexArray(0);
	}
}

void Line::setCoordinates(QVector<QVector4D>& coordinates) {
	this->vertices_.clear();
	for(auto& coordinate : coordinates) {
		this->vertices_.push_back(coordinate);
	}
}

void Line::setColor(QVector4D color) {
}

