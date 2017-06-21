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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <dockwidget.hpp>
#include "glview.hpp"

QT_BEGIN_NAMESPACE

class Ui_BezierClass
{
public:
    QAction *show_vertex_data_;
    QAction *show_surface_data_;
    QWidget *central_layout_;
    QVBoxLayout *verticalLayout;
    GLView *glview_;
    QStatusBar *status_bar_;
    QMenuBar *menu_bar_;
    QMenu *menu_view_;
    DockWidget *dock_vertex_data_;
    QWidget *dock_vertex_data_content_;
    QWidget *layoutWidget;
    QGridLayout *vertex_data_layout_;
    QLabel *x_label_;
    QSpacerItem *z_spacer_;
    QSpacerItem *weight_spacer_;
    QSpacerItem *y_spacer_;
    QDoubleSpinBox *weight_;
    QLabel *y_label_;
    QLabel *z_label_;
    QDoubleSpinBox *z_coordinate_;
    QSpacerItem *x_spacer_;
    QDoubleSpinBox *y_coordinate_;
    QDoubleSpinBox *x_coordinate_;
    QLabel *weight_label_;
    DockWidget *dock_surface_data_;
    QWidget *surface_data_content_;
    QWidget *gridLayoutWidget_2;
    QGridLayout *surface_data_layout_;
    QSlider *t_slider_;
    QCheckBox *show_sublines_;
    QSlider *s_slider_;
    QLabel *s_label_;
    QLabel *t_label_;
    QPushButton *raise_elevation_;
    QCheckBox *show_derivation_;
    QPushButton *raise_elevation_t_;
    QPushButton *raise_elevation_s_;

    void setupUi(QMainWindow *BezierClass)
    {
        if (BezierClass->objectName().isEmpty())
            BezierClass->setObjectName(QStringLiteral("BezierClass"));
        BezierClass->resize(1440, 900);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BezierClass->sizePolicy().hasHeightForWidth());
        BezierClass->setSizePolicy(sizePolicy);
        BezierClass->setDocumentMode(false);
        BezierClass->setTabShape(QTabWidget::Rounded);
        BezierClass->setDockNestingEnabled(false);
        show_vertex_data_ = new QAction(BezierClass);
        show_vertex_data_->setObjectName(QStringLiteral("show_vertex_data_"));
        show_vertex_data_->setCheckable(true);
        show_vertex_data_->setChecked(false);
        show_vertex_data_->setEnabled(false);
        show_surface_data_ = new QAction(BezierClass);
        show_surface_data_->setObjectName(QStringLiteral("show_surface_data_"));
        show_surface_data_->setCheckable(true);
        show_surface_data_->setChecked(true);
        central_layout_ = new QWidget(BezierClass);
        central_layout_->setObjectName(QStringLiteral("central_layout_"));
        central_layout_->setMouseTracking(false);
        verticalLayout = new QVBoxLayout(central_layout_);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        glview_ = new GLView(central_layout_);
        glview_->setObjectName(QStringLiteral("glview_"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(glview_->sizePolicy().hasHeightForWidth());
        glview_->setSizePolicy(sizePolicy1);
        glview_->setFocusPolicy(Qt::StrongFocus);

        verticalLayout->addWidget(glview_);

        BezierClass->setCentralWidget(central_layout_);
        status_bar_ = new QStatusBar(BezierClass);
        status_bar_->setObjectName(QStringLiteral("status_bar_"));
        BezierClass->setStatusBar(status_bar_);
        menu_bar_ = new QMenuBar(BezierClass);
        menu_bar_->setObjectName(QStringLiteral("menu_bar_"));
        menu_bar_->setGeometry(QRect(0, 0, 1440, 26));
        menu_view_ = new QMenu(menu_bar_);
        menu_view_->setObjectName(QStringLiteral("menu_view_"));
        BezierClass->setMenuBar(menu_bar_);
        dock_vertex_data_ = new DockWidget(BezierClass);
        dock_vertex_data_->setObjectName(QStringLiteral("dock_vertex_data_"));
        dock_vertex_data_->setEnabled(true);
        dock_vertex_data_->setMinimumSize(QSize(270, 91));
        dock_vertex_data_->setMaximumSize(QSize(524287, 524287));
        dock_vertex_data_->setFeatures(QDockWidget::DockWidgetFeatureMask);
        dock_vertex_data_->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        dock_vertex_data_content_ = new QWidget();
        dock_vertex_data_content_->setObjectName(QStringLiteral("dock_vertex_data_content_"));
        layoutWidget = new QWidget(dock_vertex_data_content_);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 269, 284));
        vertex_data_layout_ = new QGridLayout(layoutWidget);
        vertex_data_layout_->setSpacing(6);
        vertex_data_layout_->setContentsMargins(11, 11, 11, 11);
        vertex_data_layout_->setObjectName(QStringLiteral("vertex_data_layout_"));
        vertex_data_layout_->setContentsMargins(5, 0, 5, 0);
        x_label_ = new QLabel(layoutWidget);
        x_label_->setObjectName(QStringLiteral("x_label_"));
        sizePolicy1.setHeightForWidth(x_label_->sizePolicy().hasHeightForWidth());
        x_label_->setSizePolicy(sizePolicy1);
        x_label_->setMinimumSize(QSize(0, 0));
        x_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        vertex_data_layout_->addWidget(x_label_, 1, 0, 1, 1);

        z_spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertex_data_layout_->addItem(z_spacer_, 4, 1, 1, 1);

        weight_spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertex_data_layout_->addItem(weight_spacer_, 6, 1, 1, 1);

        y_spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertex_data_layout_->addItem(y_spacer_, 2, 1, 1, 1);

        weight_ = new QDoubleSpinBox(layoutWidget);
        weight_->setObjectName(QStringLiteral("weight_"));
        weight_->setMinimum(0);
        weight_->setMaximum(1024);

        vertex_data_layout_->addWidget(weight_, 7, 1, 1, 1);

        y_label_ = new QLabel(layoutWidget);
        y_label_->setObjectName(QStringLiteral("y_label_"));
        sizePolicy1.setHeightForWidth(y_label_->sizePolicy().hasHeightForWidth());
        y_label_->setSizePolicy(sizePolicy1);
        y_label_->setMinimumSize(QSize(0, 0));
        y_label_->setMaximumSize(QSize(16777215, 16777215));
        y_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        vertex_data_layout_->addWidget(y_label_, 3, 0, 1, 1);

        z_label_ = new QLabel(layoutWidget);
        z_label_->setObjectName(QStringLiteral("z_label_"));
        sizePolicy1.setHeightForWidth(z_label_->sizePolicy().hasHeightForWidth());
        z_label_->setSizePolicy(sizePolicy1);
        z_label_->setMinimumSize(QSize(75, 0));
        z_label_->setMaximumSize(QSize(16777215, 16777215));
        z_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        vertex_data_layout_->addWidget(z_label_, 5, 0, 1, 1);

        z_coordinate_ = new QDoubleSpinBox(layoutWidget);
        z_coordinate_->setObjectName(QStringLiteral("z_coordinate_"));
        z_coordinate_->setMinimum(-1024);
        z_coordinate_->setMaximum(1024);

        vertex_data_layout_->addWidget(z_coordinate_, 5, 1, 1, 1);

        x_spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertex_data_layout_->addItem(x_spacer_, 0, 1, 1, 1);

        y_coordinate_ = new QDoubleSpinBox(layoutWidget);
        y_coordinate_->setObjectName(QStringLiteral("y_coordinate_"));
        y_coordinate_->setMinimum(-1024);
        y_coordinate_->setMaximum(1024);

        vertex_data_layout_->addWidget(y_coordinate_, 3, 1, 1, 1);

        x_coordinate_ = new QDoubleSpinBox(layoutWidget);
        x_coordinate_->setObjectName(QStringLiteral("x_coordinate_"));
        x_coordinate_->setMinimum(-1024);
        x_coordinate_->setMaximum(1024);

        vertex_data_layout_->addWidget(x_coordinate_, 1, 1, 1, 1);

        weight_label_ = new QLabel(layoutWidget);
        weight_label_->setObjectName(QStringLiteral("weight_label_"));
        sizePolicy1.setHeightForWidth(weight_label_->sizePolicy().hasHeightForWidth());
        weight_label_->setSizePolicy(sizePolicy1);
        weight_label_->setMinimumSize(QSize(75, 0));
        weight_label_->setMaximumSize(QSize(16777215, 16777215));
        weight_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        vertex_data_layout_->addWidget(weight_label_, 7, 0, 1, 1);

        dock_vertex_data_->setWidget(dock_vertex_data_content_);
        BezierClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dock_vertex_data_);
        dock_surface_data_ = new DockWidget(BezierClass);
        dock_surface_data_->setObjectName(QStringLiteral("dock_surface_data_"));
        dock_surface_data_->setMinimumSize(QSize(270, 91));
        dock_surface_data_->setFeatures(QDockWidget::DockWidgetFeatureMask);
        dock_surface_data_->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        surface_data_content_ = new QWidget();
        surface_data_content_->setObjectName(QStringLiteral("surface_data_content_"));
        gridLayoutWidget_2 = new QWidget(surface_data_content_);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(-10, 0, 279, 571));
        surface_data_layout_ = new QGridLayout(gridLayoutWidget_2);
        surface_data_layout_->setSpacing(6);
        surface_data_layout_->setContentsMargins(11, 11, 11, 11);
        surface_data_layout_->setObjectName(QStringLiteral("surface_data_layout_"));
        surface_data_layout_->setContentsMargins(20, 0, 20, 0);
        t_slider_ = new QSlider(gridLayoutWidget_2);
        t_slider_->setObjectName(QStringLiteral("t_slider_"));
        t_slider_->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(t_slider_->sizePolicy().hasHeightForWidth());
        t_slider_->setSizePolicy(sizePolicy2);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        t_slider_->setFont(font);
        t_slider_->setMaximum(100);
        t_slider_->setSingleStep(5);
        t_slider_->setTracking(true);
        t_slider_->setOrientation(Qt::Horizontal);
        t_slider_->setInvertedAppearance(false);
        t_slider_->setInvertedControls(false);
        t_slider_->setTickPosition(QSlider::NoTicks);
        t_slider_->setTickInterval(1);

        surface_data_layout_->addWidget(t_slider_, 2, 1, 1, 1);

        show_sublines_ = new QCheckBox(gridLayoutWidget_2);
        show_sublines_->setObjectName(QStringLiteral("show_sublines_"));
        show_sublines_->setTristate(false);

        surface_data_layout_->addWidget(show_sublines_, 0, 1, 1, 1);

        s_slider_ = new QSlider(gridLayoutWidget_2);
        s_slider_->setObjectName(QStringLiteral("s_slider_"));
        s_slider_->setEnabled(false);
        sizePolicy2.setHeightForWidth(s_slider_->sizePolicy().hasHeightForWidth());
        s_slider_->setSizePolicy(sizePolicy2);
        s_slider_->setFont(font);
        s_slider_->setMaximum(100);
        s_slider_->setSingleStep(5);
        s_slider_->setTracking(true);
        s_slider_->setOrientation(Qt::Horizontal);
        s_slider_->setInvertedAppearance(false);
        s_slider_->setInvertedControls(false);
        s_slider_->setTickPosition(QSlider::NoTicks);
        s_slider_->setTickInterval(1);

        surface_data_layout_->addWidget(s_slider_, 3, 1, 1, 1);

        s_label_ = new QLabel(gridLayoutWidget_2);
        s_label_->setObjectName(QStringLiteral("s_label_"));
        s_label_->setEnabled(false);
        s_label_->setMinimumSize(QSize(75, 0));
        s_label_->setMaximumSize(QSize(150, 16777215));
        s_label_->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setWeight(50);
        s_label_->setFont(font1);
        s_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        s_label_->setWordWrap(false);
        s_label_->setMargin(0);
        s_label_->setIndent(-1);

        surface_data_layout_->addWidget(s_label_, 3, 0, 1, 1);

        t_label_ = new QLabel(gridLayoutWidget_2);
        t_label_->setObjectName(QStringLiteral("t_label_"));
        t_label_->setEnabled(false);
        t_label_->setMinimumSize(QSize(75, 0));
        t_label_->setMaximumSize(QSize(150, 16777215));
        t_label_->setBaseSize(QSize(0, 0));
        t_label_->setFont(font1);
        t_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        t_label_->setWordWrap(false);
        t_label_->setMargin(0);
        t_label_->setIndent(-1);

        surface_data_layout_->addWidget(t_label_, 2, 0, 1, 1);

        raise_elevation_ = new QPushButton(gridLayoutWidget_2);
        raise_elevation_->setObjectName(QStringLiteral("raise_elevation_"));

        surface_data_layout_->addWidget(raise_elevation_, 5, 1, 1, 1);

        show_derivation_ = new QCheckBox(gridLayoutWidget_2);
        show_derivation_->setObjectName(QStringLiteral("show_derivation_"));

        surface_data_layout_->addWidget(show_derivation_, 1, 1, 1, 1);

        raise_elevation_t_ = new QPushButton(gridLayoutWidget_2);
        raise_elevation_t_->setObjectName(QStringLiteral("raise_elevation_t_"));

        surface_data_layout_->addWidget(raise_elevation_t_, 6, 1, 1, 1);

        raise_elevation_s_ = new QPushButton(gridLayoutWidget_2);
        raise_elevation_s_->setObjectName(QStringLiteral("raise_elevation_s_"));

        surface_data_layout_->addWidget(raise_elevation_s_, 7, 1, 1, 1);

        dock_surface_data_->setWidget(surface_data_content_);
        BezierClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dock_surface_data_);

        menu_bar_->addAction(menu_view_->menuAction());
        menu_view_->addAction(show_vertex_data_);
        menu_view_->addAction(show_surface_data_);

        retranslateUi(BezierClass);

        QMetaObject::connectSlotsByName(BezierClass);
    } // setupUi

    void retranslateUi(QMainWindow *BezierClass)
    {
        BezierClass->setWindowTitle(QApplication::translate("BezierClass", "Bezier", 0));
        show_vertex_data_->setText(QApplication::translate("BezierClass", "Vertexdaten", 0));
        show_surface_data_->setText(QApplication::translate("BezierClass", "Fl\303\244chendaten", 0));
        menu_view_->setTitle(QApplication::translate("BezierClass", "Ansicht", 0));
        dock_vertex_data_->setWindowTitle(QApplication::translate("BezierClass", "Vertexdaten", 0));
        x_label_->setText(QApplication::translate("BezierClass", "X-Koordinate", 0));
        y_label_->setText(QApplication::translate("BezierClass", "Y-Koordinate", 0));
        z_label_->setText(QApplication::translate("BezierClass", "Z-Koordinate", 0));
        weight_label_->setText(QApplication::translate("BezierClass", "Gewichtung", 0));
        dock_surface_data_->setWindowTitle(QApplication::translate("BezierClass", "Fl\303\244chendaten", 0));
        show_sublines_->setText(QApplication::translate("BezierClass", "deCasteljau \n"
"anzeigen", 0));
        s_label_->setText(QApplication::translate("BezierClass", "s: 0.00", 0));
        t_label_->setText(QApplication::translate("BezierClass", "t: 0.00", 0));
        raise_elevation_->setText(QApplication::translate("BezierClass", "Gradanhebung T/S", 0));
        show_derivation_->setText(QApplication::translate("BezierClass", "Ableitung \n"
"anzeigen", 0));
        raise_elevation_t_->setText(QApplication::translate("BezierClass", "Gradanhebung T", 0));
        raise_elevation_s_->setText(QApplication::translate("BezierClass", "Gradanhebung S", 0));
    } // retranslateUi

};

namespace Ui {
    class BezierClass: public Ui_BezierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIER_H
