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
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "glview.hpp"

QT_BEGIN_NAMESPACE

class Ui_BezierClass
{
public:
    QWidget *central_widget;
    QVBoxLayout *verticalLayout;
    GLView *glview;
    QWidget *settings_widget_;
    QHBoxLayout *horizontalLayout;
    QWidget *parameter_widget_;
    QVBoxLayout *verticalLayout_4;
    QWidget *t_widget_;
    QHBoxLayout *horizontalLayout_3;
    QWidget *point_widget_;
    QVBoxLayout *verticalLayout_3;
    QListWidget *list_widget_;
    QWidget *coord_widget_;
    QHBoxLayout *horizontalLayout_2;
    QLabel *x_label_;
    QSpinBox *x_coord_;
    QLabel *y_label_;
    QSpinBox *y_coord_;
    QLabel *weigh_label_;
    QDoubleSpinBox *weight_;
    QPushButton *add_button_;
    QStatusBar *status_bar_;
    QMenuBar *menu_bar_;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_;
    QDoubleSpinBox *doubleSpinBox_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_1;
    QDoubleSpinBox *doubleSpinBox_3;
    QSpacerItem *verticalSpacer_4;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_4;
    QSpacerItem *verticalSpacer_5;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *t_label_1;
    QCheckBox *show_derivation_;
    QSlider *t_slider_;
    QCheckBox *show_sublines_;
    QSlider *t_slider_1;
    QLabel *t_label_;
    QPushButton *raise_elevation_;

    void setupUi(QMainWindow *BezierClass)
    {
        if (BezierClass->objectName().isEmpty())
            BezierClass->setObjectName(QStringLiteral("BezierClass"));
        BezierClass->resize(1279, 762);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BezierClass->sizePolicy().hasHeightForWidth());
        BezierClass->setSizePolicy(sizePolicy);
        BezierClass->setDocumentMode(false);
        BezierClass->setTabShape(QTabWidget::Rounded);
        BezierClass->setDockNestingEnabled(false);
        central_widget = new QWidget(BezierClass);
        central_widget->setObjectName(QStringLiteral("central_widget"));
        central_widget->setMouseTracking(false);
        verticalLayout = new QVBoxLayout(central_widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        glview = new GLView(central_widget);
        glview->setObjectName(QStringLiteral("glview"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(glview->sizePolicy().hasHeightForWidth());
        glview->setSizePolicy(sizePolicy1);
        glview->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(glview);

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

        verticalLayout_4->addWidget(t_widget_);


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
        QFont font;
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        list_widget_->setFont(font);

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

        weigh_label_ = new QLabel(coord_widget_);
        weigh_label_->setObjectName(QStringLiteral("weigh_label_"));

        horizontalLayout_2->addWidget(weigh_label_);

        weight_ = new QDoubleSpinBox(coord_widget_);
        weight_->setObjectName(QStringLiteral("weight_"));
        weight_->setMinimum(0.01);
        weight_->setValue(1);

        horizontalLayout_2->addWidget(weight_);

        add_button_ = new QPushButton(coord_widget_);
        add_button_->setObjectName(QStringLiteral("add_button_"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(add_button_->sizePolicy().hasHeightForWidth());
        add_button_->setSizePolicy(sizePolicy3);
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
        status_bar_ = new QStatusBar(BezierClass);
        status_bar_->setObjectName(QStringLiteral("status_bar_"));
        BezierClass->setStatusBar(status_bar_);
        menu_bar_ = new QMenuBar(BezierClass);
        menu_bar_->setObjectName(QStringLiteral("menu_bar_"));
        menu_bar_->setGeometry(QRect(0, 0, 1279, 21));
        BezierClass->setMenuBar(menu_bar_);
        dockWidget = new QDockWidget(BezierClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setEnabled(true);
        dockWidget->setMinimumSize(QSize(270, 42));
        dockWidget->setMaximumSize(QSize(524287, 400));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayoutWidget = new QWidget(dockWidgetContents);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 261, 200));
        gridLayoutWidget->setMaximumSize(QSize(16777215, 400));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        formLayout->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        formLayout->setContentsMargins(20, -1, -1, -1);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(0, QFormLayout::FieldRole, verticalSpacer);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMinimumSize(QSize(80, 0));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        doubleSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setMinimum(-1024);
        doubleSpinBox->setMaximum(1024);

        formLayout->setWidget(1, QFormLayout::FieldRole, doubleSpinBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(2, QFormLayout::FieldRole, verticalSpacer_2);

        label_ = new QLabel(gridLayoutWidget);
        label_->setObjectName(QStringLiteral("label_"));
        sizePolicy2.setHeightForWidth(label_->sizePolicy().hasHeightForWidth());
        label_->setSizePolicy(sizePolicy2);
        label_->setMinimumSize(QSize(80, 0));
        label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_);

        doubleSpinBox_2 = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        doubleSpinBox_2->setMinimum(-1024);
        doubleSpinBox_2->setMaximum(1024);

        formLayout->setWidget(3, QFormLayout::FieldRole, doubleSpinBox_2);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::FieldRole, verticalSpacer_3);

        label_1 = new QLabel(gridLayoutWidget);
        label_1->setObjectName(QStringLiteral("label_1"));
        sizePolicy2.setHeightForWidth(label_1->sizePolicy().hasHeightForWidth());
        label_1->setSizePolicy(sizePolicy2);
        label_1->setMinimumSize(QSize(80, 0));
        label_1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_1);

        doubleSpinBox_3 = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));
        doubleSpinBox_3->setMinimum(-1024);
        doubleSpinBox_3->setMaximum(1024);

        formLayout->setWidget(5, QFormLayout::FieldRole, doubleSpinBox_3);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(6, QFormLayout::FieldRole, verticalSpacer_4);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMinimumSize(QSize(80, 0));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(7, QFormLayout::LabelRole, label_3);

        doubleSpinBox_4 = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_4->setObjectName(QStringLiteral("doubleSpinBox_4"));
        doubleSpinBox_4->setMinimum(-1024);
        doubleSpinBox_4->setMaximum(1024);

        formLayout->setWidget(7, QFormLayout::FieldRole, doubleSpinBox_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(8, QFormLayout::FieldRole, verticalSpacer_5);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        horizontalLayoutWidget = new QWidget(dockWidgetContents);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 200, 349, 80));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(horizontalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_4->addWidget(pushButton);

        pushButton_2 = new QPushButton(horizontalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);

        dockWidget->setWidget(dockWidgetContents);
        BezierClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);
        dockWidget_2 = new QDockWidget(BezierClass);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidget_2->setMinimumSize(QSize(270, 38));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        gridLayoutWidget_2 = new QWidget(dockWidgetContents_2);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(0, 0, 277, 561));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(20, 0, 0, 0);
        t_label_1 = new QLabel(gridLayoutWidget_2);
        t_label_1->setObjectName(QStringLiteral("t_label_1"));
        t_label_1->setMinimumSize(QSize(75, 0));
        t_label_1->setMaximumSize(QSize(150, 16777215));
        t_label_1->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setWeight(50);
        t_label_1->setFont(font1);
        t_label_1->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        t_label_1->setWordWrap(false);
        t_label_1->setMargin(0);
        t_label_1->setIndent(-1);

        gridLayout_2->addWidget(t_label_1, 1, 0, 1, 1);

        show_derivation_ = new QCheckBox(gridLayoutWidget_2);
        show_derivation_->setObjectName(QStringLiteral("show_derivation_"));

        gridLayout_2->addWidget(show_derivation_, 2, 1, 1, 1);

        t_slider_ = new QSlider(gridLayoutWidget_2);
        t_slider_->setObjectName(QStringLiteral("t_slider_"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(t_slider_->sizePolicy().hasHeightForWidth());
        t_slider_->setSizePolicy(sizePolicy4);
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        t_slider_->setFont(font2);
        t_slider_->setMaximum(100);
        t_slider_->setSingleStep(5);
        t_slider_->setTracking(true);
        t_slider_->setOrientation(Qt::Horizontal);
        t_slider_->setInvertedAppearance(false);
        t_slider_->setInvertedControls(false);
        t_slider_->setTickPosition(QSlider::NoTicks);
        t_slider_->setTickInterval(1);

        gridLayout_2->addWidget(t_slider_, 0, 1, 1, 1);

        show_sublines_ = new QCheckBox(gridLayoutWidget_2);
        show_sublines_->setObjectName(QStringLiteral("show_sublines_"));
        show_sublines_->setTristate(false);

        gridLayout_2->addWidget(show_sublines_, 2, 0, 1, 1);

        t_slider_1 = new QSlider(gridLayoutWidget_2);
        t_slider_1->setObjectName(QStringLiteral("t_slider_1"));
        sizePolicy4.setHeightForWidth(t_slider_1->sizePolicy().hasHeightForWidth());
        t_slider_1->setSizePolicy(sizePolicy4);
        t_slider_1->setFont(font2);
        t_slider_1->setMaximum(100);
        t_slider_1->setSingleStep(5);
        t_slider_1->setTracking(true);
        t_slider_1->setOrientation(Qt::Horizontal);
        t_slider_1->setInvertedAppearance(false);
        t_slider_1->setInvertedControls(false);
        t_slider_1->setTickPosition(QSlider::NoTicks);
        t_slider_1->setTickInterval(1);

        gridLayout_2->addWidget(t_slider_1, 1, 1, 1, 1);

        t_label_ = new QLabel(gridLayoutWidget_2);
        t_label_->setObjectName(QStringLiteral("t_label_"));
        t_label_->setMinimumSize(QSize(75, 0));
        t_label_->setMaximumSize(QSize(150, 16777215));
        t_label_->setBaseSize(QSize(0, 0));
        t_label_->setFont(font1);
        t_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        t_label_->setWordWrap(false);
        t_label_->setMargin(0);
        t_label_->setIndent(-1);

        gridLayout_2->addWidget(t_label_, 0, 0, 1, 1);

        raise_elevation_ = new QPushButton(gridLayoutWidget_2);
        raise_elevation_->setObjectName(QStringLiteral("raise_elevation_"));

        gridLayout_2->addWidget(raise_elevation_, 3, 0, 1, 1);

        dockWidget_2->setWidget(dockWidgetContents_2);
        BezierClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget_2);

        retranslateUi(BezierClass);

        QMetaObject::connectSlotsByName(BezierClass);
    } // setupUi

    void retranslateUi(QMainWindow *BezierClass)
    {
        BezierClass->setWindowTitle(QApplication::translate("BezierClass", "Bezier", 0));
        x_label_->setText(QApplication::translate("BezierClass", "X-Koordinate:", 0));
        y_label_->setText(QApplication::translate("BezierClass", "Y-Koordinate:", 0));
        weigh_label_->setText(QApplication::translate("BezierClass", "Gewichtung:", 0));
        add_button_->setText(QApplication::translate("BezierClass", "Hinzuf\303\274gen", 0));
        dockWidget->setWindowTitle(QApplication::translate("BezierClass", "Vertexdaten", 0));
        label_2->setText(QApplication::translate("BezierClass", "X-Koordinate", 0));
        label_->setText(QApplication::translate("BezierClass", "Z-Koordinate", 0));
        label_1->setText(QApplication::translate("BezierClass", "Y-Koordinate", 0));
        label_3->setText(QApplication::translate("BezierClass", "Gewichtung", 0));
        pushButton->setText(QApplication::translate("BezierClass", "PushButton", 0));
        pushButton_2->setText(QApplication::translate("BezierClass", "PushButton", 0));
        t_label_1->setText(QApplication::translate("BezierClass", "s: 0.00", 0));
        show_derivation_->setText(QApplication::translate("BezierClass", "Ableitung \n"
"anzeigen", 0));
        show_sublines_->setText(QApplication::translate("BezierClass", "deCasteljau \n"
"anzeigen", 0));
        t_label_->setText(QApplication::translate("BezierClass", "t: 0.00", 0));
        raise_elevation_->setText(QApplication::translate("BezierClass", "Gradanhebung", 0));
    } // retranslateUi

};

namespace Ui {
    class BezierClass: public Ui_BezierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIER_H
