#include "patch.hpp"



Patch::Patch(QMatrix4x4& model, const QVector4D& pos)
	: Model(model, pos),
	  patch_coordinates_(nullptr) {
}

Patch::~Patch()
{
}

void Patch::init(QVector4D* position) {
	if(!default_shader_  || !patch_coordinates_) {
		return;
	}
	for(int i = 0; i < this->patch_coordinates_->size() - 1; i++) {
		for(int j = 0; j < this->patch_coordinates_->at(i).size(); j++) {
			vertices_.push_back((*patch_coordinates_)[i][j]);
			vertices_.push_back((*patch_coordinates_)[i + 1][j]);
		}
	}
	colors_.fill({ 1,0,0,.5f }, this->vertices_.size());
	for (int i = 0; i < this->vertices_.size() - 2; i++) {
		this->indices_.push_back(i);
		this->indices_.push_back(i + 1);
		this->indices_.push_back(i + 2);
	}
	Model::initBuffer();
	glBindVertexArray(0);
}

void Patch::render(QMatrix4x4& projection, QMatrix4x4& view) {
	if (!default_shader_) {
		return;
	}
	auto mvp = projection * view  * (this->model_);
	default_shader_->bind();
	default_shader_->setUniformValue("mvp", mvp);
	glBindVertexArray(this->vertexarrayobject_);
	glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(0);
}

void Patch::reinit(QVector4D* position) {
	if (!default_shader_ || !patch_coordinates_) {
		return;
	}
	this->vertices_.clear();
	this->indices_.clear();
	for (int i = 0; i < this->patch_coordinates_->size() - 1; i++) {
		for (int j = 0; j < this->patch_coordinates_->at(i).size(); j++) {
			vertices_.push_back((*patch_coordinates_)[i][j]);
			vertices_.push_back((*patch_coordinates_)[i + 1][j]);
		}

	}
	colors_.fill({ 1,0,0,.5f }, this->vertices_.size());
	for (int i = 0; i < this->vertices_.size() - 2; i++) {
		this->indices_.push_back(i);
		this->indices_.push_back(i + 1);
		this->indices_.push_back(i + 2);
	}
	Model::reinit(position);
}

void Patch::setCoordinates(QVector4DMatrix& coordinates) {
	if(coordinates.isEmpty()) {
		return;
	}
	int size = coordinates[0].size();
	for(int i = 1 ; i < coordinates.size(); i++) {
		if(coordinates[i].size() != size) {
			return;
		}
	}
	this->patch_coordinates_ = &coordinates;
}
