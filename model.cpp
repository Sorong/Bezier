#include "model.hpp"


Model::Model() {
}

Model::Model(QMatrix4x4& model) : Model(model, { 0,0,0,0 }) {

}

Model::Model(QMatrix4x4& model, const QVector4D& pos) : vertexarrayobject_(0), position_buffer_(0), color_buffer_(0), index_buffer_(0) {
	this->model_ = model;
	setPosition(pos);
	QOpenGLFunctions_3_3_Core::initializeOpenGLFunctions();
}

Model::~Model()
{	
	if(this->vertexarrayobject_) {
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

QVector4D Model::at(int index) const {
	if(index < 0 || index >= size()) {
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

void Model::addShader(QOpenGLShaderProgram& prog) {
	programs_.push_back(&prog);
}

void Model::removeShader(int index) {
	if (index < 0 || index > programs_.size() - 1) {
		throw std::out_of_range("Index out of bound");
	}
	programs_.remove(index);
}
