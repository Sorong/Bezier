#include <QOpenGLFunctions_3_3_Core>
#include <QVector>
#include <QVector3D>
#include <QOpenGLShaderProgram>

#ifndef LINES_H
#define LINES_H


class Line : protected QOpenGLFunctions_3_3_Core {
public:
	Line(QMatrix4x4* model, QMatrix4x4* view, QMatrix4x4* projection, QVector3D color, QVector<QVector4D> points);
	~Line();
	void setPosition(QVector4D pos);
	void setShader(QOpenGLShaderProgram* program);
	void renderLine();
	void initLine();
	void addVertex(QVector4D vertex);
	QVector4D at(int index) const;
	int size() const;
	QVector<QVector4D> getVertices() const;
	QVector4D at(int i);
	QVector4D last();

private:

	QMatrix4x4 *model_, *view_, *projection_;
	QVector<QVector4D> vertices_;
	QVector<QVector3D> colors_;
	QVector<GLushort> indices_;
	QOpenGLShaderProgram* program_;
	QVector4D pos_;
	GLuint vertexarrayobject_;
	GLuint position_buffer_;
	GLuint color_buffer_;
	GLuint index_buffer_;
};

#endif // LINES_H
