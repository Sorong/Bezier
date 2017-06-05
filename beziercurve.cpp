#include "beziercurve.hpp"
#include "beziercalculator.hpp"


BezierCurve::BezierCurve(QMatrix4x4& model, const QVector4D pos): Model(model, pos), coordinates_(nullptr) {
}

BezierCurve::BezierCurve(QMatrix4x4& model): Model(model), coordinates_(nullptr) {
}

BezierCurve::~BezierCurve()
{
}

void BezierCurve::setBaseCoordinates(QVector<QVector4D>* coordinates) {
	this->coordinates_ = coordinates;
}

QVector<QVector4D>& BezierCurve::getVertices() {
	return this->vertices_;
}

void BezierCurve::init(QVector4D* position) {
	if(this->coordinates_ == nullptr) {
		return;
	}
	BezierCalculator calculator;
	calculator.calculateBeziercurve(*this->coordinates_, this->vertices_);
	for (auto& vertex : vertices_) {
		if (vertex.w() == 0) {
			vertex.setW(1);
		}
		else {
			vertex /= vertex.w();
		}
	}
	this->colors_.fill(this->colors_.at(0), this->vertices_.size());
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
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &this->index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLushort), indices_.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void BezierCurve::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view  * (this->model_);
	for(auto& program : programs_) {
		program->bind();
		program->setUniformValue("mvp", mvp);
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_LINE_STRIP, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	}
	
}

int BezierCurve::size() const {
	return this->vertices_.size();
}

void BezierCurve::setColor(QVector3D color) {
	if(colors_.isEmpty()) {
		this->colors_.fill(color, 1);
	} else {
		this->colors_.fill(color);
	}
}

void BezierCurve::setModelMatrix(QMatrix4x4& model) {
	model_ = model;
}
