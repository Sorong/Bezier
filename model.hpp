#pragma once
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

class Model : protected QOpenGLFunctions_3_3_Core
{
public:
	Model();
	explicit Model(QMatrix4x4 &model);
	Model(QMatrix4x4 &model, const QVector4D &pos);
	virtual ~Model();
	void setPosition(const QVector4D &pos_);
	virtual void init(QVector4D *position = nullptr) = 0;
	virtual void render(QMatrix4x4& projection, QMatrix4x4& view) = 0;
	QVector4D at(int index) const;
	int size() const;
	const QVector<QVector4D>& getVertices() const;
	QVector4D last() const;
	void addShader(QOpenGLShaderProgram &prog);
	void removeShader(int index);
protected: 
	QMatrix4x4 model_;
	QVector<QVector4D> vertices_;
	QVector<QVector3D> colors_;
	QVector<GLushort> indices_;
	QVector<QOpenGLShaderProgram*> programs_;
	QVector4D pos_;
	GLuint vertexarrayobject_;
	GLuint position_buffer_;
	GLuint color_buffer_;
	GLuint index_buffer_;
};

