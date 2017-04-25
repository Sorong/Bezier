/********************************************************************************
** Form generated from reading UI file 'bezier.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEZIER_H
#define UI_BEZIER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <bezierscreen.h>

QT_BEGIN_NAMESPACE

class Ui_BezierClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    BezierScreen *openGLWidget;
    QGroupBox *groupBox;
    QSlider *horizontalSlider;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BezierClass)
    {
        if (BezierClass->objectName().isEmpty())
            BezierClass->setObjectName(QStringLiteral("BezierClass"));
        BezierClass->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BezierClass->sizePolicy().hasHeightForWidth());
        BezierClass->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(BezierClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        openGLWidget = new BezierScreen(centralWidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(openGLWidget->sizePolicy().hasHeightForWidth());
        openGLWidget->setSizePolicy(sizePolicy1);
        openGLWidget->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(openGLWidget);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
		groupBox->setMaximumSize(QSize(16777215, 75));
        horizontalSlider = new QSlider(groupBox);
        horizontalSlider->setObjectName(QStringLiteral("t_slider"));
        horizontalSlider->setGeometry(QRect(30, 30, 160, 22));
        horizontalSlider->setOrientation(Qt::Horizontal);
		horizontalSlider->setRange(-10, 20);
		horizontalSlider->setSingleStep(1);
		horizontalSlider->setValue(0);
		openGLWidget->set_t(0);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(210, 30, 47, 13));

        verticalLayout->addWidget(groupBox);

        BezierClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BezierClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        BezierClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BezierClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BezierClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BezierClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BezierClass->setStatusBar(statusBar);

        retranslateUi(BezierClass);

        QMetaObject::connectSlotsByName(BezierClass);
    } // setupUi

    void retranslateUi(QMainWindow *BezierClass)
    {
        BezierClass->setWindowTitle(QApplication::translate("BezierClass", "Bezier", 0));
        groupBox->setTitle(QApplication::translate("BezierClass", "GroupBox", 0));
		QString floatAsString = QString::number(this->horizontalSlider->value(), 2);
     //   label->setText(QApplication::translate("BezierClass", "TextLabel", 0));
		label->setText(floatAsString);
    } // retranslateUi

};

namespace Ui {
    class BezierClass: public Ui_BezierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIER_H
