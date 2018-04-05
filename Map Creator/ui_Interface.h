/********************************************************************************
** Form generated from reading UI file 'Interface.ui'
**
** Created: Sat 25. May 23:25:54 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QScrollBar>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Interface
{
public:
    QAction *createMap;
    QAction *loadMap;
    QAction *sendMap;
    QAction *saveMap;
    QAction *version;
    QAction *addTile;
    QAction *loadTiles;
    QAction *saveTiles;
    QAction *deleteTiles;
    QAction *save_asMap;
    QAction *save_asTiles;
    QAction *getBack;
    QAction *getForward;
    QAction *enableGrid;
    QAction *zoomIn;
    QAction *zoomOut;
    QAction *goto_cell;
    QWidget *Container;
    QFrame *frame;
    QScrollBar *VBar;
    QScrollBar *HBar;
    QTabWidget *tab_selector;
    QWidget *tab_light;
    QScrollArea *scroll_area_light;
    QWidget *scroll_light;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_3;
    QLabel *label_6;
    QSpinBox *light_radius;
    QLabel *label_7;
    QSpinBox *light_intensity;
    QLabel *label_8;
    QSpinBox *light_quality;
    QLabel *label_10;
    QDoubleSpinBox *light_opening_angle;
    QLabel *label_11;
    QDoubleSpinBox *light_angle;
    QLabel *label_12;
    QPushButton *light_color;
    QWidget *widget;
    QTreeView *layer_manager;
    QWidget *widget_2;
    QPushButton *layer_delete;
    QPushButton *layer_add;
    QPushButton *layer_down;
    QPushButton *layer_up;
    QTreeView *tile_list;
    QListView *tile_view;
    QGroupBox *tool_box;
    QToolButton *tool_place;
    QToolButton *tool_collision;
    QToolButton *tool_light;
    QToolButton *tool_delete;
    QToolButton *tool_height;
    QToolButton *tool_move;
    QMenuBar *menubar;
    QMenu *menuCarte;
    QMenu *infos;
    QMenu *menuTiles;
    QMenu *menuEdition;
    QMenu *menuGrille;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Interface)
    {
        if (Interface->objectName().isEmpty())
            Interface->setObjectName(QString::fromUtf8("Interface"));
        Interface->resize(1100, 697);
        Interface->setMinimumSize(QSize(1100, 697));
        Interface->setMaximumSize(QSize(1100, 697));
        createMap = new QAction(Interface);
        createMap->setObjectName(QString::fromUtf8("createMap"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/icon_new.png"), QSize(), QIcon::Normal, QIcon::Off);
        createMap->setIcon(icon);
        loadMap = new QAction(Interface);
        loadMap->setObjectName(QString::fromUtf8("loadMap"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/icon_open.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadMap->setIcon(icon1);
        sendMap = new QAction(Interface);
        sendMap->setObjectName(QString::fromUtf8("sendMap"));
        saveMap = new QAction(Interface);
        saveMap->setObjectName(QString::fromUtf8("saveMap"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/icon_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveMap->setIcon(icon2);
        version = new QAction(Interface);
        version->setObjectName(QString::fromUtf8("version"));
        version->setEnabled(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        version->setIcon(icon3);
        addTile = new QAction(Interface);
        addTile->setObjectName(QString::fromUtf8("addTile"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/icon_new_tile.png"), QSize(), QIcon::Normal, QIcon::Off);
        addTile->setIcon(icon4);
        loadTiles = new QAction(Interface);
        loadTiles->setObjectName(QString::fromUtf8("loadTiles"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/icon_open_tiles.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadTiles->setIcon(icon5);
        saveTiles = new QAction(Interface);
        saveTiles->setObjectName(QString::fromUtf8("saveTiles"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/icon_save_tiles.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveTiles->setIcon(icon6);
        deleteTiles = new QAction(Interface);
        deleteTiles->setObjectName(QString::fromUtf8("deleteTiles"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/icon_delete_tiles.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteTiles->setIcon(icon7);
        save_asMap = new QAction(Interface);
        save_asMap->setObjectName(QString::fromUtf8("save_asMap"));
        save_asMap->setIcon(icon2);
        save_asTiles = new QAction(Interface);
        save_asTiles->setObjectName(QString::fromUtf8("save_asTiles"));
        save_asTiles->setIcon(icon6);
        getBack = new QAction(Interface);
        getBack->setObjectName(QString::fromUtf8("getBack"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/icon_backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        getBack->setIcon(icon8);
        getForward = new QAction(Interface);
        getForward->setObjectName(QString::fromUtf8("getForward"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icons/icon_forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        getForward->setIcon(icon9);
        enableGrid = new QAction(Interface);
        enableGrid->setObjectName(QString::fromUtf8("enableGrid"));
        enableGrid->setCheckable(true);
        enableGrid->setChecked(true);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icons/icon_grid.png"), QSize(), QIcon::Normal, QIcon::Off);
        enableGrid->setIcon(icon10);
        zoomIn = new QAction(Interface);
        zoomIn->setObjectName(QString::fromUtf8("zoomIn"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icons/icon_zoomin.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomIn->setIcon(icon11);
        zoomOut = new QAction(Interface);
        zoomOut->setObjectName(QString::fromUtf8("zoomOut"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icons/icon_zoomout.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomOut->setIcon(icon12);
        goto_cell = new QAction(Interface);
        goto_cell->setObjectName(QString::fromUtf8("goto_cell"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icons/go_to.png"), QSize(), QIcon::Normal, QIcon::Off);
        goto_cell->setIcon(icon13);
        Container = new QWidget(Interface);
        Container->setObjectName(QString::fromUtf8("Container"));
        frame = new QFrame(Container);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(280, 140, 791, 431));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        VBar = new QScrollBar(Container);
        VBar->setObjectName(QString::fromUtf8("VBar"));
        VBar->setGeometry(QRect(1070, 140, 20, 431));
        VBar->setMaximum(0);
        VBar->setOrientation(Qt::Vertical);
        HBar = new QScrollBar(Container);
        HBar->setObjectName(QString::fromUtf8("HBar"));
        HBar->setGeometry(QRect(280, 570, 791, 20));
        HBar->setMaximum(0);
        HBar->setOrientation(Qt::Horizontal);
        tab_selector = new QTabWidget(Container);
        tab_selector->setObjectName(QString::fromUtf8("tab_selector"));
        tab_selector->setGeometry(QRect(20, 320, 225, 301));
        tab_selector->setMinimumSize(QSize(0, 0));
        tab_selector->setMaximumSize(QSize(225, 460));
        tab_light = new QWidget();
        tab_light->setObjectName(QString::fromUtf8("tab_light"));
        scroll_area_light = new QScrollArea(tab_light);
        scroll_area_light->setObjectName(QString::fromUtf8("scroll_area_light"));
        scroll_area_light->setGeometry(QRect(0, 0, 217, 271));
        scroll_area_light->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scroll_area_light->setWidgetResizable(true);
        scroll_light = new QWidget();
        scroll_light->setObjectName(QString::fromUtf8("scroll_light"));
        scroll_light->setGeometry(QRect(0, 0, 215, 269));
        formLayoutWidget_2 = new QWidget(scroll_light);
        formLayoutWidget_2->setObjectName(QString::fromUtf8("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(0, 0, 211, 399));
        formLayout_3 = new QFormLayout(formLayoutWidget_2);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(formLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_3->setWidget(0, QFormLayout::SpanningRole, label_6);

        light_radius = new QSpinBox(formLayoutWidget_2);
        light_radius->setObjectName(QString::fromUtf8("light_radius"));
        light_radius->setMaximum(500);
        light_radius->setValue(200);

        formLayout_3->setWidget(1, QFormLayout::FieldRole, light_radius);

        label_7 = new QLabel(formLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_3->setWidget(2, QFormLayout::FieldRole, label_7);

        light_intensity = new QSpinBox(formLayoutWidget_2);
        light_intensity->setObjectName(QString::fromUtf8("light_intensity"));
        light_intensity->setMaximum(500);
        light_intensity->setValue(150);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, light_intensity);

        label_8 = new QLabel(formLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        formLayout_3->setWidget(4, QFormLayout::FieldRole, label_8);

        light_quality = new QSpinBox(formLayoutWidget_2);
        light_quality->setObjectName(QString::fromUtf8("light_quality"));
        light_quality->setMaximum(250);
        light_quality->setValue(30);

        formLayout_3->setWidget(5, QFormLayout::FieldRole, light_quality);

        label_10 = new QLabel(formLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        formLayout_3->setWidget(6, QFormLayout::FieldRole, label_10);

        light_opening_angle = new QDoubleSpinBox(formLayoutWidget_2);
        light_opening_angle->setObjectName(QString::fromUtf8("light_opening_angle"));
        light_opening_angle->setMaximum(360);
        light_opening_angle->setValue(360);

        formLayout_3->setWidget(7, QFormLayout::FieldRole, light_opening_angle);

        label_11 = new QLabel(formLayoutWidget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        formLayout_3->setWidget(8, QFormLayout::FieldRole, label_11);

        light_angle = new QDoubleSpinBox(formLayoutWidget_2);
        light_angle->setObjectName(QString::fromUtf8("light_angle"));
        light_angle->setMaximum(360);
        light_angle->setValue(180);

        formLayout_3->setWidget(9, QFormLayout::FieldRole, light_angle);

        label_12 = new QLabel(formLayoutWidget_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        formLayout_3->setWidget(10, QFormLayout::FieldRole, label_12);

        light_color = new QPushButton(formLayoutWidget_2);
        light_color->setObjectName(QString::fromUtf8("light_color"));
        light_color->setStyleSheet(QString::fromUtf8("QPushButton { background : rgb( 255,255,255) }"));

        formLayout_3->setWidget(11, QFormLayout::FieldRole, light_color);

        scroll_area_light->setWidget(scroll_light);
        tab_selector->addTab(tab_light, QString());
        widget = new QWidget(Container);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 150, 241, 161));
        layer_manager = new QTreeView(widget);
        layer_manager->setObjectName(QString::fromUtf8("layer_manager"));
        layer_manager->setGeometry(QRect(0, 30, 240, 125));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(layer_manager->sizePolicy().hasHeightForWidth());
        layer_manager->setSizePolicy(sizePolicy);
        layer_manager->setMinimumSize(QSize(240, 125));
        layer_manager->setMaximumSize(QSize(240, 125));
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 0, 240, 25));
        widget_2->setMaximumSize(QSize(240, 25));
        layer_delete = new QPushButton(widget_2);
        layer_delete->setObjectName(QString::fromUtf8("layer_delete"));
        layer_delete->setGeometry(QRect(60, 0, 61, 26));
        layer_delete->setMaximumSize(QSize(1000, 1000));
        layer_add = new QPushButton(widget_2);
        layer_add->setObjectName(QString::fromUtf8("layer_add"));
        layer_add->setGeometry(QRect(0, 0, 61, 26));
        layer_add->setMaximumSize(QSize(1000, 1000));
        layer_down = new QPushButton(widget_2);
        layer_down->setObjectName(QString::fromUtf8("layer_down"));
        layer_down->setGeometry(QRect(180, 0, 61, 26));
        layer_down->setMinimumSize(QSize(55, 25));
        layer_down->setMaximumSize(QSize(1000, 1000));
        layer_up = new QPushButton(widget_2);
        layer_up->setObjectName(QString::fromUtf8("layer_up"));
        layer_up->setGeometry(QRect(120, 0, 61, 26));
        layer_up->setMinimumSize(QSize(55, 25));
        layer_up->setMaximumSize(QSize(1000, 1000));
        tile_list = new QTreeView(Container);
        tile_list->setObjectName(QString::fromUtf8("tile_list"));
        tile_list->setGeometry(QRect(280, 10, 405, 121));
        tile_view = new QListView(Container);
        tile_view->setObjectName(QString::fromUtf8("tile_view"));
        tile_view->setGeometry(QRect(685, 10, 405, 121));
        tool_box = new QGroupBox(Container);
        tool_box->setObjectName(QString::fromUtf8("tool_box"));
        tool_box->setEnabled(true);
        tool_box->setGeometry(QRect(20, 10, 151, 120));
        tool_box->setMinimumSize(QSize(151, 120));
        tool_box->setMaximumSize(QSize(151, 120));
        tool_box->setCheckable(false);
        tool_place = new QToolButton(tool_box);
        tool_place->setObjectName(QString::fromUtf8("tool_place"));
        tool_place->setGeometry(QRect(50, 20, 50, 50));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icons/icon_place.png"), QSize(), QIcon::Normal, QIcon::Off);
        tool_place->setIcon(icon14);
        tool_place->setIconSize(QSize(35, 35));
        tool_place->setCheckable(true);
        tool_place->setChecked(false);
        tool_collision = new QToolButton(tool_box);
        tool_collision->setObjectName(QString::fromUtf8("tool_collision"));
        tool_collision->setGeometry(QRect(100, 70, 50, 50));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icons/icon_collision.png"), QSize(), QIcon::Normal, QIcon::Off);
        tool_collision->setIcon(icon15);
        tool_collision->setIconSize(QSize(50, 50));
        tool_collision->setCheckable(true);
        tool_light = new QToolButton(tool_box);
        tool_light->setObjectName(QString::fromUtf8("tool_light"));
        tool_light->setGeometry(QRect(0, 70, 50, 50));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icons/icon_light.png"), QSize(), QIcon::Normal, QIcon::Off);
        tool_light->setIcon(icon16);
        tool_light->setIconSize(QSize(40, 40));
        tool_light->setCheckable(true);
        tool_delete = new QToolButton(tool_box);
        tool_delete->setObjectName(QString::fromUtf8("tool_delete"));
        tool_delete->setGeometry(QRect(100, 20, 50, 50));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/icons/icon_delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        tool_delete->setIcon(icon17);
        tool_delete->setIconSize(QSize(35, 35));
        tool_delete->setCheckable(true);
        tool_height = new QToolButton(tool_box);
        tool_height->setObjectName(QString::fromUtf8("tool_height"));
        tool_height->setGeometry(QRect(50, 70, 50, 50));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/icons/icon_height.png"), QSize(), QIcon::Normal, QIcon::Off);
        tool_height->setIcon(icon18);
        tool_height->setIconSize(QSize(35, 35));
        tool_height->setCheckable(true);
        tool_move = new QToolButton(tool_box);
        tool_move->setObjectName(QString::fromUtf8("tool_move"));
        tool_move->setGeometry(QRect(0, 20, 50, 50));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/icons/move.png"), QSize(), QIcon::Normal, QIcon::On);
        tool_move->setIcon(icon19);
        tool_move->setIconSize(QSize(35, 35));
        tool_move->setCheckable(true);
        Interface->setCentralWidget(Container);
        menubar = new QMenuBar(Interface);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1100, 20));
        menuCarte = new QMenu(menubar);
        menuCarte->setObjectName(QString::fromUtf8("menuCarte"));
        infos = new QMenu(menubar);
        infos->setObjectName(QString::fromUtf8("infos"));
        menuTiles = new QMenu(menubar);
        menuTiles->setObjectName(QString::fromUtf8("menuTiles"));
        menuEdition = new QMenu(menubar);
        menuEdition->setObjectName(QString::fromUtf8("menuEdition"));
        menuGrille = new QMenu(menubar);
        menuGrille->setObjectName(QString::fromUtf8("menuGrille"));
        Interface->setMenuBar(menubar);
        statusbar = new QStatusBar(Interface);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Interface->setStatusBar(statusbar);
        toolBar = new QToolBar(Interface);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        Interface->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuCarte->menuAction());
        menubar->addAction(menuTiles->menuAction());
        menubar->addAction(menuEdition->menuAction());
        menubar->addAction(menuGrille->menuAction());
        menubar->addAction(infos->menuAction());
        menuCarte->addAction(createMap);
        menuCarte->addAction(loadMap);
        menuCarte->addAction(saveMap);
        menuCarte->addAction(save_asMap);
        menuCarte->addAction(sendMap);
        infos->addAction(version);
        menuTiles->addAction(addTile);
        menuTiles->addAction(loadTiles);
        menuTiles->addAction(saveTiles);
        menuTiles->addAction(save_asTiles);
        menuTiles->addAction(deleteTiles);
        menuEdition->addAction(getForward);
        menuEdition->addAction(getBack);
        menuGrille->addAction(zoomIn);
        menuGrille->addAction(zoomOut);
        menuGrille->addAction(enableGrid);
        menuGrille->addAction(goto_cell);
        toolBar->addSeparator();
        toolBar->addAction(createMap);
        toolBar->addAction(loadMap);
        toolBar->addAction(saveMap);
        toolBar->addSeparator();
        toolBar->addAction(addTile);
        toolBar->addAction(loadTiles);
        toolBar->addAction(saveTiles);
        toolBar->addAction(deleteTiles);
        toolBar->addSeparator();
        toolBar->addAction(getBack);
        toolBar->addAction(getForward);
        toolBar->addSeparator();
        toolBar->addAction(zoomOut);
        toolBar->addAction(zoomIn);
        toolBar->addAction(enableGrid);
        toolBar->addAction(goto_cell);

        retranslateUi(Interface);

        tab_selector->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Interface);
    } // setupUi

    void retranslateUi(QMainWindow *Interface)
    {
        Interface->setWindowTitle(QApplication::translate("Interface", "Map Creator", 0, QApplication::UnicodeUTF8));
        createMap->setText(QApplication::translate("Interface", "Nouvelle Carte", 0, QApplication::UnicodeUTF8));
        createMap->setShortcut(QApplication::translate("Interface", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        loadMap->setText(QApplication::translate("Interface", "Ouvrir", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        loadMap->setToolTip(QApplication::translate("Interface", "Charger une Carte", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        loadMap->setShortcut(QApplication::translate("Interface", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        sendMap->setText(QApplication::translate("Interface", "Envoyer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sendMap->setToolTip(QApplication::translate("Interface", "Envoyer une Carte", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveMap->setText(QApplication::translate("Interface", "Enregistrer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveMap->setToolTip(QApplication::translate("Interface", "Enregistrer la Carte", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveMap->setShortcut(QApplication::translate("Interface", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        version->setText(QApplication::translate("Interface", "Map Creator ", 0, QApplication::UnicodeUTF8));
        addTile->setText(QApplication::translate("Interface", "Editeur de Tiles", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addTile->setToolTip(QApplication::translate("Interface", "Ajouter un Tile", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addTile->setShortcut(QApplication::translate("Interface", "Ctrl+T", 0, QApplication::UnicodeUTF8));
        loadTiles->setText(QApplication::translate("Interface", "Ouvrir", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        loadTiles->setToolTip(QApplication::translate("Interface", "Charger des Tiles", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        loadTiles->setShortcut(QApplication::translate("Interface", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        saveTiles->setText(QApplication::translate("Interface", "Enregistrer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveTiles->setToolTip(QApplication::translate("Interface", "Enregistrer les Tiles", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveTiles->setShortcut(QApplication::translate("Interface", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        deleteTiles->setText(QApplication::translate("Interface", "Supprimer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        deleteTiles->setToolTip(QApplication::translate("Interface", "Supprimer des Tiles", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        deleteTiles->setShortcut(QApplication::translate("Interface", "Ctrl+D", 0, QApplication::UnicodeUTF8));
        save_asMap->setText(QApplication::translate("Interface", "Enregistrer sous", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        save_asMap->setToolTip(QApplication::translate("Interface", "Enregistrer la Carte", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        save_asTiles->setText(QApplication::translate("Interface", "Enregistrer sous", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        save_asTiles->setToolTip(QApplication::translate("Interface", "Enregistrer les Tiles", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        getBack->setText(QApplication::translate("Interface", "Annluer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        getBack->setToolTip(QApplication::translate("Interface", "Revenir en Arri\303\250re", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        getBack->setShortcut(QApplication::translate("Interface", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        getForward->setText(QApplication::translate("Interface", "Repeter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        getForward->setToolTip(QApplication::translate("Interface", "Retour en Avant", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        getForward->setShortcut(QApplication::translate("Interface", "Ctrl+Y", 0, QApplication::UnicodeUTF8));
        enableGrid->setText(QApplication::translate("Interface", "Grille", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        enableGrid->setToolTip(QApplication::translate("Interface", "Activer/Desactiver la Grille", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        enableGrid->setShortcut(QApplication::translate("Interface", "Ctrl+G", 0, QApplication::UnicodeUTF8));
        zoomIn->setText(QApplication::translate("Interface", "Zoomer", 0, QApplication::UnicodeUTF8));
        zoomIn->setShortcut(QApplication::translate("Interface", "Ctrl+=", 0, QApplication::UnicodeUTF8));
        zoomOut->setText(QApplication::translate("Interface", "Dezoomer", 0, QApplication::UnicodeUTF8));
        zoomOut->setShortcut(QApplication::translate("Interface", "Ctrl+-", 0, QApplication::UnicodeUTF8));
        goto_cell->setText(QApplication::translate("Interface", "Aller \303\240 ...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        goto_cell->setToolTip(QApplication::translate("Interface", "Aller \303\240 la case", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_6->setText(QApplication::translate("Interface", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Rayon</p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Interface", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Intensit\303\251</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Interface", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Qualit\303\251</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Interface", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Angle d'ouverture</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Interface", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Angle</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Interface", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Couleur</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        light_color->setText(QString());
        tab_selector->setTabText(tab_selector->indexOf(tab_light), QApplication::translate("Interface", "Lumi\303\250res", 0, QApplication::UnicodeUTF8));
        layer_delete->setText(QApplication::translate("Interface", "Supprimer", 0, QApplication::UnicodeUTF8));
        layer_add->setText(QApplication::translate("Interface", "Nouveau", 0, QApplication::UnicodeUTF8));
        layer_down->setText(QApplication::translate("Interface", "Descendre", 0, QApplication::UnicodeUTF8));
        layer_up->setText(QApplication::translate("Interface", "Monter", 0, QApplication::UnicodeUTF8));
        tool_box->setTitle(QApplication::translate("Interface", "Outils", 0, QApplication::UnicodeUTF8));
        tool_place->setText(QString());
        tool_collision->setText(QString());
        tool_light->setText(QString());
        tool_delete->setText(QString());
        tool_height->setText(QString());
        tool_move->setText(QApplication::translate("Interface", "...", 0, QApplication::UnicodeUTF8));
        menuCarte->setTitle(QApplication::translate("Interface", "Carte", 0, QApplication::UnicodeUTF8));
        infos->setTitle(QApplication::translate("Interface", "A propos", 0, QApplication::UnicodeUTF8));
        menuTiles->setTitle(QApplication::translate("Interface", "Tiles", 0, QApplication::UnicodeUTF8));
        menuEdition->setTitle(QApplication::translate("Interface", "Edition", 0, QApplication::UnicodeUTF8));
        menuGrille->setTitle(QApplication::translate("Interface", "Vue", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("Interface", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Interface: public Ui_Interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERFACE_H
