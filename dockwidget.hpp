#pragma once
#include <QDockWidget>

class DockWidget : public QDockWidget {
	Q_OBJECT
public:
	DockWidget(QWidget *parent = nullptr);
signals:
	void closed();
protected:
	void closeEvent(QCloseEvent *event) override;
};
