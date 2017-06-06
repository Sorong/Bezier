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
	GLuint progId = this->programs_.at(0)->programId();
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
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &this->index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLushort), indices_.data(), GL_STATIC_DRAW);

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

void TriangleStrip::setFirstCurve(BezierCurve* first) {
	this->first_curve_ = first;
}

void TriangleStrip::setSecondCurve(BezierCurve* second) {
	this->second_curve_ = second;
}
