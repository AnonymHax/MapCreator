/********************************************************************************
** Form generated from reading UI file 'TileEditor.ui'
**
** Created: Sat 25. May 23:25:54 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TILEEDITOR_H
#define UI_TILEEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TileEditor
{
public:
    QAction *newTile;
    QAction *newAnimation;
    QAction *modifiyTile;
    QWidget *centralwidget;
    QGroupBox *frame_box;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label_axey;
    QSpinBox *tile_secondFloor;
    QLabel *label_axex;
    QSpinBox *tile_secondSide;
    QLabel *label_scaley;
    QDoubleSpinBox *tile_scalex;
    QLabel *label_scalex;
    QDoubleSpinBox *tile_scaley;
    QLabel *label;
    QSpinBox *frame_interval;
    QLabel *label_2;
    QWidget *widget_2;
    QSpinBox *frame_restart;
    QCheckBox *check_restart;
    QLCDNumber *frame_number;
    QWidget *widget;
    QPushButton *frame_previous;
    QPushButton *frame_next;
    QPushButton *tile_add;
    QFrame *frame;
    QGroupBox *tile_infos;
    QLabel *label_name;
    QLineEdit *tile_name;
    QPushButton *tile_play;
    QTreeView *animation_manager;
    QGroupBox *cube_box;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *cube_inverse;
    QCheckBox *cube_show;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *TileEditor)
    {
        if (TileEditor->objectName().isEmpty())
            TileEditor->setObjectName(QString::fromUtf8("TileEditor"));
        TileEditor->resize(1087, 732);
        TileEditor->setMinimumSize(QSize(0, 0));
        TileEditor->setMaximumSize(QSize(1087, 793));
        newTile = new QAction(TileEditor);
        newTile->setObjectName(QString::fromUtf8("newTile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icon_new_tile.png"), QSize(), QIcon::Normal, QIcon::Off);
        newTile->setIcon(icon);
        newAnimation = new QAction(TileEditor);
        newAnimation->setObjectName(QString::fromUtf8("newAnimation"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icon_animation.png"), QSize(), QIcon::Normal, QIcon::Off);
        newAnimation->setIcon(icon1);
        modifiyTile = new QAction(TileEditor);
        modifiyTile->setObjectName(QString::fromUtf8("modifiyTile"));
        centralwidget = new QWidget(TileEditor);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        frame_box = new QGroupBox(centralwidget);
        frame_box->setObjectName(QString::fromUtf8("frame_box"));
        frame_box->setEnabled(false);
        frame_box->setGeometry(QRect(10, 170, 205, 311));
        frame_box->setMinimumSize(QSize(205, 1));
        frame_box->setMaximumSize(QSize(205, 461));
        verticalLayoutWidget = new QWidget(frame_box);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 10, 202, 301));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_axey = new QLabel(verticalLayoutWidget);
        label_axey->setObjectName(QString::fromUtf8("label_axey"));

        gridLayout->addWidget(label_axey, 0, 0, 1, 1);

        tile_secondFloor = new QSpinBox(verticalLayoutWidget);
        tile_secondFloor->setObjectName(QString::fromUtf8("tile_secondFloor"));
        tile_secondFloor->setMinimum(-10000);
        tile_secondFloor->setMaximum(10000);

        gridLayout->addWidget(tile_secondFloor, 0, 1, 1, 1);

        label_axex = new QLabel(verticalLayoutWidget);
        label_axex->setObjectName(QString::fromUtf8("label_axex"));

        gridLayout->addWidget(label_axex, 1, 0, 1, 1);

        tile_secondSide = new QSpinBox(verticalLayoutWidget);
        tile_secondSide->setObjectName(QString::fromUtf8("tile_secondSide"));
        tile_secondSide->setMinimum(-10000);
        tile_secondSide->setMaximum(10000);

        gridLayout->addWidget(tile_secondSide, 1, 1, 1, 1);

        label_scaley = new QLabel(verticalLayoutWidget);
        label_scaley->setObjectName(QString::fromUtf8("label_scaley"));

        gridLayout->addWidget(label_scaley, 2, 0, 1, 1);

        tile_scalex = new QDoubleSpinBox(verticalLayoutWidget);
        tile_scalex->setObjectName(QString::fromUtf8("tile_scalex"));
        tile_scalex->setMinimum(0.5);
        tile_scalex->setMaximum(1.5);
        tile_scalex->setSingleStep(0.1);
        tile_scalex->setValue(1);

        gridLayout->addWidget(tile_scalex, 2, 1, 1, 1);

        label_scalex = new QLabel(verticalLayoutWidget);
        label_scalex->setObjectName(QString::fromUtf8("label_scalex"));

        gridLayout->addWidget(label_scalex, 3, 0, 1, 1);

        tile_scaley = new QDoubleSpinBox(verticalLayoutWidget);
        tile_scaley->setObjectName(QString::fromUtf8("tile_scaley"));
        tile_scaley->setMinimum(0.5);
        tile_scaley->setMaximum(1.5);
        tile_scaley->setSingleStep(0.1);
        tile_scaley->setValue(1);

        gridLayout->addWidget(tile_scaley, 3, 1, 1, 1);

        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 4, 0, 1, 1);

        frame_interval = new QSpinBox(verticalLayoutWidget);
        frame_interval->setObjectName(QString::fromUtf8("frame_interval"));
        frame_interval->setMinimum(1);
        frame_interval->setMaximum(999999999);
        frame_interval->setValue(10);

        gridLayout->addWidget(frame_interval, 4, 1, 1, 1);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        widget_2 = new QWidget(verticalLayoutWidget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(95, 21));
        widget_2->setMaximumSize(QSize(95, 21));
        frame_restart = new QSpinBox(widget_2);
        frame_restart->setObjectName(QString::fromUtf8("frame_restart"));
        frame_restart->setGeometry(QRect(0, 0, 75, 20));
        frame_restart->setMaximum(999999999);
        check_restart = new QCheckBox(widget_2);
        check_restart->setObjectName(QString::fromUtf8("check_restart"));
        check_restart->setGeometry(QRect(81, 4, 13, 13));
        check_restart->setChecked(true);

        gridLayout->addWidget(widget_2, 5, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        frame_number = new QLCDNumber(verticalLayoutWidget);
        frame_number->setObjectName(QString::fromUtf8("frame_number"));
        frame_number->setMaximumSize(QSize(200, 50));
        frame_number->setFrameShape(QFrame::Box);
        frame_number->setFrameShadow(QFrame::Plain);
        frame_number->setSmallDecimalPoint(false);
        frame_number->setMode(QLCDNumber::Dec);
        frame_number->setProperty("value", QVariant(1));

        verticalLayout->addWidget(frame_number);

        widget = new QWidget(verticalLayoutWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(200, 51));
        widget->setMaximumSize(QSize(200, 51));
        frame_previous = new QPushButton(widget);
        frame_previous->setObjectName(QString::fromUtf8("frame_previous"));
        frame_previous->setGeometry(QRect(0, 0, 101, 50));
        frame_previous->setMinimumSize(QSize(0, 50));
        frame_next = new QPushButton(widget);
        frame_next->setObjectName(QString::fromUtf8("frame_next"));
        frame_next->setGeometry(QRect(100, 0, 101, 50));
        frame_next->setMinimumSize(QSize(0, 50));

        verticalLayout->addWidget(widget);

        tile_add = new QPushButton(centralwidget);
        tile_add->setObjectName(QString::fromUtf8("tile_add"));
        tile_add->setEnabled(false);
        tile_add->setGeometry(QRect(20, 564, 191, 71));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(240, 170, 821, 481));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        tile_infos = new QGroupBox(centralwidget);
        tile_infos->setObjectName(QString::fromUtf8("tile_infos"));
        tile_infos->setEnabled(false);
        tile_infos->setGeometry(QRect(10, 10, 101, 141));
        label_name = new QLabel(tile_infos);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(20, 15, 46, 13));
        tile_name = new QLineEdit(tile_infos);
        tile_name->setObjectName(QString::fromUtf8("tile_name"));
        tile_name->setGeometry(QRect(5, 35, 90, 30));
        tile_play = new QPushButton(centralwidget);
        tile_play->setObjectName(QString::fromUtf8("tile_play"));
        tile_play->setEnabled(false);
        tile_play->setGeometry(QRect(20, 500, 191, 61));
        animation_manager = new QTreeView(centralwidget);
        animation_manager->setObjectName(QString::fromUtf8("animation_manager"));
        animation_manager->setGeometry(QRect(240, 10, 821, 151));
        cube_box = new QGroupBox(centralwidget);
        cube_box->setObjectName(QString::fromUtf8("cube_box"));
        cube_box->setGeometry(QRect(120, 20, 111, 71));
        verticalLayoutWidget_2 = new QWidget(cube_box);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(0, 10, 111, 51));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        cube_inverse = new QCheckBox(verticalLayoutWidget_2);
        cube_inverse->setObjectName(QString::fromUtf8("cube_inverse"));
        cube_inverse->setChecked(true);

        verticalLayout_2->addWidget(cube_inverse);

        cube_show = new QCheckBox(verticalLayoutWidget_2);
        cube_show->setObjectName(QString::fromUtf8("cube_show"));

        verticalLayout_2->addWidget(cube_show);

        TileEditor->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TileEditor);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1087, 21));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        TileEditor->setMenuBar(menubar);
        statusbar = new QStatusBar(TileEditor);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TileEditor->setStatusBar(statusbar);
        toolBar = new QToolBar(TileEditor);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        TileEditor->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFichier->menuAction());
        menuFichier->addAction(newTile);
        menuFichier->addAction(modifiyTile);
        menuFichier->addAction(newAnimation);
        toolBar->addAction(newTile);
        toolBar->addAction(newAnimation);

        retranslateUi(TileEditor);

        QMetaObject::connectSlotsByName(TileEditor);
    } // setupUi

    void retranslateUi(QMainWindow *TileEditor)
    {
        TileEditor->setWindowTitle(QApplication::translate("TileEditor", "Editeur de Tiles", 0, QApplication::UnicodeUTF8));
        newTile->setText(QApplication::translate("TileEditor", "Nouveau Tile", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        newTile->setToolTip(QApplication::translate("TileEditor", "Creer un nouveau Tile", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        newTile->setShortcut(QApplication::translate("TileEditor", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        newAnimation->setText(QApplication::translate("TileEditor", "Nouvelle Animation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        newAnimation->setToolTip(QApplication::translate("TileEditor", "Ajouter une Animation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        newAnimation->setShortcut(QApplication::translate("TileEditor", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        modifiyTile->setText(QApplication::translate("TileEditor", "Modifier Tile", 0, QApplication::UnicodeUTF8));
        modifiyTile->setShortcut(QApplication::translate("TileEditor", "Ctrl+M", 0, QApplication::UnicodeUTF8));
        frame_box->setTitle(QApplication::translate("TileEditor", "Frame", 0, QApplication::UnicodeUTF8));
        label_axey->setText(QApplication::translate("TileEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Axe Horizontal</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_axex->setText(QApplication::translate("TileEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Axe Vertical</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_scaley->setText(QApplication::translate("TileEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Dimension</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Horizontal</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_scalex->setText(QApplication::translate("TileEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Dimension</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Vertical</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TileEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Interval</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\"> Frames (ms)</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("TileEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Interval</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Redemarrage (ms)</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        check_restart->setText(QString());
        frame_previous->setText(QApplication::translate("TileEditor", "<", 0, QApplication::UnicodeUTF8));
        frame_next->setText(QApplication::translate("TileEditor", ">", 0, QApplication::UnicodeUTF8));
        tile_add->setText(QApplication::translate("TileEditor", "Ajouter", 0, QApplication::UnicodeUTF8));
        tile_infos->setTitle(QApplication::translate("TileEditor", "Tile", 0, QApplication::UnicodeUTF8));
        label_name->setText(QApplication::translate("TileEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Nom</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        tile_name->setText(QString());
        tile_play->setText(QApplication::translate("TileEditor", "Rendu", 0, QApplication::UnicodeUTF8));
        cube_box->setTitle(QApplication::translate("TileEditor", "Cube", 0, QApplication::UnicodeUTF8));
        cube_inverse->setText(QApplication::translate("TileEditor", "Inverser Cadreur", 0, QApplication::UnicodeUTF8));
        cube_show->setText(QApplication::translate("TileEditor", "Afficher", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("TileEditor", "Fichier", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("TileEditor", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TileEditor: public Ui_TileEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TILEEDITOR_H
