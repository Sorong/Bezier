#pragma once
#include <QVector4D>

class Clickable
{
public:
	explicit Clickable(QVector4D& reference_vertex);
	virtual ~Clickable();
	virtual void translateToReference() = 0;
	virtual void setClicked(QVector4D& color) = 0;
	virtual void setUnclicked(QVector4D& color) = 0;
	virtual QVector4D& getReference() const;
protected:
	QVector4D &reference_vertex_;
};

