#include "MainWindow.h"
#include "NewMapDialog.hpp"
#include "MANAGERS/TileManager.h"
#include "GAME_ELEMENTS/Effect.h"
#include "SYSTEM/GoToWidget.h"
#include "MANAGERS/TileManager.h"
#include "GAME_ELEMENTS/Selector.h"

#include <QToolBar>
#include <QDockWidget>
#include <QScrollArea>
#include <QToolBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_carteMenu(NULL)
    , m_tileMenu(NULL)
    , m_editionMenu(NULL)
    , m_vueMenu(NULL)
    , m_aProposMenu(NULL)
    , m_affichageMenu(NULL)
    , m_newMapAction(NULL)
    , m_openMapAction(NULL)
    , m_saveMapAction(NULL)
    , m_saveAsMapAction(NULL)
    , m_openTileEditorAction(NULL)
    , m_redoAction(NULL)
    , m_undoAction(NULL)
    , m_zoomAction(NULL)
    , m_dezoomAction(NULL)
    , m_grilleAction(NULL)
    , m_aProposAction(NULL)
    , m_moveTo(NULL)
    , m_tileEditor(NULL)
    , m_baseEngine(NULL)
    , m_toolWidget(NULL)
    , m_engine(NULL)
    , m_editor(NULL)
    , m_layerWidget(NULL)
    , m_sfmlWidgetArea(NULL)
    , m_lightWidget(NULL)
    , m_tilesWidget(NULL)
{
    setWindowState(windowState() | Qt::WindowMaximized);
    buildGUI();
    buildDock();
}

void MainWindow::buildGUI()
{
    createAction();
    createMenu();
    createToolBar();
    QWidget *mainWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainWidget->setLayout(mainLayout);

    buildSFML(mainLayout);

    setCentralWidget(mainWidget);
}

void MainWindow::buildDock()
{
    QDockWidget *toolDock = new QDockWidget("Outils", this);
    m_toolWidget = new ToolWidget(this);
    connect(m_toolWidget, SIGNAL(toolSelected(int)), this, SLOT(toolSelected(int)));
    toolDock->setWidget(m_toolWidget);
    addDockWidget(Qt::LeftDockWidgetArea, toolDock);
    m_affichageMenu->addAction(toolDock->toggleViewAction());

    QDockWidget *layerDock = new QDockWidget("Layers", this);
    m_layerWidget = new LayerWidget(this);
    layerDock->setWidget(m_layerWidget);
    addDockWidget(Qt::LeftDockWidgetArea, layerDock);
    m_affichageMenu->addAction(layerDock->toggleViewAction());
    connect(m_layerWidget, SIGNAL(layerSelected(int,bool)), this, SLOT(layerChanged(int,bool)));

    QDockWidget *lightDock = new QDockWidget("Lumières", this);
    m_lightWidget = new LightWidget(this);
    lightDock->setWidget(m_lightWidget);
    addDockWidget(Qt::LeftDockWidgetArea, lightDock);
    m_affichageMenu->addAction(lightDock->toggleViewAction());
    connect(m_lightWidget, SIGNAL(lightChanged()), this, SLOT(lightChanged()));

    QDockWidget *tilesDock = new QDockWidget("Tiles", this);
    m_tilesWidget = new TilesWidget(this);
    connect(m_tilesWidget, SIGNAL(tileSelected(int)), this, SLOT(tileChanged(int)));
    tilesDock->setWidget(m_tilesWidget);
    addDockWidget(Qt::RightDockWidgetArea, tilesDock);
    m_affichageMenu->addAction(tilesDock->toggleViewAction());
}

void MainWindow::buildSFML(QHBoxLayout *mainLayout)
{
    m_sfmlWidgetArea = new QScrollArea(this);
    m_sfmlWidgetArea->setMinimumSize(830,630);
    m_sfmlWidgetArea->setMaximumSize(830,630);
    QHBoxLayout *layout = new QHBoxLayout;
    m_sfmlWidgetArea->setLayout(layout);

    QScrollBar *hbar = new QScrollBar(this);
    connect(hbar, SIGNAL(valueChanged(int)), this, SLOT(horizontalBarValueChanged(int)));
    hbar->setOrientation(Qt::Horizontal);

    QScrollBar *vbar = new QScrollBar(this);
    connect(vbar, SIGNAL(valueChanged(int)), this, SLOT(verticalBarValueChanged(int)));
    vbar->setOrientation(Qt::Vertical);

    m_sfmlWidgetArea->setHorizontalScrollBar(hbar);
    m_sfmlWidgetArea->setVerticalScrollBar(vbar);

    m_sfmlWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    m_sfmlWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    m_engine = new BaseEngine(this, QPoint(0,0), QSize(800,600));
    connect(m_engine, SIGNAL(mapMoved()), this, SLOT(mapMoved()));
    layout->addWidget(m_engine);

    connect(&(m_engine->getSelector()), SIGNAL(selectorMoved(sf::Vector2i)), this, SLOT(selectorMoved(sf::Vector2i)));
    mainLayout->addWidget(m_sfmlWidgetArea);
}

void MainWindow::createAction()
{
    m_newMapAction = new QAction(QIcon(":/icons/icon_new.png"),"Nouvelle carte", this);
    m_newMapAction->setShortcut(QKeySequence("Ctrl+N"));
    connect(m_newMapAction, SIGNAL(triggered()), this, SLOT(newMap()));

    m_openMapAction = new QAction(QIcon(":/icons/icon_open.png"),"Ouvrir", this);
    m_openMapAction->setShortcut(QKeySequence("Ctrl+O"));
    connect(m_openMapAction, SIGNAL(triggered()), this, SLOT(openMap()));

    m_saveMapAction = new QAction(QIcon(":/icons/icon_save.png"),"Enregistrer", this);
    m_saveMapAction->setShortcut(QKeySequence("Ctrl+S"));
    connect(m_saveMapAction, SIGNAL(triggered()), this, SLOT(saveMap()));
    m_saveMapAction->setDisabled(true);

    m_saveAsMapAction = new QAction(QIcon(":/icons/icon_save.png"),"Enregistrer sous", this);
    m_saveAsMapAction->setShortcut(QKeySequence("Ctrl+Shift+S"));
    connect(m_saveAsMapAction, SIGNAL(triggered()), this, SLOT(saveAsMap()));
    m_saveAsMapAction->setDisabled(true);

    m_closeAction = new QAction("Quitter", this);
    m_closeAction->setShortcut(QKeySequence("Ctrl+X"));
    connect(m_closeAction, SIGNAL(triggered()), this, SLOT(close()));

    m_openTileEditorAction = new QAction(QIcon(":/icons/icon_new_tile.png"),"Editeur de Tiles", this);
    m_openTileEditorAction->setShortcut(QKeySequence("Ctrl+T"));
    connect(m_openTileEditorAction, SIGNAL(triggered()), this, SLOT(openTileEditor()));

    m_redoAction = new QAction(QIcon(":/icons/icon_forward.png"),"Annuler", this);
    m_redoAction->setShortcut(QKeySequence("Ctrl+Z"));
    connect(m_redoAction, SIGNAL(triggered()), this, SLOT(redo()));

    m_undoAction = new QAction(QIcon(":/icons/icon_backward.png"),"Repeter", this);
    m_undoAction->setShortcut(QKeySequence("Ctrl+Y"));
    connect(m_undoAction, SIGNAL(triggered()), this, SLOT(undo()));

    m_zoomAction = new QAction(QIcon(":/icons/icon_zoomin.png"),"Zoomer", this);
    m_zoomAction->setShortcut(QKeySequence("Ctrl+="));
    connect(m_zoomAction, SIGNAL(triggered()), this, SLOT(zoom()));

    m_dezoomAction = new QAction(QIcon(":/icons/icon_zoomout.png"),"Dezoomer", this);
    m_dezoomAction->setShortcut(QKeySequence("Ctrl+-"));
    connect(m_dezoomAction, SIGNAL(triggered()), this, SLOT(dezoom()));

    m_grilleAction = new QAction(QIcon(":/icons/icon_grid.png"),"Grille", this);
    m_grilleAction->setShortcut(QKeySequence("Ctrl+G"));
    m_grilleAction->setCheckable(true);
    m_grilleAction->setChecked(true);
    connect(m_grilleAction, SIGNAL(triggered()), this, SLOT(showGrille()));

    m_aProposAction = new QAction("A propos", this);
    connect(m_aProposAction, SIGNAL(triggered()), this, SLOT(openAPropos()));

    m_moveTo = new QAction(QIcon(":/icons/go_to.png"),"Allez à..", this);
    connect(m_moveTo, SIGNAL(triggered()), this, SLOT(moveTo()));
}

void MainWindow::createMenu()
{
    m_carteMenu = menuBar()->addMenu("Carte");
    m_carteMenu->addAction(m_newMapAction);
    m_carteMenu->addAction(m_openMapAction);
    m_carteMenu->addAction(m_saveMapAction);
    m_carteMenu->addAction(m_saveAsMapAction);
    m_carteMenu->addAction(m_closeAction);

    m_tileMenu = menuBar()->addMenu("Tiles");
    m_tileMenu->addAction(m_openTileEditorAction);

    m_editionMenu = menuBar()->addMenu("Edition");
    m_editionMenu->addAction(m_redoAction);
    m_editionMenu->addAction(m_undoAction);

    m_affichageMenu = menuBar()->addMenu("Affichage");

    m_vueMenu = menuBar()->addMenu("Vue");
    m_vueMenu->addAction(m_zoomAction);
    m_vueMenu->addAction(m_dezoomAction);
    m_vueMenu->addAction(m_grilleAction);
    m_vueMenu->addAction(m_moveTo);

    m_aProposMenu = menuBar()->addMenu("A propos");
    m_aProposMenu->addAction(m_aProposAction);
}

void MainWindow::createToolBar()
{
    QToolBar* bar = addToolBar("");
    bar->addAction(m_newMapAction);
    bar->addAction(m_openMapAction);
    bar->addAction(m_saveMapAction);
    bar->addSeparator();
    bar->addAction(m_openTileEditorAction);
    bar->addSeparator();
    bar->addAction(m_undoAction);
    bar->addAction(m_redoAction);
    bar->addSeparator();
    bar->addAction(m_zoomAction);
    bar->addAction(m_dezoomAction);
    bar->addAction(m_grilleAction);
    bar->addAction(m_moveTo);
}

void MainWindow::newMap()
{
    QSize size;
    QString name;
    NewMapDialog *d = new NewMapDialog(&size, &name, this);
    int ret = d->exec();
    if(ret == QDialog::Rejected)
        return;

    setWindowTitle("Map Creator - [ "+name+" ]");

    m_engine->resetEngine();
    m_engine->getManager()->createMap(sf::Vector2i(size.width(), size.height()));
    m_engine->getManager()->setName(name);

    QScrollBar *hbar = m_sfmlWidgetArea->horizontalScrollBar();
    QScrollBar *vbar = m_sfmlWidgetArea->verticalScrollBar();

    vbar->setMaximum(m_engine->getManager()->mapSize().x * SCROLL_PRECISION);
    hbar->setMaximum(m_engine->getManager()->mapSize().y * SCROLL_PRECISION);

    vbar->setValue(0);
    hbar->blockSignals(true);
    hbar->setValue((m_engine->getManager()->mapSize().y * SCROLL_PRECISION)/2);
    hbar->blockSignals(false);


    m_engine->getRender()->updateScrollBox();

    m_saveMapAction->setEnabled(true);

    m_engine->getManager()->removeAllLayers();

    // on rajoute les layers de bases
    GameLayer* selector_layer = m_engine->getManager()->addLayer(-2, "Selecteur", true, true);
    if(selector_layer == NULL)
    {
        qDebug() << "Impossible de creer le layer -2 dans " << __FILE__ << __LINE__;
        exit(0);
    }

    GameLayer* collision_layer = m_engine->getManager()->addLayer(-1, "Couche SYSTEM", false, true);
    if(collision_layer == NULL)
    {
        qDebug() << "Impossible de creer le layer -1 dans " << __FILE__ << __LINE__;
        exit(0);
    }

    m_layerWidget->setMapManager(m_engine->getManager());
    m_layerWidget->newLayer();
}

void MainWindow::openMap()
{

}

void MainWindow::saveMap()
{

}

void MainWindow::saveAsMap()
{

}

void MainWindow::openTileEditor()
{
    m_tileEditor = new TileEditorDialog(this);
    m_tileEditor->show();

    connect(m_tileEditor, SIGNAL(tileAdded()), this, SLOT(populateTile()));
}

void MainWindow::redo()
{
    m_engine->loadNextCell();
}

void MainWindow::undo()
{
    m_engine->loadLastCell();
}

void MainWindow::zoom()
{
    m_engine->getRender()->setZoom(m_engine->getRender()->getZoom()+POSITIVE_ZOOM,ZOOM_TIME);
}

void MainWindow::dezoom()
{
    m_engine->getRender()->setZoom(m_engine->getRender()->getZoom()+NEGATIVE_ZOOM,ZOOM_TIME);
}

void MainWindow::showGrille()
{
    m_engine->getRender()->showGrid(m_grilleAction->isChecked());
}

void MainWindow::openAPropos()
{
    QDialog* version = new QDialog ();
    version->setModal(true);
    version->setWindowTitle("Version");
    QVBoxLayout *layout = new QVBoxLayout (version);

    QLabel* Label = new QLabel ("Map Creator est developpé dans le cardre d'un jeu MMORPG");
    QLabel* Label2 = new QLabel ("Revision "+ toString(REVISION) +" - Alpha");
    QLabel* Label3 = new QLabel ("Si vous etes un graphiste, et voulez joindre le projet, vous pouvez me contacter sur le site du zero : <a href=\"www.siteduzero.com/membres-294-291282.html\">Pti'Zero</a>");
    Label3->setOpenExternalLinks(true);

    layout->addWidget(Label, 0, Qt::AlignHCenter);
    layout->addWidget(Label2, 0, Qt::AlignHCenter);
    layout->addWidget(Label3, 0, Qt::AlignHCenter);

    version->exec();
}

void MainWindow::verticalBarValueChanged(int value)
{
    QScrollBar *vbar = m_sfmlWidgetArea->verticalScrollBar();
    QScrollBar *hbar = m_sfmlWidgetArea->horizontalScrollBar();
    sf::Vector2i mapSize = m_engine->getManager()->getSize();

    int x = ((float(hbar->value())/float(hbar->maximum()))-0.5)*mapSize.x*CELL_SIZE_X;
    int y = (float(value)/float(vbar->maximum()))*mapSize.y*CELL_SIZE_Y;

    m_engine->getRender()->setViewPosition(sf::Vector2f(x,y));
}

void MainWindow::horizontalBarValueChanged(int value)
{
    QScrollBar *vbar = m_sfmlWidgetArea->verticalScrollBar();
    QScrollBar *hbar = m_sfmlWidgetArea->horizontalScrollBar();

    sf::Vector2i mapSize = m_engine->getManager()->getSize();
    int x = ((float(value)/float(hbar->maximum()))-0.5)*mapSize.x*CELL_SIZE_X;
    int y = (float(vbar->value())/float(vbar->maximum()))*mapSize.y*CELL_SIZE_Y;

    m_engine->getRender()->setViewPosition(sf::Vector2f(x,y));
}

void MainWindow::toolSelected(int tool)
{
    if(m_engine != NULL)
        m_engine->setTool(static_cast<TOOL>(tool));
}

void MainWindow::moveTo()
{
    QSize position;
    position.setHeight(0);
    position.setWidth(0);
    GoToWidget *dialog = new GoToWidget(m_engine->getManager(), &position, this);
    dialog->exec();

    m_engine->getRender()->setViewVPosition(sf::Vector2i(position.width(), position.height()),1500);
}

void MainWindow::mapMoved()
{
    sf::Vector2i mapSize = m_engine->getManager()->getSize();
    QScrollBar *hbar = m_sfmlWidgetArea->horizontalScrollBar();
    QScrollBar *vbar = m_sfmlWidgetArea->verticalScrollBar();
    sf::Vector2f position = m_engine->getRender()->getViewPosition();

    float hvalue = ((position.x / (CELL_SIZE_X*mapSize.x))+0.5)*hbar->maximum();
    float vvalue = (position.y / (CELL_SIZE_Y*mapSize.y))*vbar->maximum();

    hbar->blockSignals(true);
    hbar->setValue(hvalue);
    hbar->blockSignals(false);

    vbar->blockSignals(true);
    vbar->setValue(vvalue);
    vbar->blockSignals(false);
}

void MainWindow::populateTile()
{
    if(m_tilesWidget == NULL)
        return;
    m_tilesWidget->update();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    TileManagerSingleton::clear();
    EffectManagerSingleton::clear();
    event->accept();
}

void MainWindow::layerChanged(int layerId, bool checked)
{
    m_engine->setLayerFocus(layerId);

    GameLayer *layer = m_engine->getManager()->getLayer(layerId);

    layer->setVisible(checked);
}

void MainWindow::lightChanged()
{
    if(m_engine == NULL || m_lightWidget == NULL)
        return;

    int rayon = m_lightWidget->getRayon();
    int intensite = m_lightWidget->getIntensite();
    int qualite = m_lightWidget->getQualite();
    double angle = m_lightWidget->getAngle();
    double angleOuverture = m_lightWidget->getAngleOuverture();
    QColor color = m_lightWidget->getColor();

    m_engine->setLight(rayon, qualite, intensite, color, angleOuverture, angle);
    m_toolWidget->selectButton(TOOL_LIGHT);
}

void MainWindow::tileChanged(int idTile)
{
    m_engine->setTileChoice(idTile);
    m_toolWidget->selectButton(TOOL_PLACE);
}

void MainWindow::selectorMoved(sf::Vector2i position)
{
    QString text = "Case courante: "+toString(position.x)+", "+toString(position.y);

    if (!m_engine->getManager()->inProportions(position))
        text+= " - Hors Carte";

    statusBar()->showMessage(text);
}
