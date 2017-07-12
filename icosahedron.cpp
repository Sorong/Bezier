#include "icosahedron.hpp"


Icosahedron::Icosahedron(QMatrix4x4& model, QVector4D& reference_vertex) : Model(model), Clickable(reference_vertex) {
	setRadius(1);
	this->colors_.push_back({ 1,1,1,1 });
}

Icosahedron::~Icosahedron() {
}

void Icosahedron::init(QVector4D *position) {
	if (!default_shader_) {
		return;
	}
	if (position) {
		this->setPosition(*position);
	}

	this->vertices_ = {
		{ -radius_, 0, 1 ,1},{ radius_, 0, 1 ,1},{ -radius_, 0, -1 ,1},{ radius_, 0, -1 ,1},
		{ 0, 1, radius_ ,1},{ 0, 1, -radius_ ,1},{ 0, -1, radius_ ,1},{ 0, -1, -radius_ ,1},
		{ 1, radius_, 0 ,1},{ -1, radius_, 0 ,1},{ 1, -radius_, 0 ,1},{ -1, -radius_, 0 ,1}
	};
	this->indices_ = {
		1, 4, 0, 4, 9, 0, 4, 5, 9, 8, 5, 4,	1, 8, 4,
		1, 10, 8, 10, 3, 8, 8, 3, 5, 3, 2, 5, 3, 7, 2,
		3, 10, 7, 10, 6, 7, 6, 11, 7, 6, 0, 11,	6, 1, 0,
		10, 1, 6, 11, 0, 9, 2, 11, 9, 5, 2, 9, 11, 2, 7
	};
	this->colors_.fill(this->colors_.at(0), this->vertices_.size());
	Model::initBuffer();
	// Unbind vertex array object (back to default).
	glBindVertexArray(0);

}

void Icosahedron::render(QMatrix4x4& projection, QMatrix4x4& view) {
	if(!default_shader_) {
		return;
	}
	auto mvp = projection * view * model_;
	default_shader_->bind();
	if(!click_shader_) {
		default_shader_->setUniformValue("mvp", mvp);
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	} else {
		
	}
	
}


void Icosahedron::setRadius(float i) {
	int asInt = i * 100;
	if (asInt == 0) { return; }
	this->radius_ = (i / 4) * (1 + 2.236067977);
}

void Icosahedron::setColor(QVector4D color) {
	if (this->vertices_.isEmpty()) {
		this->colors_.fill(color, 1);
	}
	else {
		this->colors_.fill(color, this->vertices_.size());
		glBindVertexArray(this->vertexarrayobject_);
		glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_);
		glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(QVector4D), colors_.data(), GL_DYNAMIC_DRAW);
		glBindVertexArray(0);
	}

}

void Icosahedron::scale(float ratio) {
	this->model_.scale(ratio);
}

void Icosahedron::translateToReference() {
	this->model_.translate(reference_vertex_->toVector3DAffine());
}

void Icosahedron::setClicked(QVector4D& color) {
	this->setColor(color);
}

void Icosahedron::setUnclicked(QVector4D& color) {
	this->setColor(color);
}

void Icosahedron::setClickShader(QOpenGLShaderProgram& shader) {
	this->default_shader_ = &shader;
	Clickable::setClickShader(shader);
}
