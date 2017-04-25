#include "line.h"


Line::Line(QMatrix4x4* model, QMatrix4x4* view, QMatrix4x4* projection, QVector3D color, QVector<QVector3D> points): vertexarrayobject(0), position_buffer(0), color_buffer(0), index_buffer(0)
{
	this->model = new QMatrix4x4(*model);
	this->view = view;
	this->projection = projection;
	this->vertices = QVector<QVector3D>(points);
	this->colors.push_back(this->vertices.size() != 1 ? QVector3D(color): QVector3D(1,1,1));
	this->program = nullptr;

	QOpenGLFunctions_3_3_Core::initializeOpenGLFunctions();
}

Line::~Line()
{
	glDeleteVertexArrays(1, &this->vertexarrayobject);
	glDeleteBuffers(1, &index_buffer);
	glDeleteBuffers(1, &color_buffer);
	glDeleteBuffers(1, &position_buffer);
	delete this->model;
}

void Line::setPosition(QVector3D pos)
{
	this->pos = QVector3D(pos);
}

void Line::setShader(QOpenGLShaderProgram* program)
{
	this->program = program;
}

void Line::render_line()
{
	auto mvp = *(this->projection) * *(this->view) * *(this->model);
	auto mv = *(this->view) * *(this->model);
	auto i = this->program->bind();
	this->program->setUniformValue("mvp", mvp);
	qDebug() << this->program->uniformLocation("mvp");
	this->program->setUniformValue("ModelViewMatrix", mv);
	glBindVertexArray(this->vertexarrayobject);
	if(this->vertices.size() != 1)
	{
		glDrawElements(GL_LINE_STRIP, indices.size(), GL_UNSIGNED_SHORT, nullptr);
	} else
	{
		glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_SHORT, nullptr);
	}
	
	glBindVertexArray(0);

}

void Line::init_line()
{
	if (program == nullptr) { return; }
	QVector3D col = this->colors.at(0);
	while(this->colors.size() < this->vertices.size())
	{
		colors.push_back({ col });
	}
	for (int i = 0; i < this->vertices.size(); i++)
	{
		this->indices.push_back(i);
	}
	GLuint progId = this->program->programId();
	GLuint pos;

	// Step 0: Create vertex array object.
	glGenVertexArrays(1, &this->vertexarrayobject);
	glBindVertexArray(this->vertexarrayobject);

	// Step 1: Create vertex buffer object for position attribute and bind it to the associated "shader attribute".
	glGenBuffers(1, &this->position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->position_buffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(QVector3D), vertices.data(), GL_STATIC_DRAW);

	// Bind it to position.
	pos = glGetAttribLocation(progId, "position");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 2: Create vertex buffer object for color attribute and bind it to...
	glGenBuffers(1, &this->color_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->color_buffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(QVector3D), colors.data(), GL_STATIC_DRAW);

	// Bind it to color.
	pos = glGetAttribLocation(progId, "color");
	glEnableVertexAttribArray(pos);
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Step 3: Create vertex buffer object for indices. No binding needed here.
	glGenBuffers(1, &this->index_buffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(), GL_STATIC_DRAW);

	// Unbind vertex array object (back to default).
	glBindVertexArray(0);


	// Modify model matrix.
	this->model->translate(this->pos);
}

QVector3D Line::at(int index) const
{
	return this->vertices.at(index);
}

int Line::size() const
{
	return this->vertices.size();
}
