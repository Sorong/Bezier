#include "rectangle.hpp"


Rectangle::Rectangle(QVector4D start, int size): Clickable(start) {

	QVector4D right = start;
	QVector4D botleft = start;
	QVector4D botright = start;
	right.setX(right.x() + size);
	botleft.setY(botleft.y() + size);
	botright = right + botleft;
	this->vertices_ = {
		start, right, botleft, botright
	};
}

Rectangle::~Rectangle() {
}

void Rectangle::init(QVector4D* position) {
	if(programs_.isEmpty() || this->vertices_.isEmpty()) {
		return;
	}
	if(position) {
		this->setPosition(*position);
	}
	this->indices_ = { 0,1,0,2,1,3,2,3 };
	if (this->colors_.isEmpty()) {
		this->colors_.push_back({ 0,0,0,1 });
	}

	this->colors_.fill(this->colors_.at(0), 4);



	Model::initBuffer();
	glBindVertexArray(0);
}

void Rectangle::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view * model_;
	for (auto& prog : programs_) {
		prog->bind();
		prog->setUniformValue("mvp", mvp);
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	}
}

void Rectangle::reinit(QVector4D* position) {
	this->vertices_[1] = { vertices_[2].x(), vertices_[0].y(), vertices_[1].z(), 1 };
	this->vertices_[2] = { vertices_[0].x(), vertices_[2].y(), vertices_[2].z(), 1 };
	glBindVertexArray(this->vertexarrayobject_);
	glBindBuffer(GL_ARRAY_BUFFER, this->position_buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(QVector4D), vertices_.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Rectangle::setColor(QVector4D color) {
	this->colors_.fill(color, 4);
}

void Rectangle::translateToReference() {
}

void Rectangle::setClicked(QVector4D& color) {
	this->setColor(color);
}

void Rectangle::setUnclicked(QVector4D& color) {
	this->setColor(color);
}
