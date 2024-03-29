#include "beziersurfacestrip.hpp"

BezierSurfaceStrip::BezierSurfaceStrip(QMatrix4x4& model, BezierCurve* first_curve, BezierCurve* second_curve, Light& light)
	: Model(model), PhongModel(light),
	first_curve_(first_curve),
	second_curve_(second_curve) {
}

BezierSurfaceStrip::BezierSurfaceStrip(QMatrix4x4& model, const QVector4D& pos, BezierCurve* first_curve, BezierCurve* second_curve, Light& light)
	: Model(model, pos), PhongModel(light),
	first_curve_(first_curve),
	second_curve_(second_curve) {
}

void BezierSurfaceStrip::init(QVector4D* position) {
	if (!default_shader_ || first_curve_->size() != second_curve_->size()) {
		return;
	}
	for (int f_i = 0; f_i < first_curve_->size(); f_i++) {
		QVector4D current_first = first_curve_->at(f_i);
		QVector4D current_second = second_curve_->at(f_i);
		vertices_.push_back(first_curve_->at(f_i));
		vertices_.push_back(second_curve_->at(f_i));
		if (first_curve_->normalsSet() && second_curve_->normalsSet()) {
			normals_.push_back(first_curve_->normalAt(f_i));
			normals_.push_back(second_curve_->normalAt(f_i));
		}

	}
	colors_.fill({ 1,0,0,.5f }, this->vertices_.size());
	QVector4D mat = { 1, 0, 0.2f, .5f };
	this->setMaterial(mat);
	for (int i = 0; i < this->vertices_.size(); i++) {
		this->indices_.push_back(i);
	}
	Model::initBuffer();
	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void BezierSurfaceStrip::render(QMatrix4x4& projection, QMatrix4x4& view) {
	if (!default_shader_) {
		return;
	}
	auto mvp = projection * view  * (this->model_);
	auto mv = view * this->model_;
	QMatrix3x3 nm = this->model_.normalMatrix();

	if (show_normals_ && !normals_.isEmpty() && normal_shader_) {
		normal_shader_->bind();
		auto test = normal_shader_->uniformLocation("mvp");
		normal_shader_->setUniformValue("mvp", mvp);
		normal_shader_->setUniformValue("nm", nm);
		normal_shader_->setUniformValue("projection", projection);
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	}

	default_shader_->bind();
	default_shader_->setUniformValue("mvp", mvp);
	auto test = default_shader_->uniformLocation("mv");
//	if(default_shader_->uniformLocation("mv") != -1) {
	auto test2 = default_shader_->uniformLocation("light.pos");
		default_shader_->setUniformValue("mv", mv);
		default_shader_->setUniformValue("light.pos", light_->pos);
		default_shader_->setUniformValue("light.ambient", light_->ambient);
		default_shader_->setUniformValue("light.diffuse", light_->diffuse);
		default_shader_->setUniformValue("light.specular", light_->specular);
		default_shader_->setUniformValue("material.diffuse", material_.diffuse);
		default_shader_->setUniformValue("material.ambient", material_.ambient);
		default_shader_->setUniformValue("material.specular", material_.specular);
		default_shader_->setUniformValue("material.shininess", material_.shininess);
//	}
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
}

void BezierSurfaceStrip::reinit(QVector4D* pos) {
	this->vertices_.clear();
	this->normals_.clear();
	for (int f_i = 0; f_i < first_curve_->size(); f_i++) {
		QVector4D current_first = first_curve_->at(f_i);
		QVector4D current_second = second_curve_->at(f_i);
		vertices_.push_back(first_curve_->at(f_i));
		vertices_.push_back(second_curve_->at(f_i));
		if (first_curve_->normalsSet() && second_curve_->normalsSet()) {
			normals_.push_back(first_curve_->normalAt(f_i));
			normals_.push_back(second_curve_->normalAt(f_i));
		}
	}

	if (this->vertices_.size() != this->indices_.size()) {
		this->indices_.clear();
		for (int i = 0; i < this->vertices_.size(); i++) {
			this->indices_.push_back(i);
		}
	}
	Model::reinit(pos);

}

void BezierSurfaceStrip::setFirstCurve(BezierCurve* first) {
	this->first_curve_ = first;
}

void BezierSurfaceStrip::setSecondCurve(BezierCurve* second) {
	this->second_curve_ = second;
}
