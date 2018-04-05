#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QScrollArea>

#include "SYSTEM/BaseEngine.h"
#include "SYSTEM/TileEditorDialog.h"
#include "SYSTEM/ToolWidget.h"
#include "SYSTEM/LayerWidget.h"
#include "SYSTEM/LightWidget.h"
#include "SYSTEM/TilesWidget.h"

class QHBoxLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    
private:
    void buildGUI();
    void buildDock();
    void buildSFML(QHBoxLayout *layout);

    void createAction();
    void createMenu();
    void createToolBar();

protected:
    void closeEvent(QCloseEvent *);

private slots:
    void newMap();
    void openMap();
    void saveMap();
    void saveAsMap();

    void openTileEditor();
    void redo();
    void undo();

    void zoom();
    void dezoom();
    void showGrille();
    void openAPropos();

    void moveTo();

    void verticalBarValueChanged(int value);
    void horizontalBarValueChanged(int value);

    void toolSelected(int);

    void populateTile();

    void mapMoved();

    void layerChanged(int layerId, bool checked);

    void lightChanged();

    void tileChanged(int);

    void selectorMoved(sf::Vector2i);

private:
    QMenu *m_carteMenu;
    QMenu *m_tileMenu;
    QMenu *m_editionMenu;
    QMenu *m_vueMenu;
    QMenu *m_aProposMenu;
    QMenu *m_affichageMenu;

    QAction *m_newMapAction;
    QAction *m_openMapAction;
    QAction *m_saveMapAction;
    QAction *m_saveAsMapAction;
    QAction *m_closeAction;

    QAction *m_openTileEditorAction;
    QAction *m_redoAction;
    QAction *m_undoAction;

    QAction *m_zoomAction;
    QAction *m_dezoomAction;
    QAction *m_grilleAction;
    QAction *m_aProposAction;

    QAction *m_moveTo;

    TileEditorDialog *m_tileEditor;
    BaseEngine *m_baseEngine;

    ToolWidget *m_toolWidget;

    BaseEngine *m_engine;
    TileEditorDialog *m_editor;

    LayerWidget *m_layerWidget;

    QScrollArea *m_sfmlWidgetArea;

    LightWidget *m_lightWidget;

    TilesWidget *m_tilesWidget;
};

#endif // MAINWINDOW_H
