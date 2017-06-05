#include "beziersurface.hpp"


BezierSurface::BezierSurface(QMatrix4x4& model, const QVector4D& pos): Model(model, pos) {
}

BezierSurface::~BezierSurface()
{
}

void BezierSurface::init(QVector4D *position) {
	if(programs_.isEmpty()) {
		return;
	}
	auto horizonal_length = this->coordinates_.at(0).size();
	auto vertical_length = this->coordinates_.size();
	for (auto m = 0; m < vertical_length; m++) {
		auto n = 0;
		for (; n < horizonal_length; n++) {
			this->vertices_.push_back(this->coordinates_.at(m).at(n));
			this->base_points_.push_back(std::make_shared<Icosahedron>(model_, &this->coordinates_.at(m).at(n)));
			if(n != horizonal_length - 1) {
				this->indices_.push_back((m * horizonal_length + n));
				this->indices_.push_back(m * horizonal_length + n + 1);
			}
		
			if(m != 0) {
				this->indices_.push_back(((m - 1) * horizonal_length + n));
				this->indices_.push_back((m * horizonal_length + n));
			}
		}
	/*	this->vertices_.push_back(this->coordinates_.at(m).at(n));
		this->indices_.push_back((m * horizonal_length + n));
		this->indices_.push_back((m * horizonal_length + ((n+1))));*/
	}
	this->colors_.fill({0,1,0}, this->vertices_.size());
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
	for(auto& ico : base_points_) {
		ico->addShader(*this->programs_.at(0));
		ico->setColor({ 1,1,1 });
		ico->init();
		ico->scale(0.05);
	}
	// Unbind vertex array object (
}

void BezierSurface::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view * model_;
	for(auto& program : programs_) {
		program->setUniformValue("mvp", mvp);
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_LINES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	}
	for(auto& ico : base_points_) {
		ico->render(projection, view);
	}
}

void BezierSurface::reinit(QVector4D* pos) {
	glDeleteVertexArrays(1, &this->vertexarrayobject_);
	glDeleteBuffers(1, &index_buffer_);
	glDeleteBuffers(1, &color_buffer_);
	glDeleteBuffers(1, &position_buffer_);
	init(pos);
	this->base_points_.clear();
}

void BezierSurface::setT(float t) {
	this->t_ = t;
}

void BezierSurface::setS(float s) {
	this->s_ = s;
}

void BezierSurface::addCoordinates(QVector<QVector4D> coordinates) {
}

void BezierSurface::setCoordinates(QVector<QVector<QVector4D>> coordinates) {
	this->coordinates_ = coordinates;
}

const QVector4D* BezierSurface::get(int index) const {
	return this->base_points_.at(index)->getReference();
}
