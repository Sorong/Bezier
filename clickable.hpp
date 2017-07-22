#pragma once
#include <QVector4D>
#include <QOpenGLShaderProgram>

class Clickable
{
public:
	explicit Clickable(QVector4D& reference_vertex);
	virtual ~Clickable();
	virtual void translateToReference() = 0;
	virtual void setClicked(QVector4D& color) = 0;
	virtual void setUnclicked(QVector4D& color) = 0;
	virtual void setUnclicked();
	virtual QVector4D& getReference() const;
	virtual void setClickShader(QOpenGLShaderProgram &shader);
protected:
	void setReference(QVector4D& reference);
	QOpenGLShaderProgram *click_shader_;
	QVector4D *reference_vertex_;
};

