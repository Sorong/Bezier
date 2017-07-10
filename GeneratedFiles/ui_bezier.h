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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
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
    QLabel *z_label_;
    QSpacerItem *y_spacer_;
    QDoubleSpinBox *z_coordinate_;
    QDoubleSpinBox *weight_;
    QLabel *y_label_;
    QSpacerItem *x_spacer_;
    QLabel *weight_label_;
    QDoubleSpinBox *y_coordinate_;
    QSpacerItem *weight_spacer_;
    QDoubleSpinBox *x_coordinate_;
    QSpacerItem *z_spacer_;
    QLabel *x_label_;
    DockWidget *dock_surface_data_;
    QWidget *surface_data_content_;
    QWidget *gridLayoutWidget_2;
    QGridLayout *surface_data_layout_;
    QSlider *u_slider_;
    QCheckBox *show_sublines_;
    QSlider *v_slider_;
    QLabel *v_label_;
    QLabel *u_label_;
    QPushButton *raise_elevation_;
    QCheckBox *show_derivation_;
    QPushButton *raise_elevation_u_;
    QPushButton *raise_elevation_v_;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *tool_buttons_2;
    QToolButton *edit_model_;
    QToolButton *draw_curve_;
    QToolButton *draw_surface_;
    QToolButton *draw_coons_;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox;

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
        show_surface_data_->setChecked(false);
        show_surface_data_->setEnabled(false);
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
        menu_bar_->setGeometry(QRect(0, 0, 1440, 21));
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
        vertex_data_layout_->setContentsMargins(5, 0, 50, 0);
        z_label_ = new QLabel(layoutWidget);
        z_label_->setObjectName(QStringLiteral("z_label_"));
        sizePolicy1.setHeightForWidth(z_label_->sizePolicy().hasHeightForWidth());
        z_label_->setSizePolicy(sizePolicy1);
        z_label_->setMinimumSize(QSize(75, 0));
        z_label_->setMaximumSize(QSize(16777215, 16777215));
        z_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        vertex_data_layout_->addWidget(z_label_, 5, 0, 1, 1);

        y_spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertex_data_layout_->addItem(y_spacer_, 2, 1, 1, 1);

        z_coordinate_ = new QDoubleSpinBox(layoutWidget);
        z_coordinate_->setObjectName(QStringLiteral("z_coordinate_"));
        z_coordinate_->setMinimum(-1024);
        z_coordinate_->setMaximum(1024);

        vertex_data_layout_->addWidget(z_coordinate_, 5, 1, 1, 1);

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

        x_spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertex_data_layout_->addItem(x_spacer_, 0, 1, 1, 1);

        weight_label_ = new QLabel(layoutWidget);
        weight_label_->setObjectName(QStringLiteral("weight_label_"));
        sizePolicy1.setHeightForWidth(weight_label_->sizePolicy().hasHeightForWidth());
        weight_label_->setSizePolicy(sizePolicy1);
        weight_label_->setMinimumSize(QSize(75, 0));
        weight_label_->setMaximumSize(QSize(16777215, 16777215));
        weight_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        vertex_data_layout_->addWidget(weight_label_, 7, 0, 1, 1);

        y_coordinate_ = new QDoubleSpinBox(layoutWidget);
        y_coordinate_->setObjectName(QStringLiteral("y_coordinate_"));
        y_coordinate_->setMinimum(-1024);
        y_coordinate_->setMaximum(1024);

        vertex_data_layout_->addWidget(y_coordinate_, 3, 1, 1, 1);

        weight_spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertex_data_layout_->addItem(weight_spacer_, 6, 1, 1, 1);

        x_coordinate_ = new QDoubleSpinBox(layoutWidget);
        x_coordinate_->setObjectName(QStringLiteral("x_coordinate_"));
        x_coordinate_->setMaximumSize(QSize(80, 16777215));
        x_coordinate_->setMinimum(-1024);
        x_coordinate_->setMaximum(1024);

        vertex_data_layout_->addWidget(x_coordinate_, 1, 1, 1, 1);

        z_spacer_ = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertex_data_layout_->addItem(z_spacer_, 4, 1, 1, 1);

        x_label_ = new QLabel(layoutWidget);
        x_label_->setObjectName(QStringLiteral("x_label_"));
        sizePolicy1.setHeightForWidth(x_label_->sizePolicy().hasHeightForWidth());
        x_label_->setSizePolicy(sizePolicy1);
        x_label_->setMinimumSize(QSize(0, 0));
        x_label_->setMaximumSize(QSize(80, 16777215));
        x_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        vertex_data_layout_->addWidget(x_label_, 1, 0, 1, 1);

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
        u_slider_ = new QSlider(gridLayoutWidget_2);
        u_slider_->setObjectName(QStringLiteral("u_slider_"));
        u_slider_->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(u_slider_->sizePolicy().hasHeightForWidth());
        u_slider_->setSizePolicy(sizePolicy2);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        u_slider_->setFont(font);
        u_slider_->setMaximum(100);
        u_slider_->setSingleStep(5);
        u_slider_->setTracking(true);
        u_slider_->setOrientation(Qt::Horizontal);
        u_slider_->setInvertedAppearance(false);
        u_slider_->setInvertedControls(false);
        u_slider_->setTickPosition(QSlider::NoTicks);
        u_slider_->setTickInterval(1);

        surface_data_layout_->addWidget(u_slider_, 2, 1, 1, 1);

        show_sublines_ = new QCheckBox(gridLayoutWidget_2);
        show_sublines_->setObjectName(QStringLiteral("show_sublines_"));
        show_sublines_->setTristate(false);

        surface_data_layout_->addWidget(show_sublines_, 0, 1, 1, 1);

        v_slider_ = new QSlider(gridLayoutWidget_2);
        v_slider_->setObjectName(QStringLiteral("v_slider_"));
        v_slider_->setEnabled(false);
        sizePolicy2.setHeightForWidth(v_slider_->sizePolicy().hasHeightForWidth());
        v_slider_->setSizePolicy(sizePolicy2);
        v_slider_->setFont(font);
        v_slider_->setMaximum(100);
        v_slider_->setSingleStep(5);
        v_slider_->setTracking(true);
        v_slider_->setOrientation(Qt::Horizontal);
        v_slider_->setInvertedAppearance(false);
        v_slider_->setInvertedControls(false);
        v_slider_->setTickPosition(QSlider::NoTicks);
        v_slider_->setTickInterval(1);

        surface_data_layout_->addWidget(v_slider_, 3, 1, 1, 1);

        v_label_ = new QLabel(gridLayoutWidget_2);
        v_label_->setObjectName(QStringLiteral("v_label_"));
        v_label_->setEnabled(false);
        v_label_->setMinimumSize(QSize(75, 0));
        v_label_->setMaximumSize(QSize(150, 16777215));
        v_label_->setBaseSize(QSize(0, 0));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(false);
        font1.setWeight(50);
        v_label_->setFont(font1);
        v_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        v_label_->setWordWrap(false);
        v_label_->setMargin(0);
        v_label_->setIndent(-1);

        surface_data_layout_->addWidget(v_label_, 3, 0, 1, 1);

        u_label_ = new QLabel(gridLayoutWidget_2);
        u_label_->setObjectName(QStringLiteral("u_label_"));
        u_label_->setEnabled(false);
        u_label_->setMinimumSize(QSize(75, 0));
        u_label_->setMaximumSize(QSize(150, 16777215));
        u_label_->setBaseSize(QSize(0, 0));
        u_label_->setFont(font1);
        u_label_->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        u_label_->setWordWrap(false);
        u_label_->setMargin(0);
        u_label_->setIndent(-1);

        surface_data_layout_->addWidget(u_label_, 2, 0, 1, 1);

        raise_elevation_ = new QPushButton(gridLayoutWidget_2);
        raise_elevation_->setObjectName(QStringLiteral("raise_elevation_"));

        surface_data_layout_->addWidget(raise_elevation_, 5, 1, 1, 1);

        show_derivation_ = new QCheckBox(gridLayoutWidget_2);
        show_derivation_->setObjectName(QStringLiteral("show_derivation_"));

        surface_data_layout_->addWidget(show_derivation_, 1, 1, 1, 1);

        raise_elevation_u_ = new QPushButton(gridLayoutWidget_2);
        raise_elevation_u_->setObjectName(QStringLiteral("raise_elevation_u_"));

        surface_data_layout_->addWidget(raise_elevation_u_, 6, 1, 1, 1);

        raise_elevation_v_ = new QPushButton(gridLayoutWidget_2);
        raise_elevation_v_->setObjectName(QStringLiteral("raise_elevation_v_"));

        surface_data_layout_->addWidget(raise_elevation_v_, 7, 1, 1, 1);

        dock_surface_data_->setWidget(surface_data_content_);
        BezierClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dock_surface_data_);
        dockWidget = new QDockWidget(BezierClass);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setMinimumSize(QSize(150, 100));
        dockWidget->setFeatures(QDockWidget::DockWidgetMovable);
        dockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayoutWidget = new QWidget(dockWidgetContents);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 250, 89));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 5);
        tool_buttons_2 = new QHBoxLayout();
        tool_buttons_2->setSpacing(6);
        tool_buttons_2->setObjectName(QStringLiteral("tool_buttons_2"));
        edit_model_ = new QToolButton(verticalLayoutWidget);
        edit_model_->setObjectName(QStringLiteral("edit_model_"));
        edit_model_->setMinimumSize(QSize(32, 32));
        edit_model_->setToolTipDuration(-1);
        QIcon icon;
        icon.addFile(QStringLiteral("res/hand-point-090.png"), QSize(), QIcon::Normal, QIcon::Off);
        edit_model_->setIcon(icon);
        edit_model_->setIconSize(QSize(32, 32));

        tool_buttons_2->addWidget(edit_model_);

        draw_curve_ = new QToolButton(verticalLayoutWidget);
        draw_curve_->setObjectName(QStringLiteral("draw_curve_"));
        draw_curve_->setMinimumSize(QSize(32, 32));
        draw_curve_->setToolTipDuration(-1);
        QIcon icon1;
        icon1.addFile(QStringLiteral("res/layer-shape-curve.png"), QSize(), QIcon::Normal, QIcon::Off);
        draw_curve_->setIcon(icon1);
        draw_curve_->setIconSize(QSize(32, 32));
        draw_curve_->setAutoRaise(false);

        tool_buttons_2->addWidget(draw_curve_);

        draw_surface_ = new QToolButton(verticalLayoutWidget);
        draw_surface_->setObjectName(QStringLiteral("draw_surface_"));
        draw_surface_->setMinimumSize(QSize(32, 32));
        QIcon icon2;
        icon2.addFile(QStringLiteral("res/layer-shape.png"), QSize(), QIcon::Normal, QIcon::Off);
        draw_surface_->setIcon(icon2);
        draw_surface_->setIconSize(QSize(32, 32));

        tool_buttons_2->addWidget(draw_surface_);

        draw_coons_ = new QToolButton(verticalLayoutWidget);
        draw_coons_->setObjectName(QStringLiteral("draw_coons_"));
        draw_coons_->setEnabled(false);
        draw_coons_->setMinimumSize(QSize(32, 32));
        QIcon icon3;
        icon3.addFile(QStringLiteral("res/layer-shape-polygon.png"), QSize(), QIcon::Normal, QIcon::Off);
        draw_coons_->setIcon(icon3);
        draw_coons_->setIconSize(QSize(32, 32));

        tool_buttons_2->addWidget(draw_coons_);


        verticalLayout_2->addLayout(tool_buttons_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, 15, -1);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);
        label->setMargin(5);

        horizontalLayout->addWidget(label);

        doubleSpinBox = new QDoubleSpinBox(verticalLayoutWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        doubleSpinBox->setBaseSize(QSize(0, 0));
        doubleSpinBox->setMinimum(-10);

        horizontalLayout->addWidget(doubleSpinBox);


        verticalLayout_2->addLayout(horizontalLayout);

        dockWidget->setWidget(dockWidgetContents);
        BezierClass->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockWidget);

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
        z_label_->setText(QApplication::translate("BezierClass", "Z-Koordinate", 0));
        y_label_->setText(QApplication::translate("BezierClass", "Y-Koordinate", 0));
        weight_label_->setText(QApplication::translate("BezierClass", "Gewichtung", 0));
        x_label_->setText(QApplication::translate("BezierClass", "X-Koordinate", 0));
        dock_surface_data_->setWindowTitle(QApplication::translate("BezierClass", "Fl\303\244chendaten", 0));
        show_sublines_->setText(QApplication::translate("BezierClass", "deCasteljau \n"
"anzeigen", 0));
        v_label_->setText(QApplication::translate("BezierClass", "v: 0.00", 0));
        u_label_->setText(QApplication::translate("BezierClass", "u: 0.00", 0));
        raise_elevation_->setText(QApplication::translate("BezierClass", "Gradanhebung U/V", 0));
        show_derivation_->setText(QApplication::translate("BezierClass", "Ableitung \n"
"anzeigen", 0));
        raise_elevation_u_->setText(QApplication::translate("BezierClass", "Gradanhebung U", 0));
        raise_elevation_v_->setText(QApplication::translate("BezierClass", "Gradanhebung V", 0));
        dockWidget->setWindowTitle(QApplication::translate("BezierClass", "Werkzeuge", 0));
#ifndef QT_NO_TOOLTIP
        edit_model_->setToolTip(QApplication::translate("BezierClass", "Bearbeitungsmodus", 0));
#endif // QT_NO_TOOLTIP
        edit_model_->setText(QApplication::translate("BezierClass", "...", 0));
#ifndef QT_NO_TOOLTIP
        draw_curve_->setToolTip(QApplication::translate("BezierClass", "Zeichnet Bezierkurve", 0));
#endif // QT_NO_TOOLTIP
        draw_curve_->setText(QApplication::translate("BezierClass", "...", 0));
#ifndef QT_NO_TOOLTIP
        draw_surface_->setToolTip(QApplication::translate("BezierClass", "Zeichnet Bezierfl\303\244che", 0));
#endif // QT_NO_TOOLTIP
        draw_surface_->setText(QApplication::translate("BezierClass", "...", 0));
#ifndef QT_NO_TOOLTIP
        draw_coons_->setToolTip(QApplication::translate("BezierClass", "Zeichnet Coonspatch", 0));
#endif // QT_NO_TOOLTIP
        draw_coons_->setText(QApplication::translate("BezierClass", "...", 0));
        label->setText(QApplication::translate("BezierClass", "Z-Achse:", 0));
#ifndef QT_NO_TOOLTIP
        doubleSpinBox->setToolTip(QApplication::translate("BezierClass", "Z-Achse wird \"festgesetzt\" anhand des eigegebenen Wertes.", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class BezierClass: public Ui_BezierClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIER_H
