#include "controlgrid.hpp"




ControlGrid::ControlGrid(QVector4D start, QVector4DMatrix start_mat)
	: Clickable(start) {
	if(start_mat.empty()) {
		this->distance_.fill({ 0,0,0,0 }, 1);
	} 
	QVector<QVector4D> prepend = { start };
	for(int i = 0; i < start_mat.size() - 1; i++) {
		if (!start_mat[i].isEmpty() && !start_mat[i+1].isEmpty()) {
			distance_.push_back(start_mat[i + 1][0] - start);
		} else {
			distance_.push_back({ 0,0,0,0 });
		}
		prepend.push_back(start + distance_.last());
	}
	for(int j = 0; j < start_mat.size(); j++) {
		start_mat[j].push_back(prepend[j]);
	}
	this->coordinates_ = start_mat;
}

ControlGrid::~ControlGrid() {
}

void ControlGrid::init(QVector4D* position) {
	if (!default_shader_ ) {
		return;
	}
	if (position) {
		this->setPosition(*position);
	}
	auto horizonal_length = this->coordinates_.at(0).size();
	auto vertical_length = this->coordinates_.size();
	for (auto m = 0; m < vertical_length; m++) {
		auto n = 0;
		for (; n < horizonal_length; n++) {
			this->vertices_.push_back(this->coordinates_[m][n]);
			if (n != horizonal_length - 1) {
				this->indices_.push_back((m * horizonal_length + n));
				this->indices_.push_back(m * horizonal_length + n + 1);
			}
			if (m != 0) {
				this->indices_.push_back(((m - 1) * horizonal_length + n));
				this->indices_.push_back((m * horizonal_length + n));
			}
		}
	}
	if (this->colors_.isEmpty()) {
		this->colors_.push_back({ 0,0,0,1 });
	}

	this->colors_.fill({ 0,0,0,1 }, this->vertices_.size());



	Model::initBuffer();
	glBindVertexArray(0);
}

void ControlGrid::reinit(QVector4D* position) {
	for(int i = 0; i < coordinates_.size(); i++) {
			coordinates_[i][0] = *this->reference_vertex_ + distance_[i];
	}
	glBindVertexArray(this->vertexarrayobject_);
	glBindBuffer(GL_ARRAY_BUFFER, this->position_buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(QVector4D), vertices_.data(), GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void ControlGrid::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view * model_;
	default_shader_->bind();
	default_shader_->setUniformValue("mvp", mvp);
	glBindVertexArray(this->vertexarrayobject_);
	glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
	glBindVertexArray(0);
}

void ControlGrid::translateToReference() {
}

void ControlGrid::setClicked(QVector4D& color) {
}

void ControlGrid::setUnclicked(QVector4D& color) {
}
