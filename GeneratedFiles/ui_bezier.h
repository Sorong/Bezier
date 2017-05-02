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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "bezierscreen.h"

QT_BEGIN_NAMESPACE

class Ui_BezierClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    BezierScreen *bezier;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *tWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *tLabel;
    QSlider *tSlider;
    QWidget *pointWidget;
    QVBoxLayout *verticalLayout_3;
    QListWidget *listWidget;
    QWidget *coordWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *xLabel;
    QSpinBox *xCoord;
    QLabel *yLabel;
    QSpinBox *yCoord;
    QPushButton *addButton;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *BezierClass)
    {
        if (BezierClass->objectName().isEmpty())
            BezierClass->setObjectName(QStringLiteral("BezierClass"));
        BezierClass->resize(1024, 768);
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
        bezier = new BezierScreen(centralWidget);
        bezier->setObjectName(QStringLiteral("bezier"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bezier->sizePolicy().hasHeightForWidth());
        bezier->setSizePolicy(sizePolicy1);
        bezier->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(bezier);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMaximumSize(QSize(16777215, 200));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 9, -1);
        tWidget = new QWidget(widget);
        tWidget->setObjectName(QStringLiteral("tWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tWidget->sizePolicy().hasHeightForWidth());
        tWidget->setSizePolicy(sizePolicy2);
        horizontalLayout_3 = new QHBoxLayout(tWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tLabel = new QLabel(tWidget);
        tLabel->setObjectName(QStringLiteral("tLabel"));
        tLabel->setMinimumSize(QSize(50, 0));
        tLabel->setMaximumSize(QSize(150, 16777215));
        QFont font;
        font.setPointSize(15);
        font.setBold(false);
        font.setWeight(50);
        tLabel->setFont(font);
        tLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        tLabel->setWordWrap(false);
        tLabel->setMargin(15);
        tLabel->setIndent(-1);

        horizontalLayout_3->addWidget(tLabel);

        tSlider = new QSlider(tWidget);
        tSlider->setObjectName(QStringLiteral("tSlider"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tSlider->sizePolicy().hasHeightForWidth());
        tSlider->setSizePolicy(sizePolicy3);
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        tSlider->setFont(font1);
        tSlider->setMaximum(10);
        tSlider->setTracking(true);
        tSlider->setOrientation(Qt::Horizontal);
        tSlider->setInvertedAppearance(false);
        tSlider->setInvertedControls(false);
        tSlider->setTickPosition(QSlider::NoTicks);
        tSlider->setTickInterval(1);

        horizontalLayout_3->addWidget(tSlider);


        horizontalLayout->addWidget(tWidget);

        pointWidget = new QWidget(widget);
        pointWidget->setObjectName(QStringLiteral("pointWidget"));
        pointWidget->setMinimumSize(QSize(50, 0));
        pointWidget->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(pointWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        listWidget = new QListWidget(pointWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setFont(font);

        verticalLayout_3->addWidget(listWidget);

        coordWidget = new QWidget(pointWidget);
        coordWidget->setObjectName(QStringLiteral("coordWidget"));
        horizontalLayout_2 = new QHBoxLayout(coordWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        xLabel = new QLabel(coordWidget);
        xLabel->setObjectName(QStringLiteral("xLabel"));

        horizontalLayout_2->addWidget(xLabel);

        xCoord = new QSpinBox(coordWidget);
        xCoord->setObjectName(QStringLiteral("xCoord"));
        xCoord->setMinimumSize(QSize(50, 0));
        xCoord->setMinimum(-10);
        xCoord->setMaximum(10);

        horizontalLayout_2->addWidget(xCoord);

        yLabel = new QLabel(coordWidget);
        yLabel->setObjectName(QStringLiteral("yLabel"));

        horizontalLayout_2->addWidget(yLabel);

        yCoord = new QSpinBox(coordWidget);
        yCoord->setObjectName(QStringLiteral("yCoord"));
        yCoord->setMinimumSize(QSize(50, 0));
        yCoord->setMinimum(-7);
        yCoord->setMaximum(7);

        horizontalLayout_2->addWidget(yCoord);

        addButton = new QPushButton(coordWidget);
        addButton->setObjectName(QStringLiteral("addButton"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(addButton->sizePolicy().hasHeightForWidth());
        addButton->setSizePolicy(sizePolicy4);
        addButton->setMaximumSize(QSize(200, 100));
        addButton->setBaseSize(QSize(0, 0));
        addButton->setLayoutDirection(Qt::LeftToRight);
        addButton->setCheckable(false);
        addButton->setAutoRepeat(false);

        horizontalLayout_2->addWidget(addButton);


        verticalLayout_3->addWidget(coordWidget);


        horizontalLayout->addWidget(pointWidget);


        verticalLayout->addWidget(widget);

        BezierClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(BezierClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        BezierClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BezierClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        BezierClass->setStatusBar(statusBar);
        menuBar = new QMenuBar(BezierClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 21));
        BezierClass->setMenuBar(menuBar);

        retranslateUi(BezierClass);

        QMetaObject::connectSlotsByName(BezierClass);
    } // setupUi

    void retranslateUi(QMainWindow *BezierClass)
    {
        BezierClass->setWindowTitle(QApplication::translate("BezierClass", "Bezier", 0));
        tLabel->setText(QApplication::translate("BezierClass", "t: 0.00", 0));
        xLabel->setText(QApplication::translate("BezierClass", "X-Koordinate:", 0));
        yLabel->setText(QApplication::translate("BezierClass", "Y-Koordinate:", 0));
        addButton->setText(QApplication::translate("BezierClass", "Hinzuf\303\274gen", 0));
    } // retranslateUi

};

namespace Ui {
    class BezierClass: public Ui_BezierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIER_H
