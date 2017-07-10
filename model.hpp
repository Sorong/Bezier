#pragma once
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>

class Model : protected QOpenGLFunctions_3_3_Core
{
public:
	Model();
	explicit Model(QMatrix4x4 &model);
	Model(const Model&) = delete;
	Model &operator=(const Model&) = delete;
	Model(QMatrix4x4 &model, const QVector4D &pos);
	virtual ~Model();
	void setPosition(const QVector4D &pos_);
	virtual void init(QVector4D *position = nullptr) = 0;
	virtual void render(QMatrix4x4& projection, QMatrix4x4& view) = 0;
	virtual void reinit(QVector4D *position = nullptr);
	QVector4D at(int index) const;
	virtual int size() const;
	const QVector<QVector4D>& getVertices() const;
	QVector4D last() const;
	virtual void setDefaultShader(QOpenGLShaderProgram &prog);
	void setModelMatrix(QMatrix4x4& model);
	void rotate(qreal angle, qreal x, qreal y, qreal z = 0.0f);
	void rotate(qreal angle, const QVector3D & vector);
	void scale(qreal factor);
	virtual void setColor(QVector4D color);
	QMatrix4x4& getModelMatrix();
	void addNormalShader(QOpenGLShaderProgram& prog);
	void showNormals(bool show);
protected: 
	virtual void initBuffer();
	virtual QVector4D calculateNormals(QVector4D origin, QVector4D v2, QVector4D v3);
	QMatrix4x4 model_;
	QVector<QVector4D> vertices_;
	QVector<QVector4D> colors_;
	QVector<GLushort> indices_;
	QVector<QVector4D> normals_;
	QOpenGLShaderProgram* default_shader_;
	QOpenGLShaderProgram* normal_shader_;
	QVector4D pos_;
	GLuint vertexarrayobject_;
	GLuint position_buffer_;
	GLuint color_buffer_;
	GLuint index_buffer_;
	GLuint normal_buffer_;
	bool show_normals_;
};

