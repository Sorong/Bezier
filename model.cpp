#include "model.hpp"


Model::Model() : default_shader_(nullptr), normal_shader_(nullptr), vertexarrayobject_(0), position_buffer_(0), color_buffer_(0), index_buffer_(0), show_normals_(false) {
	QOpenGLFunctions_3_3_Core::initializeOpenGLFunctions();
}

Model::Model(QMatrix4x4& model) : Model(model, { 0,0,0,0 }) {
}

Model::Model(QMatrix4x4& model, const QVector4D& pos) : default_shader_(nullptr), normal_shader_(nullptr), vertexarrayobject_(0), position_buffer_(0), color_buffer_(0), index_buffer_(0), show_normals_(false) {
	this->model_ = model;
	setPosition(pos);
	QOpenGLFunctions_3_3_Core::initializeOpenGLFunctions();
}

Model::~Model()
{
	if (this->vertexarrayobject_) {
		glDeleteVertexArrays(1, &this->vertexarrayobject_);
		glDeleteBuffers(1, &index_buffer_);
		glDeleteBuffers(1, &color_buffer_);
		glDeleteBuffers(1, &position_buffer_);
	}

}

void Model::setPosition(const QVector4D& position) {
	this->pos_ = position;
	this->model_.translate(pos_.toVector3D());
}

void Model::reinit(QVector4D* position) {
	glBindVertexArray(this->vertexarrayobject_);
	glBindBuffer(GL_ARRAY_BUFFER, this->position_buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(QVector4D), vertices_.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);

	glBindVertexArray(this->vertexarrayobject_);
	glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_);
	glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(QVector4D), colors_.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);

	glBindVertexArray(this->vertexarrayobject_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLushort), indices_.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
	if(!normals_.isEmpty()) {
		glBindVertexArray(this->vertexarrayobject_);
		glBindBuffer(GL_ARRAY_BUFFER, this->normal_buffer_);
		glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(QVector4D), normals_.data(), GL_STATIC_DRAW);
		glBindVertexArray(0);
	}
	if (position) {
		model_.translate(position->toVector3DAffine());
	}
}

QVector4D Model::at(int index) const {
	if (index < 0 || index >= size()) {
		throw std::out_of_range("Index out of Bounds");
	}
	return vertices_.at(index);
}

int Model::size() const {
	return vertices_.size();
}

const QVector<QVector4D>& Model::getVertices() const {
	return vertices_;
}

QVector4D Model::last() const {
	return at(vertices_.size() - 1);
}

void Model::setDefaultShader(QOpenGLShaderProgram& prog) {
	default_shader_ = &prog;
}


void Model::setModelMatrix(QMatrix4x4& model) {
	this->model_ = model;
}

void Model::rotate(qreal angle, qreal x, qreal y, qreal z) {
	this->model_.rotate(angle, x, y, z);
}

void Model::rotate(qreal angle, const QVector3D& vector) {
	this->model_.rotate(angle, vector);
}

void Model::scale(qreal factor) {
	this->model_.scale(factor);
}

void Model::setColor(QVector4D color) {
	if (this->vertices_.isEmpty()) {
		this->colors_.fill(color, 1);
	}
	else {
		this->colors_.fill(color, this->vertices_.size());
		if (vertexarrayobject_) {
			glBindVertexArray(this->vertexarrayobject_);
			glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_);
			glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(QVector4D), colors_.data(), GL_STATIC_DRAW);
			glBindVertexArray(0);
		}
	}
}

QMatrix4x4& Model::getModelMatrix() {
	return model_;
}

void Model::addNormalShader(QOpenGLShaderProgram & prog) {
	this->normal_shader_ = &prog;
}

void Model::showNormals(bool show) {
	this->show_normals_ = show;
}

void Model::initBuffer() {
	GLuint progId = this->default_shader_->programId();
	GLuint pos;
	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &this->vertexarrayobject_);
	glBindVertexArray(this->vertexarrayobject_);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &this->position_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, this->position_buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(QVector4D), vertices_.data(), GL_STATIC_DRAW);

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
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	if(!normals_.isEmpty()) {
		// Step 3: Normale
		glGenBuffers(1, &this->normal_buffer_);
		glBindBuffer(GL_ARRAY_BUFFER, this->normal_buffer_);
		glBufferData(GL_ARRAY_BUFFER, normals_.size() * sizeof(QVector4D), normals_.data(), GL_STATIC_DRAW);

		pos = glGetAttribLocation(progId, "normal");
		glEnableVertexAttribArray(pos);
		glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	}

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &this->index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLushort), indices_.data(), GL_STATIC_DRAW);
}

QVector4D Model::calculateNormals(QVector4D origin, QVector4D v2, QVector4D v3) {
	const QVector4D a = v2 - origin;
	const QVector4D b = v3 - origin;

	return QVector3D::crossProduct(a.toVector3D(), b.toVector3D()).normalized();
}
