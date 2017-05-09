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
#include <QtWidgets/QCheckBox>
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
    QWidget *central_widget;
    QVBoxLayout *verticalLayout;
    BezierScreen *bezier;
    QWidget *settings_widget_;
    QHBoxLayout *horizontalLayout;
    QWidget *parameter_widget_;
    QVBoxLayout *verticalLayout_4;
    QWidget *t_widget_;
    QHBoxLayout *horizontalLayout_3;
    QLabel *t_label_;
    QSlider *t_slider_;
    QHBoxLayout *settings_layout_;
    QCheckBox *show_sublines_;
    QPushButton *show_derivation_;
    QPushButton *raise_elevation_;
    QWidget *point_widget_;
    QVBoxLayout *verticalLayout_3;
    QListWidget *list_widget_;
    QWidget *coord_widget_;
    QHBoxLayout *horizontalLayout_2;
    QLabel *x_label_;
    QSpinBox *x_coord_;
    QLabel *y_label_;
    QSpinBox *y_coord_;
    QPushButton *add_button_;
    QToolBar *main_toolbar_;
    QStatusBar *status_bar_;
    QMenuBar *menu_bar_;

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
        central_widget = new QWidget(BezierClass);
        central_widget->setObjectName(QStringLiteral("central_widget"));
        verticalLayout = new QVBoxLayout(central_widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        bezier = new BezierScreen(central_widget);
        bezier->setObjectName(QStringLiteral("bezier"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bezier->sizePolicy().hasHeightForWidth());
        bezier->setSizePolicy(sizePolicy1);
        bezier->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(bezier);

        settings_widget_ = new QWidget(central_widget);
        settings_widget_->setObjectName(QStringLiteral("settings_widget_"));
        settings_widget_->setMaximumSize(QSize(16777215, 200));
        horizontalLayout = new QHBoxLayout(settings_widget_);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 9, -1);
        parameter_widget_ = new QWidget(settings_widget_);
        parameter_widget_->setObjectName(QStringLiteral("parameter_widget_"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(parameter_widget_->sizePolicy().hasHeightForWidth());
        parameter_widget_->setSizePolicy(sizePolicy2);
        verticalLayout_4 = new QVBoxLayout(parameter_widget_);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        t_widget_ = new QWidget(parameter_widget_);
        t_widget_->setObjectName(QStringLiteral("t_widget_"));
        horizontalLayout_3 = new QHBoxLayout(t_widget_);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        t_label_ = new QLabel(t_widget_);
        t_label_->setObjectName(QStringLiteral("t_label_"));
        t_label_->setMinimumSize(QSize(75, 0));
        t_label_->setMaximumSize(QSize(150, 16777215));
        t_label_->setBaseSize(QSize(0, 0));
        QFont font;
        font.setPointSize(15);
        font.setBold(false);
        font.setWeight(50);
        t_label_->setFont(font);
        t_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        t_label_->setWordWrap(false);
        t_label_->setMargin(0);
        t_label_->setIndent(-1);

        horizontalLayout_3->addWidget(t_label_);

        t_slider_ = new QSlider(t_widget_);
        t_slider_->setObjectName(QStringLiteral("t_slider_"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(t_slider_->sizePolicy().hasHeightForWidth());
        t_slider_->setSizePolicy(sizePolicy3);
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        t_slider_->setFont(font1);
        t_slider_->setMaximum(10);
        t_slider_->setTracking(true);
        t_slider_->setOrientation(Qt::Horizontal);
        t_slider_->setInvertedAppearance(false);
        t_slider_->setInvertedControls(false);
        t_slider_->setTickPosition(QSlider::NoTicks);
        t_slider_->setTickInterval(1);

        horizontalLayout_3->addWidget(t_slider_);


        verticalLayout_4->addWidget(t_widget_);

        settings_layout_ = new QHBoxLayout();
        settings_layout_->setSpacing(6);
        settings_layout_->setObjectName(QStringLiteral("settings_layout_"));
        show_sublines_ = new QCheckBox(parameter_widget_);
        show_sublines_->setObjectName(QStringLiteral("show_sublines_"));
        show_sublines_->setTristate(false);

        settings_layout_->addWidget(show_sublines_);

        show_derivation_ = new QPushButton(parameter_widget_);
        show_derivation_->setObjectName(QStringLiteral("show_derivation_"));

        settings_layout_->addWidget(show_derivation_);

        raise_elevation_ = new QPushButton(parameter_widget_);
        raise_elevation_->setObjectName(QStringLiteral("raise_elevation_"));

        settings_layout_->addWidget(raise_elevation_);


        verticalLayout_4->addLayout(settings_layout_);


        horizontalLayout->addWidget(parameter_widget_);

        point_widget_ = new QWidget(settings_widget_);
        point_widget_->setObjectName(QStringLiteral("point_widget_"));
        point_widget_->setMinimumSize(QSize(50, 0));
        point_widget_->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(point_widget_);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        list_widget_ = new QListWidget(point_widget_);
        list_widget_->setObjectName(QStringLiteral("list_widget_"));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        list_widget_->setFont(font2);

        verticalLayout_3->addWidget(list_widget_);

        coord_widget_ = new QWidget(point_widget_);
        coord_widget_->setObjectName(QStringLiteral("coord_widget_"));
        horizontalLayout_2 = new QHBoxLayout(coord_widget_);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        x_label_ = new QLabel(coord_widget_);
        x_label_->setObjectName(QStringLiteral("x_label_"));

        horizontalLayout_2->addWidget(x_label_);

        x_coord_ = new QSpinBox(coord_widget_);
        x_coord_->setObjectName(QStringLiteral("x_coord_"));
        x_coord_->setMinimumSize(QSize(50, 0));
        x_coord_->setMinimum(-10);
        x_coord_->setMaximum(10);

        horizontalLayout_2->addWidget(x_coord_);

        y_label_ = new QLabel(coord_widget_);
        y_label_->setObjectName(QStringLiteral("y_label_"));

        horizontalLayout_2->addWidget(y_label_);

        y_coord_ = new QSpinBox(coord_widget_);
        y_coord_->setObjectName(QStringLiteral("y_coord_"));
        y_coord_->setMinimumSize(QSize(50, 0));
        y_coord_->setMinimum(-7);
        y_coord_->setMaximum(7);

        horizontalLayout_2->addWidget(y_coord_);

        add_button_ = new QPushButton(coord_widget_);
        add_button_->setObjectName(QStringLiteral("add_button_"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(add_button_->sizePolicy().hasHeightForWidth());
        add_button_->setSizePolicy(sizePolicy4);
        add_button_->setMaximumSize(QSize(200, 100));
        add_button_->setBaseSize(QSize(0, 0));
        add_button_->setLayoutDirection(Qt::LeftToRight);
        add_button_->setCheckable(false);
        add_button_->setAutoRepeat(false);

        horizontalLayout_2->addWidget(add_button_);


        verticalLayout_3->addWidget(coord_widget_);


        horizontalLayout->addWidget(point_widget_);


        verticalLayout->addWidget(settings_widget_);

        BezierClass->setCentralWidget(central_widget);
        main_toolbar_ = new QToolBar(BezierClass);
        main_toolbar_->setObjectName(QStringLiteral("main_toolbar_"));
        BezierClass->addToolBar(Qt::TopToolBarArea, main_toolbar_);
        status_bar_ = new QStatusBar(BezierClass);
        status_bar_->setObjectName(QStringLiteral("status_bar_"));
        BezierClass->setStatusBar(status_bar_);
        menu_bar_ = new QMenuBar(BezierClass);
        menu_bar_->setObjectName(QStringLiteral("menu_bar_"));
        menu_bar_->setGeometry(QRect(0, 0, 1024, 21));
        BezierClass->setMenuBar(menu_bar_);

        retranslateUi(BezierClass);

        QMetaObject::connectSlotsByName(BezierClass);
    } // setupUi

    void retranslateUi(QMainWindow *BezierClass)
    {
        BezierClass->setWindowTitle(QApplication::translate("BezierClass", "Bezier", 0));
        t_label_->setText(QApplication::translate("BezierClass", "t: 0.00", 0));
        show_sublines_->setText(QApplication::translate("BezierClass", "t-Linien anzeigen", 0));
        show_derivation_->setText(QApplication::translate("BezierClass", "Hodographen anzeigen", 0));
        raise_elevation_->setText(QApplication::translate("BezierClass", "Gradanhebung", 0));
        x_label_->setText(QApplication::translate("BezierClass", "X-Koordinate:", 0));
        y_label_->setText(QApplication::translate("BezierClass", "Y-Koordinate:", 0));
        add_button_->setText(QApplication::translate("BezierClass", "Hinzuf\303\274gen", 0));
    } // retranslateUi

};

namespace Ui {
    class BezierClass: public Ui_BezierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIER_H
