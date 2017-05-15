#include "line.h"


Line::Line(QMatrix4x4* model, QMatrix4x4* view, QMatrix4x4* projection, QVector3D color, QVector<QVector4D> points): vertexarrayobject_(0), position_buffer_(0), color_buffer_(0), index_buffer_(0) {
	this->model_ = new QMatrix4x4(*model);
	this->view_ = view;
	this->projection_ = projection;
	this->vertices_ = QVector<QVector4D>(points);
	this->colors_.push_back(this->vertices_.size() != 1 ? QVector3D(color) : QVector3D(1, 1, 1));
	this->program_ = nullptr;

	QOpenGLFunctions_3_3_Core::initializeOpenGLFunctions();
}

Line::~Line() {
	glDeleteVertexArrays(1, &this->vertexarrayobject_);
	glDeleteBuffers(1, &index_buffer_);
	glDeleteBuffers(1, &color_buffer_);
	glDeleteBuffers(1, &position_buffer_);
	delete this->model_;
}

void Line::setPosition(QVector4D pos) {
	this->pos_ = QVector3D(pos);
	this->model_->translate(pos.x(), pos.y(), pos.z());
}


void Line::setShader(QOpenGLShaderProgram* program) {
	this->program_ = program;
}

void Line::renderLine() {
	auto mvp = *(this->projection_) * *(this->view_) * *(this->model_);
	auto mv = *(this->view_) * *(this->model_);
	auto i = this->program_->bind();
	this->program_->setUniformValue("mvp", mvp);
	this->program_->setUniformValue("ModelViewMatrix", mv);
	glBindVertexArray(this->vertexarrayobject_);
	if (this->vertices_.size() != 1) {
		glDrawElements(GL_LINE_STRIP, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
	} else {
		glDrawElements(GL_POINTS, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
	}

	glBindVertexArray(0);

}

void Line::initLine() {
	if (program_ == nullptr) {
		return;
	}
	QVector<QVector4D> vertices = this->vertices_;
	for(auto& vertex: vertices) {
		if(vertex.w() == 0) {
			vertex.setW(1);
		} else {
			vertex /= vertex.w();
		}
	}
	QVector3D col = this->colors_.at(0);
	while (this->colors_.size() < this->vertices_.size()) {
		colors_.push_back({col});
	}
	for (int i = 0; i < this->vertices_.size(); i++) {
		this->indices_.push_back(i);
	}
	GLuint progId = this->program_->programId();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &this->vertexarrayobject_);
	glBindVertexArray(this->vertexarrayobject_);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &this->position_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, this->position_buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(QVector4D), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(progId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &this->color_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_);
	glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(QVector4D), colors_.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(progId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &this->index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLushort), indices_.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);


}

void Line::addVertex(QVector4D vertex) {
	glDeleteVertexArrays(1, &this->vertexarrayobject_);
	glDeleteBuffers(1, &index_buffer_);
	glDeleteBuffers(1, &color_buffer_);
	glDeleteBuffers(1, &position_buffer_);
	this->vertices_.push_back(vertex);
	initLine();
}

QVector4D Line::at(int index) const {
	return this->vertices_.at(index);
}

int Line::size() const {
	return this->vertices_.size();
}

QVector<QVector4D> Line::getVertices() const {
	return this->vertices_;
}

QVector4D Line::at(int i) {
	if(i < 0 || i >= this->vertices_.size()) {
		throw std::out_of_range("Index out of range");
	}
	return this->vertices_.at(i);
}

QVector4D Line::last() {
	QVector4D vec;
	try {
		vec = this->at((this->vertices_.size() - 1));
	} catch(std::out_of_range exception) {
		throw exception;
	}
	return this->at((this->vertices_.size() - 1));
}
