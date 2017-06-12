#include "dockwidget.hpp"

DockWidget::DockWidget(QWidget* parent) : QDockWidget(parent) {
	
}

void DockWidget::closeEvent(QCloseEvent* event) {
	emit closed();
	QDockWidget::closeEvent(event);
}