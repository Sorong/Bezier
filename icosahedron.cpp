#include "icosahedron.hpp"


Icosahedron::Icosahedron(): Model(), reference_vertex_(nullptr) {
	setRadius(1);
}


Icosahedron::Icosahedron(QMatrix4x4& model, QVector4D* reference_vertex) : Model(model), reference_vertex_(reference_vertex) {
	setRadius(1);
	if(reference_vertex != nullptr) {
		this->setPosition(*reference_vertex);
	}
}

Icosahedron::~Icosahedron()
{
}

void Icosahedron::init(QVector4D *position) {
	if (reference_vertex_ == nullptr || programs_.isEmpty()) {
		return;
	}
	if(position) {
		this->setPosition(*position);
	}

	auto reference_normalized = this->reference_vertex_->w() != 0 ? this->reference_vertex_->toVector3DAffine() : this->reference_vertex_->toVector3D();
	this->vertices_ = {
		{ -radius_, 0, 1 ,1},{ radius_, 0, 1 ,1},{ -radius_, 0, -1 ,1},{ radius_, 0, -1 ,1},
		{ 0, 1, radius_ ,1},{ 0, 1, -radius_ ,1},{ 0, -1, radius_ ,1},{ 0, -1, -radius_ ,1},
		{ 1, radius_, 0 ,1},{ -1, radius_, 0 ,1},{ 1, -radius_, 0 ,1},{ -1, -radius_, 0 ,1}
	

	/*	{radius_, 1, 0, 1}, {-radius_, 1, 0, 1}, {radius_, -1, 0, 1},
		{-radius_, -1, 0, 1}, {1, 0, radius_, 1}, {1, 0, -radius_, 1},
		{-1, 0, radius_, 1}, {-1, 0, -radius_, 1}, {0, radius_,1 ,1 },
		{0, -radius_, 1, 1}, {0, radius_, -1, 1}, {0, -radius_, -1, 1}*/
	};
	this->indices_ = {
		/*0,8,4,
		1,10,7,
		2,9,11,
		7,3,1,
		0,5,10,
		3,9,6,
		3,11,9,
		8,6,4,
		2,4,9,
		3,7,11,
		4,2,0,
		9,4,6,
		2,11,5,
		0,10,8,
		5,0,2,
		10,5,7,
		1,6,8,
		1,8,10,
		6,1,3,
		11,7,5*/
			1, 4, 0, 4, 9, 0, 4, 5, 9, 8, 5, 4,	1, 8, 4, 
	1, 10, 8, 10, 3, 8, 8, 3, 5, 3, 2, 5, 3, 7, 2, 
	3, 10, 7, 10, 6, 7, 6, 11, 7, 6, 0, 11,	6, 1, 0, 
	10, 1, 6, 11, 0, 9, 2, 11, 9, 5, 2, 9, 11, 2, 7
	};
	this->colors_.fill(this->color_, this->vertices_.size());
	auto prog_id = this->programs_.at(0)->bind();
	GLuint pos;


	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &this->vertexarrayobject_);
	glBindVertexArray(this->vertexarrayobject_);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &this->position_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, this->position_buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(QVector4D), vertices_.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(prog_id, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &this->color_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_);
	glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(QVector4D), colors_.data(), GL_DYNAMIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(prog_id, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &this->index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLushort), indices_.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void Icosahedron::render(QMatrix4x4& projection, QMatrix4x4& view) {
	auto mvp = projection * view * model_;
	for (auto &prog : programs_) {
	    prog->bind();
		prog->setUniformValue("mvp", mvp);
	auto i =	prog->uniformLocation("mvp");
		glBindVertexArray(this->vertexarrayobject_);
		glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_SHORT, nullptr);
		glBindVertexArray(0);
	}
}

void Icosahedron::reinit() {
	if (this->vertexarrayobject_) {
		glDeleteVertexArrays(1, &this->vertexarrayobject_);
		glDeleteBuffers(1, &index_buffer_);
		glDeleteBuffers(1, &color_buffer_);
		glDeleteBuffers(1, &position_buffer_);
	}
	this->colors_.fill(this->color_);
	auto prog_id = this->programs_.at(0)->bind();
	GLuint pos;


	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &this->vertexarrayobject_);
	glBindVertexArray(this->vertexarrayobject_);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &this->position_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, this->position_buffer_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(QVector4D), vertices_.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(prog_id, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &this->color_buffer_);
	glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_);
	glBufferData(GL_ARRAY_BUFFER, colors_.size() * sizeof(QVector4D), colors_.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(prog_id, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &this->index_buffer_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLushort), indices_.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);
}

void Icosahedron::setRadius(float i) {
	int asInt = i * 100;
	if (asInt == 0) { return; }
	this->radius_ = (i / 4) * (1 + 2.236067977);
}

void Icosahedron::setColor(QVector4D color) {
	this->color_ = color;
	this->colors_.fill(color);
	glBindVertexArray(this->vertexarrayobject_);
	glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer_);
	glBufferSubData(GL_ARRAY_BUFFER, 0, colors_.size() * sizeof(QVector4D), colors_.data());
	glBindVertexArray(0);
}

void Icosahedron::scale(float ratio) {
	this->model_.scale(ratio);
}

void Icosahedron::translateToReference() {
	this->model_.translate(reference_vertex_->toVector3DAffine());
}

QVector4D* Icosahedron::getReference() const {
	return this->reference_vertex_;
}
