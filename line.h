#include <QOpenGLFunctions_3_3_Core>
#include <QVector>
#include <QVector3D>
#include <QOpenGLShaderProgram>

#ifndef LINES_H
#define LINES_H


class Line : protected QOpenGLFunctions_3_3_Core
{
public:
	Line(QMatrix4x4* model, QMatrix4x4* view, QMatrix4x4* projection, QVector3D color, QVector<QVector3D> points);
	~Line();
	void setPosition(QVector3D pos);
	void setShader(QOpenGLShaderProgram* program);
	void render_line();
	void init_line();
	QVector3D at(int index) const;
	int size() const;

private:

	QMatrix4x4 *model, *view, *projection;
	QVector<QVector3D> vertices, colors;
	QVector<GLushort> indices;
	QOpenGLShaderProgram *program;
	QVector3D pos;
	GLuint vertexarrayobject;
	GLuint position_buffer;
	GLuint color_buffer;
	GLuint index_buffer;
};

#endif // LINES_H
