#include "trianglestrip.hpp"

TriangleStrip::TriangleStrip(QMatrix4x4& model, BezierCurve* first_curve, BezierCurve* second_curve)
	: Model(model),
	first_curve_(first_curve),
	second_curve_(second_curve) {
}

TriangleStrip::TriangleStrip(QMatrix4x4& model, const QVector4D& pos, BezierCurve* first_curve, BezierCurve* second_curve)
	: Model(model, pos),
	first_curve_(first_curve),
	second_curve_(second_curve) {
}

void TriangleStrip::init(QVector4D* position) {
	if (programs_.isEmpty() || first_curve_->size() != second_curve_->size()) {
		return;
	}
	for (int f_i = 0; f_i < first_curve_->size(); f_i++) {
		QVector4D current_first = first_curve_->at(f_i);
		QVector4D current_second = second_curve_->at(f_i);
		if(current_first.w() != 0) {
			current_first /= current_first.w();
		} else {
			current_first.setW(1);
		}
		if (current_second.w() != 0) {
			current_second /= current_second.w();
		}
		else {
			current_second.setW(1);
		}
		vertices_.push_back(first_curve_->at(f_i));
		vertices_.push_back(second_curve_->at(f_i));
	}



	QVector<QVector4D> vertices = this->vertices_;
	for (auto& vertex : vertices) {
		if (vertex.w() == 0) {
			vertex.setW(1);
		}
		else {
			vertex /= vertex.w();
		}
	}
	colors_.fill({ 1,0,0,.5f }, this->vertices_.size());
	for (int i = 0; i < this->vertices_.size(); i++) {
		this->indices_.push_back(i);
	}
	Model::initBuffer();
	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void TriangleStrip::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view  * (this->model_);
	for (auto& program : programs_) {
		program->bind();
		program->setUniformValue("mvp", mvp);
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	}

}

void TriangleStrip::reinit(QVector4D* pos) {
	this->vertices_.clear();
	for (int f_i = 0; f_i < first_curve_->size(); f_i++) {
		QVector4D current_first = first_curve_->at(f_i);
		QVector4D current_second = second_curve_->at(f_i);
		if (current_first.w() != 0) {
			current_first /= current_first.w();
		}
		else {
			current_first.setW(1);
		}
		if (current_second.w() != 0) {
			current_second /= current_second.w();
		}
		else {
			current_second.setW(1);
		}
		vertices_.push_back(first_curve_->at(f_i));
		vertices_.push_back(second_curve_->at(f_i));
	}

	if(this->vertices_.size() != this->indices_.size()) {
		this->indices_.clear();
		for (int i = 0; i < this->vertices_.size(); i++) {
			this->indices_.push_back(i);
		}
	}
	Model::reinit(pos);

}

void TriangleStrip::setFirstCurve(BezierCurve* first) {
	this->first_curve_ = first;
}

void TriangleStrip::setSecondCurve(BezierCurve* second) {
	this->second_curve_ = second;
}
