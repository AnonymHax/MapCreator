#include "TileEditorDialog.h"
#include "MANAGERS/TileManager.h"
#include "GAME_ELEMENTS/Effect.h"
#include "GAME_ELEMENTS/Cell.h"

#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QToolBar>
#include <QWidget>
#include <QFrame>
#include <QListWidget>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>

#define LABEL_FRAME_WIDTH 100
#define SPIN_FRAME_WIDTH 100
#define BUTTON_HEIGHT 50
#define SFML_WIDTH 800
#define SFML_HEIGHT 500

TileEditorDialog::TileEditorDialog(QWidget *parent) :
    QMainWindow(parent)
  , m_fileMenu(NULL)
  , m_newTileAction(NULL)
  , m_newAnimationAction(NULL)
  , m_modifTileAction(NULL)
  , m_addTextureAction(NULL)
  , m_boxName(NULL)
  , m_boxCube(NULL)
  , m_boxFrame(NULL)
  , m_name(NULL)
  , m_inverserCadre(NULL)
  , m_afficherCube(NULL)
  , m_axeHorizontal(NULL)
  , m_axisxInitAll(NULL)
  , m_axeVertical(NULL)
  , m_axisyInitAll(NULL)
  , m_dimensionHorizontal(NULL)
  , m_dimensionxInitAll(NULL)
  , m_dimensionVertical(NULL)
  , m_dimensionyInitAll(NULL)
  , m_intervalFrames(NULL)
  , m_intervalInitAll(NULL)
  , m_intervalRedemarrageCheckBox(NULL)
  , m_numberFrame(NULL)
  , m_previousFrame(NULL)
  , m_nextFrame(NULL)
  , m_renduButton(NULL)
  , m_addButton(NULL)
  , m_render(NULL)
  , m_mapRender(NULL)
  , m_map(NULL)
  , m_tile(NULL)
  , m_currentFrame(0)
  , m_currentAnimation("")
  , m_tileName("")
  , m_animationWidget(NULL)
  , m_animationModel(NULL)
  , m_tileAnimationData(NULL)
  , m_tileAnimationFrameData(NULL)
  , m_newAnimationButton(NULL)
  , m_newTextureButton(NULL)
  , m_upFrame(NULL)
  , m_downFrame(NULL)
  , m_deleteFrame(NULL)
  , m_cell(NULL)
  , m_added(false)
{
    setWindowState(windowState() | Qt::WindowMaximized);
    buildGUI();
}

TileEditorDialog::~TileEditorDialog()
{
    delete m_map;
    delete m_mapRender;

    if(m_tile != NULL && m_added == false)
        TileManagerSingleton::getInstance()->remove(m_tile->getId());
}

void TileEditorDialog::buildGUI()
{
    createAction();
    createMenu();
    createToolBar();

    QWidget *mainWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainWidget->setLayout(mainLayout);

    buildLeftPanel(mainLayout);

    QWidget *rightPanel = new QWidget(this);
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightPanel->setLayout(rightLayout);

    buildAnimation(rightLayout);
    buildRenderSFML(rightLayout);

    mainLayout->addWidget(rightPanel);
    mainLayout->addStretch();

    setCentralWidget(mainWidget);
}

void TileEditorDialog::buildLeftPanel(QHBoxLayout *mainLayout)
{
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    mainWidget->setLayout(layout);
    layout->setMargin(0);

    // Tile
    m_boxName = new QGroupBox("Tile", this);
    QVBoxLayout *boxNameLayout = new QVBoxLayout;
    m_boxName->setLayout(boxNameLayout);

    QLabel *labelName = new QLabel("Nom", this);
    m_name = new QLineEdit(this);
    boxNameLayout->addWidget(labelName);
    boxNameLayout->addWidget(m_name);

    // Cube
    m_boxCube = new QGroupBox("Cube", this);
    QVBoxLayout *boxCubeLayout = new QVBoxLayout;
    m_boxCube->setLayout(boxCubeLayout);

    m_inverserCadre = new QCheckBox("Inverser Cadre", this);
    connect(m_inverserCadre, SIGNAL(stateChanged(int)), this, SLOT(inverserCadre(int)));
    m_afficherCube = new QCheckBox("Afficher", this);
    connect(m_afficherCube, SIGNAL(stateChanged(int)), this, SLOT(afficherCube(int)));
    boxCubeLayout->addWidget(m_inverserCadre);
    boxCubeLayout->addWidget(m_afficherCube);

    // Frame
    m_boxFrame = new QGroupBox("Frame", this);
    QVBoxLayout *boxFrameLayout = new QVBoxLayout;
    m_boxFrame->setLayout(boxFrameLayout);

    // Frame->Axe Horizontal
    QHBoxLayout *axeHLayout = new QHBoxLayout;
    QLabel *axeHLabel = new QLabel("Axe Horizontal", this);
    axeHLabel->setMinimumWidth(LABEL_FRAME_WIDTH);
    axeHLabel->setMaximumWidth(LABEL_FRAME_WIDTH);
    axeHLabel->setAlignment(Qt::AlignHCenter);
    m_axeHorizontal = new QSpinBox(this);
    m_axeHorizontal->setMinimum(-10000);
    m_axeHorizontal->setMaximum(10000);
    connect(m_axeHorizontal, SIGNAL(valueChanged(int)), this, SLOT(axeHorizontalChanged(int)));
    m_axeHorizontal->setMinimumWidth(SPIN_FRAME_WIDTH-35);
    m_axeHorizontal->setMaximumWidth(SPIN_FRAME_WIDTH-35);
    m_axisxInitAll = new QPushButton(QIcon(":/icons/gear.png"),"", this);
    connect(m_axisxInitAll, SIGNAL(clicked()), this, SLOT(initAllAxisX()));

    axeHLayout->addWidget(axeHLabel, 0, Qt::AlignLeft);
    axeHLayout->addWidget(m_axeHorizontal, 0, Qt::AlignLeft);
    axeHLayout->addWidget(m_axisxInitAll, 0, Qt::AlignLeft);

    boxFrameLayout->addLayout(axeHLayout);

    // Frame->Axe Vertical
    QHBoxLayout *axeVLayout = new QHBoxLayout;
    QLabel *axeVLabel = new QLabel("Axe Vertical", this);
    axeVLabel->setMinimumWidth(LABEL_FRAME_WIDTH);
    axeVLabel->setMaximumWidth(LABEL_FRAME_WIDTH);
    axeVLabel->setAlignment(Qt::AlignHCenter);
    m_axeVertical = new QSpinBox(this);
    m_axeVertical->setMinimum(-10000);
    m_axeVertical->setMaximum(10000);
    connect(m_axeHorizontal, SIGNAL(valueChanged(int)), this, SLOT(axeVerticalChanged(int)));
    m_axeVertical->setMinimumWidth(SPIN_FRAME_WIDTH-35);
    m_axeVertical->setMaximumWidth(SPIN_FRAME_WIDTH-35);
    m_axisyInitAll = new QPushButton(QIcon(":/icons/gear.png"),"", this);
    connect(m_axisxInitAll, SIGNAL(clicked()), this, SLOT(initAllAxisX()));

    axeVLayout->addWidget(axeVLabel, 0, Qt::AlignLeft);
    axeVLayout->addWidget(m_axeVertical, 0, Qt::AlignLeft);
    axeVLayout->addWidget(m_axisyInitAll, 0, Qt::AlignLeft);

    boxFrameLayout->addLayout(axeVLayout);

    // Frame->Dimension Horizontal
    QHBoxLayout *dimHLayout = new QHBoxLayout;
    QLabel *dimHLabel = new QLabel("Dimension\nHorizontal", this);
    dimHLabel->setMinimumWidth(LABEL_FRAME_WIDTH);
    dimHLabel->setMaximumWidth(LABEL_FRAME_WIDTH);
    dimHLabel->setAlignment(Qt::AlignHCenter);
    m_dimensionHorizontal = new QDoubleSpinBox(this);
    m_dimensionHorizontal->setMinimum(0.5);
    m_dimensionHorizontal->setMaximum(1.5);
    m_dimensionHorizontal->setDecimals(2);
    m_dimensionHorizontal->setSingleStep(0.1);
    m_dimensionHorizontal->setValue(1);
    connect(m_dimensionHorizontal, SIGNAL(valueChanged(double)), this, SLOT(dimensionHorizontalChanged(double)));
    m_dimensionHorizontal->setMinimumWidth(SPIN_FRAME_WIDTH-35);
    m_dimensionHorizontal->setMaximumWidth(SPIN_FRAME_WIDTH-35);
    m_dimensionxInitAll = new QPushButton(QIcon(":/icons/gear.png"),"", this);
    connect(m_dimensionxInitAll, SIGNAL(clicked()), this, SLOT(initAllDimensionX()));

    dimHLayout->addWidget(dimHLabel, 0, Qt::AlignLeft);
    dimHLayout->addWidget(m_dimensionHorizontal, 0, Qt::AlignLeft);
    dimHLayout->addWidget(m_dimensionxInitAll, 0, Qt::AlignLeft);

    boxFrameLayout->addLayout(dimHLayout);

    // Frame->Dimension Vertical
    QHBoxLayout *dimVLayout = new QHBoxLayout;
    QLabel *dimVLabel = new QLabel("Dimension\nVertical", this);
    dimVLabel->setMinimumWidth(LABEL_FRAME_WIDTH);
    dimVLabel->setMaximumWidth(LABEL_FRAME_WIDTH);
    dimVLabel->setAlignment(Qt::AlignHCenter);
    m_dimensionVertical = new QDoubleSpinBox(this);
    m_dimensionVertical->setMinimum(0.5);
    m_dimensionVertical->setMaximum(1.5);
    m_dimensionVertical->setDecimals(2);
    m_dimensionVertical->setSingleStep(0.1);
    m_dimensionVertical->setValue(1);
    connect(m_dimensionVertical, SIGNAL(valueChanged(double)), this, SLOT(dimensionVerticalChanged(double)));
    m_dimensionVertical->setMinimumWidth(SPIN_FRAME_WIDTH-35);
    m_dimensionVertical->setMaximumWidth(SPIN_FRAME_WIDTH-35);
    m_dimensionyInitAll = new QPushButton(QIcon(":/icons/gear.png"),"", this);
    connect(m_dimensionyInitAll, SIGNAL(clicked()), this, SLOT(initAllDimensionY()));

    dimVLayout->addWidget(dimVLabel, 0, Qt::AlignLeft);
    dimVLayout->addWidget(m_dimensionVertical, 0, Qt::AlignLeft);
    dimVLayout->addWidget(m_dimensionyInitAll, 0, Qt::AlignLeft);

    boxFrameLayout->addLayout(dimVLayout);

    // Frame->Interval Frame
    QHBoxLayout *intervalFrameLayout = new QHBoxLayout;
    QLabel *intervalFrameLabel = new QLabel("Intervalle\nFrames (ms)", this);
    intervalFrameLabel->setMinimumWidth(LABEL_FRAME_WIDTH);
    intervalFrameLabel->setMaximumWidth(LABEL_FRAME_WIDTH);
    intervalFrameLabel->setAlignment(Qt::AlignHCenter);
    m_intervalFrames = new QSpinBox(this);
    m_intervalFrames->setMinimum(0);
    m_intervalFrames->setMaximum(99999999);
    m_intervalFrames->setValue(0);
    m_intervalFrames->setMinimumWidth(SPIN_FRAME_WIDTH-35);
    m_intervalFrames->setMaximumWidth(SPIN_FRAME_WIDTH-35);
    connect(m_intervalFrames, SIGNAL(valueChanged(int)), this, SLOT(intervalFrameChanged(int)));
    m_intervalInitAll = new QPushButton(QIcon(":/icons/gear.png"),"", this);
    connect(m_intervalInitAll, SIGNAL(clicked()), this, SLOT(initAllInterval()));

    intervalFrameLayout->addWidget(intervalFrameLabel, 0, Qt::AlignLeft);
    intervalFrameLayout->addWidget(m_intervalFrames, 0, Qt::AlignLeft);
    intervalFrameLayout->addWidget(m_intervalInitAll, 0, Qt::AlignLeft);

    boxFrameLayout->addLayout(intervalFrameLayout);

    // Frame->Interval Redemarrage
    QHBoxLayout *intervalRedemarrageLayout = new QHBoxLayout;
    QLabel *intervalRedemarrageLabel = new QLabel("Intervalle\nRedemarrage (ms)", this);
    intervalRedemarrageLabel->setMinimumWidth(LABEL_FRAME_WIDTH);
    intervalRedemarrageLabel->setMaximumWidth(LABEL_FRAME_WIDTH);
    intervalRedemarrageLabel->setAlignment(Qt::AlignHCenter);
    m_intervalRedemarrageCheckBox = new QCheckBox(this);
    connect(m_intervalRedemarrageCheckBox, SIGNAL(stateChanged(int)), this, SLOT(intervalRedemarrageCheckChanged(int)));
    m_intervalRedemarrageCheckBox->setChecked(true);
    intervalRedemarrageLayout->addWidget(intervalRedemarrageLabel, 0, Qt::AlignLeft);
    intervalRedemarrageLayout->addWidget(m_intervalRedemarrageCheckBox, 0, Qt::AlignLeft);

    boxFrameLayout->addLayout(intervalRedemarrageLayout);

    // Frame->Numero Frame
    QHBoxLayout *frameNumberLayout = new QHBoxLayout;
    m_numberFrame = new QLCDNumber(5, this);
    m_numberFrame->setDigitCount(5);
    m_numberFrame->display(1);
    m_numberFrame->setMinimumWidth(SPIN_FRAME_WIDTH+LABEL_FRAME_WIDTH);
    m_numberFrame->setMaximumWidth(SPIN_FRAME_WIDTH+LABEL_FRAME_WIDTH);

    frameNumberLayout->addWidget(m_numberFrame);

    boxFrameLayout->addLayout(frameNumberLayout);

    // Frame->Button Frame
    QHBoxLayout *frameButtonLayout = new QHBoxLayout;
    m_previousFrame = new QPushButton("<", this);
    m_previousFrame->setMinimumHeight(BUTTON_HEIGHT);
    m_previousFrame->setMaximumHeight(BUTTON_HEIGHT);
    connect(m_previousFrame, SIGNAL(clicked()), this, SLOT(previousFrame()));
    m_nextFrame = new QPushButton(">", this);
    m_nextFrame->setMinimumHeight(BUTTON_HEIGHT);
    m_nextFrame->setMaximumHeight(BUTTON_HEIGHT);
    connect(m_nextFrame, SIGNAL(clicked()), this, SLOT(nextFrame()));
    frameButtonLayout->addWidget(m_previousFrame);
    frameButtonLayout->addWidget(m_nextFrame);

    boxFrameLayout->addLayout(frameButtonLayout);

    m_renduButton = new QPushButton("Rendu", this);
    m_renduButton->setMinimumHeight(BUTTON_HEIGHT);
    m_renduButton->setMaximumHeight(BUTTON_HEIGHT);
    m_renduButton->setMinimumWidth(SPIN_FRAME_WIDTH+LABEL_FRAME_WIDTH);
    m_renduButton->setMaximumWidth(SPIN_FRAME_WIDTH+LABEL_FRAME_WIDTH);
    connect(m_renduButton, SIGNAL(clicked()), this, SLOT(render()));
    m_addButton = new QPushButton("Ajouter", this);
    m_addButton->setMinimumHeight(BUTTON_HEIGHT);
    m_addButton->setMaximumHeight(BUTTON_HEIGHT);
    m_addButton->setMinimumWidth(SPIN_FRAME_WIDTH+LABEL_FRAME_WIDTH);
    m_addButton->setMaximumWidth(SPIN_FRAME_WIDTH+LABEL_FRAME_WIDTH);
    connect(m_addButton, SIGNAL(clicked()), this, SLOT(addTile()));

    // Ajout de tout les layout/widget dans layout
    layout->addWidget(m_boxName, 0, Qt::AlignTop);
    layout->addWidget(m_boxCube, 0, Qt::AlignTop);
    layout->addWidget(m_boxFrame, 0, Qt::AlignTop);
    layout->addWidget(m_renduButton, 0, Qt::AlignTop | Qt::AlignCenter);
    layout->addWidget(m_addButton, 1, Qt::AlignTop | Qt::AlignCenter);

    mainLayout->addWidget(mainWidget, 1, Qt::AlignLeft);
}

void TileEditorDialog::buildRenderSFML(QVBoxLayout *mainLayout)
{
    QWidget *widget = new QWidget(this);
    widget->setMinimumSize(SFML_WIDTH,SFML_HEIGHT);
    QHBoxLayout *layout = new QHBoxLayout;
    widget->setLayout(layout);

    m_render = new Render(this, QPoint(0,0), QSize(SFML_WIDTH,SFML_HEIGHT));
    m_map = new MapManager();
    m_map->addLayer(-1, "X", true, true);
    m_map->addLayer(0, "Couche principal");

    m_mapRender = new MapRender(m_map, sf::Vector2i(SFML_WIDTH,SFML_HEIGHT));
    m_mapRender->setZoom(ZOOM_MAX);

    m_render->add(m_mapRender);
    m_mapRender->showGrid(false);

    layout->addWidget(m_render);
    mainLayout->addWidget(widget);

    newTile();
}

void TileEditorDialog::buildAnimation(QVBoxLayout *mainLayout)
{
    QHBoxLayout *layout = new QHBoxLayout;

    m_animationWidget = new QTreeView(this);
    m_animationWidget->header()->hide();
    connect(m_animationWidget, SIGNAL(pressed(QModelIndex)), this, SLOT(animationItemSelected(QModelIndex)));
    connect(m_animationWidget, SIGNAL(entered(QModelIndex)), this, SLOT(animationItemSelected(QModelIndex)));

    m_animationModel = new QStandardItemModel(this);
    m_animationWidget->setModel(m_animationModel);

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    m_newAnimationButton = new QPushButton(QIcon(":/icons/icon_animation.png"), "", this);
    connect(m_newAnimationButton, SIGNAL(clicked()), this, SLOT(newAnimation()));
    m_newTextureButton = new QPushButton(QIcon(":/icons/icon_texture.png"), "", this);
    connect(m_newTextureButton, SIGNAL(clicked()), this, SLOT(newTexture()));
    m_upFrame = new QPushButton(QIcon(":/icons/icon_up.png"), "", this);
    connect(m_upFrame, SIGNAL(clicked()), this, SLOT(upFrameAnimation()));
    m_downFrame = new QPushButton(QIcon(":/icons/icon_down.png"), "", this);
    connect(m_downFrame, SIGNAL(clicked()), this, SLOT(downFrameAnimation()));
    m_deleteFrame = new QPushButton(QIcon(":/icons/icon_delete.png"), "", this);
    connect(m_deleteFrame, SIGNAL(clicked()), this, SLOT(deleteFrameAnimation()));

    buttonLayout->addWidget(m_newAnimationButton);
    buttonLayout->addWidget(m_newTextureButton);
    buttonLayout->addWidget(m_upFrame);
    buttonLayout->addWidget(m_downFrame);
    buttonLayout->addWidget(m_deleteFrame);
    buttonLayout->addStretch();

    layout->addWidget(m_animationWidget);
    layout->addLayout(buttonLayout);
    layout->setAlignment(buttonLayout, Qt::AlignRight);

    mainLayout->addLayout(layout);
}

void TileEditorDialog::createAction()
{
    m_newTileAction = new QAction(QIcon(":/icons/icon_new_tile.png"), "Nouveau Tile", this);
    m_newTileAction->setShortcut(QKeySequence("Ctrl+N"));
    connect(m_newTileAction, SIGNAL(triggered()), this, SLOT(newTile()));

    m_modifTileAction = new QAction("Modifier Tile", this);
    m_modifTileAction->setShortcut(QKeySequence("Ctrl+M"));
    connect(m_modifTileAction, SIGNAL(triggered()), this, SLOT(modifTile()));

    m_newAnimationAction = new QAction(QIcon(":/icons/icon_animation.png"), "Nouvelle Animation", this);
    m_newAnimationAction->setShortcut(QKeySequence("Ctrl+A"));
    connect(m_newAnimationAction, SIGNAL(triggered()), this, SLOT(newAnimation()));
}

void TileEditorDialog::createMenu()
{
    m_fileMenu = menuBar()->addMenu("&Fichier");
    m_fileMenu->addAction(m_newTileAction);
    m_fileMenu->addAction(m_modifTileAction);
    m_fileMenu->addAction(m_newAnimationAction);
}

void TileEditorDialog::createToolBar()
{
    QToolBar *bar = addToolBar("Fichier");
    bar->addAction(m_newTileAction);
    bar->addAction(m_newAnimationAction);
}

/******************************************************************
 *                          SLOTS
 ******************************************************************/

void TileEditorDialog::keyPressEvent (QKeyEvent *event )
{
    event->accept();

    // Zoomer et Dezoomer
    if(event->key() == Qt::Key_Plus)
        m_mapRender->setZoom (m_mapRender->getZoom()+POSITIVE_ZOOM);
    if(event->key() == Qt::Key_Minus)
        m_mapRender->setZoom (m_mapRender->getZoom()+NEGATIVE_ZOOM);
}

void TileEditorDialog::wheelEvent(QWheelEvent *event)
{
    event->accept();
    if(event->delta() > -1)
        m_mapRender->setZoom (m_mapRender->getZoom()+POSITIVE_ZOOM);
    else
        m_mapRender->setZoom (m_mapRender->getZoom()+NEGATIVE_ZOOM);
}

void TileEditorDialog::newTile()
{
    m_currentFrame = 0;
    m_currentAnimation = DEFAULT_ANIMATION;

    if (m_tile != NULL && !m_added)
        TileManagerSingleton::getInstance()->remove(m_tile->getId());

    m_tile = TileManagerSingleton::getInstance()->create();
    m_tile->addAnimation(DEFAULT_ANIMATION);
    m_tileAnimationData = m_tile->getAnimation(m_currentAnimation);
    if(m_tileAnimationData != NULL)
        m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_currentFrame);

    m_map->createMap(sf::Vector2i(1,1));

    Container* container = m_map->getCell(0,0);
    if(container == NULL)
        return;

    m_cell = container->cell(0);
    if(m_cell == NULL)
    {
        m_cell = new Cell();
        container->addElement(0, m_cell);
    }

    m_cell->addEffect(EffectManagerSingleton::getInstance()->create(Effect::CUBE)->getId());

    m_animationModel->clear();

    m_added = false;

    populateAnimation();

    selectAnimationFrame(DEFAULT_ANIMATION);
}

void TileEditorDialog::modifTile()
{

}

bool TileEditorDialog::addAnimation(QString name)
{
    m_tileAnimationData = m_tile->addAnimation(name);

    if(m_tileAnimationData != NULL)
     {
        newTexture(name);
        return true;
     }

    return false;
}

void TileEditorDialog::newAnimation()
{
    if(m_tile == NULL)
        return;

    if(m_tile->getAnimations()->count() == 0)
    {
        addAnimation(DEFAULT_ANIMATION);
        return;
    }

    bool ok = false;
    QString newNameAnimation = "";


   do
       {
          if (newNameAnimation != "")
        QMessageBox::critical(this,"Operation impossible", "Une animation existe deja sous ce nom");

          ok = false;
        newNameAnimation = QInputDialog::getText(this, "Nom animation", "Nouvelle animation", QLineEdit::Normal, DEFAULT_ANIMATION, &ok);
        if(!ok)
            return;
       }
       while (newNameAnimation == "" || !addAnimation(newNameAnimation));

}

void TileEditorDialog::inverserCadre(int checkstate)
{
    if(checkstate)
        m_map->getLayerSystem()->moveUp(-1);
    else
        m_map->getLayerSystem()->moveDown(-1);
}

void TileEditorDialog::afficherCube(int checkstate)
{
    Container *container = m_map->getCell(0,0);
    if(container==NULL)
        return;
    container->data(-1)->setVisible(!checkstate);
    m_cell->setVisibleEffects(checkstate);
}

void TileEditorDialog::intervalFrameChanged(int value)
{
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setFrameInterval(value);
}

void TileEditorDialog::intervalRedemarrageCheckChanged(int checked)
{
    if (m_tileAnimationData == NULL)
        return;

    if (checked == Qt::Checked)
      m_tileAnimationData->setRestarting(true);

    else if (checked == Qt::Unchecked)
      m_tileAnimationData->setRestarting(false);
}

void TileEditorDialog::nextFrame()
{
    if(m_tileAnimationData ==NULL)
        return;

    if (m_numberFrame->value()+1 <= m_tileAnimationData->getNbFrame())
    {
        m_currentFrame += 1;
        m_numberFrame->display(m_currentFrame+1);
    }
    else
    {
        m_currentFrame = 0;
        m_numberFrame->display(1);
    }

    m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_currentFrame);
    if(m_tileAnimationFrameData == NULL)
        return;

    m_cell->setFrame(m_currentFrame);

    updateData();

    m_cell->update();
}

void TileEditorDialog::previousFrame()
{
    if(m_tileAnimationData ==NULL)
        return;

    if (m_numberFrame->value()-1 > 0)
    {
        m_currentFrame -= 1;
        m_numberFrame->display(m_numberFrame->value()-1);
    }

    else
    {
        m_currentFrame = m_tileAnimationData->getNbFrame()-1;
        m_numberFrame->display(m_currentFrame+1);
    }

    m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_currentFrame);
    if(m_tileAnimationFrameData == NULL)
        return;

    m_cell->setFrame(m_currentFrame);

    updateData();

    m_cell->update();
}

void TileEditorDialog::axeHorizontalChanged(int value)
{
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setPosition(sf::Vector2i(value, m_tileAnimationFrameData->getPosition().y));
    m_cell->update();
}

void TileEditorDialog::axeVerticalChanged(int value)
{
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setPosition(sf::Vector2i(m_tileAnimationFrameData->getPosition().x, value));
    m_cell->update();
}

void TileEditorDialog::dimensionHorizontalChanged(double value)
{
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setScale(sf::Vector2f(value, m_tileAnimationFrameData->getScale().y));
    m_cell->update();
}

void TileEditorDialog::dimensionVerticalChanged(double value)
{
    if(m_tileAnimationFrameData == NULL)
        return;

    m_tileAnimationFrameData->setScale(sf::Vector2f(m_tileAnimationFrameData->getScale().x, value));
    m_cell->update();
}

void TileEditorDialog::updateData()
{
    if(m_tileAnimationData== NULL || m_tileAnimationFrameData == NULL)
        return;
    m_axeHorizontal->setValue(m_tileAnimationFrameData->getPosition().x);
    m_axeVertical->setValue(m_tileAnimationFrameData->getPosition().y);
    m_dimensionHorizontal->setValue(m_tileAnimationFrameData->getScale().x);
    m_dimensionVertical->setValue(m_tileAnimationFrameData->getScale().y);
    m_intervalFrames->setValue(m_tileAnimationFrameData->getFrameInterval());
}

void TileEditorDialog::render()
{
    if(m_renduButton->text() == "Rendu")
    {
        m_boxName->setEnabled(false);
        m_boxCube->setEnabled(false);
        m_animationWidget->setEnabled(false);
        m_boxFrame->setEnabled(false);
        if (m_afficherCube->isChecked())
        {
            m_afficherCube->setChecked(false);
            afficherCube(0);
        }

        m_renduButton->setText("Stop");

        GameLayer* layer = m_map->getLayer(-1);
        if(layer == NULL)
        {
            qDebug() << __FILE__ << __LINE__ << ", Layer -1 n'existe pas.";
            return;
        }
        layer->setVisible(false);

        m_cell->setFrame(0);
        m_cell->startAnimation();
    }
    else
    {
        m_boxName->setEnabled(true);
        m_boxCube->setEnabled(true);
        m_animationWidget->setEnabled(true);
        m_boxFrame->setEnabled(true);
        m_renduButton->setText("Rendu");

        GameLayer* layer = m_map->getLayer(-1);
        if(layer == NULL)
            qDebug() << __FILE__ << __LINE__ << ", Layer -1 n'existe pas.";
        else
            layer->setVisible(true);

        m_cell->setFrame(m_currentAnimation, m_currentFrame);
    }
}

void TileEditorDialog::addTile()
{
    if (m_name->text() == "")
    {
        QMessageBox::critical(this, "Erreur", "Veuillez attribuer un nom a ce tile");
        m_name->setFocus();
        return;
    }

    m_added = true;
    m_tile->setName(m_name->text());
    emit tileAdded();
    close();
}

void TileEditorDialog::newTexture()
{   
    QModelIndexList indexes = m_animationWidget->selectionModel()->selectedIndexes();
    if(indexes.count() == 0 || indexes.count() > 1)
        return;

    QStandardItem *item = m_animationModel->itemFromIndex(indexes[0]);
    if(item == NULL)
        return;

    if(item->parent() != NULL)
        newTexture(item->parent()->text());
    else
        newTexture(item->text());
}

void TileEditorDialog::newTexture(QString animationName)
{
    TileAnimationData *tad = m_tile->getAnimation(animationName);
    if(tad != NULL)
    {
        QStringList paths = QFileDialog::getOpenFileNames(this,"Selectionez les images", "", IMAGE_FORMATS);

        if (paths.isEmpty())
            return;

        foreach(QString path, paths)
        {
            sf::Texture *texture = new sf::Texture();
            texture->loadFromFile(path.toStdString());

            TileAnimationFrameData *tafd = tad->addFrame(texture);
            if(tafd == NULL)
            {
                delete texture;
                return;
            }
        }
    }

    m_cell->setId(m_tile->getId(),false);
    m_cell->update();

    populateAnimation();
}

void TileEditorDialog::initAllInterval()
{
    if(m_tileAnimationData == NULL)
        return;

    int count = m_tileAnimationData->getNbFrame();
    for(int i = 0 ; i < count ; ++i)
    {
        TileAnimationFrameData *tafd = m_tileAnimationData->getFrame(i);
        if(tafd == NULL)
            continue;
        tafd->setFrameInterval(m_intervalFrames->value());
    }
    updateData();
}

void TileEditorDialog::initAllAxisX()
{

}

void TileEditorDialog::initAllAxisY()
{

}

void TileEditorDialog::initAllDimensionX()
{

}

void TileEditorDialog::initAllDimensionY()
{

}

void TileEditorDialog::animationItemSelected(const QModelIndex &index)
{
    QStandardItem *item = m_animationModel->itemFromIndex(index);
    if(item == NULL)
        return;
    if(item->parent() != NULL)
    {
        m_cell->setFrame(item->parent()->text(), item->data(Qt::UserRole).toInt());
        m_tileAnimationData = m_tile->getAnimation(item->parent()->text());
        m_tileAnimationFrameData = m_tileAnimationData->getFrame(item->data(Qt::UserRole).toInt());
        updateData();
        m_cell->update();
    }
    else
    {
        m_cell->setFrame(item->text(), 0);
        m_tileAnimationData = m_tile->getAnimation(item->text());
        m_tileAnimationFrameData = m_tileAnimationData->getFrame(0);
        updateData();
    }
}

void TileEditorDialog::populateAnimation()
{
    if(m_tile == NULL)
        return;

    m_animationModel->clear();

    const QHash<QString, TileAnimationData*>* animations = m_tile->getAnimations();
    foreach(TileAnimationData *tad, *animations)
    {
        QStandardItem *root = new QStandardItem(tad->name());
        m_animationModel->appendRow(root);

        const QList<TileAnimationFrameData*>* frames = tad->datas();
        foreach(TileAnimationFrameData *tafd, *frames)
        {
            QStandardItem *child = new QStandardItem(QString("Image n°%1").arg(tafd->getTimePosition()));
            root->appendRow(child);
            child->setData(tafd->getTimePosition(), Qt::UserRole);
            child->setData(tad->name(), Qt::UserRole+1);
        }
    }

    m_animationWidget->expandAll();
}

void TileEditorDialog::upFrameAnimation()
{
    QModelIndexList indexes = m_animationWidget->selectionModel()->selectedIndexes();
    if(indexes.size() == 0 || indexes.size() > 1)
        return;

    QStandardItem *item = m_animationModel->itemFromIndex(indexes[0]);
    if(item == NULL)
        return;

    int frame = item->data(Qt::UserRole).toInt();

    m_currentFrame = m_tileAnimationData->moveFrameToPrevious(frame);

    populateAnimation();

    selectCurrentAnimationFrame();
}

void TileEditorDialog::downFrameAnimation()
{
    QModelIndexList indexes = m_animationWidget->selectionModel()->selectedIndexes();
    if(indexes.size() == 0 || indexes.size() > 1)
        return;

    QStandardItem *item = m_animationModel->itemFromIndex(indexes[0]);
    if(item == NULL)
        return;

    int frame = item->data(Qt::UserRole).toInt();

    m_currentFrame = m_tileAnimationData->moveFrameToNext(frame);

    populateAnimation();

    selectCurrentAnimationFrame();
}

void TileEditorDialog::deleteFrameAnimation()
{
    QModelIndexList indexes = m_animationWidget->selectionModel()->selectedIndexes();
    if(indexes.size() == 0 || indexes.size() > 1)
        return;

    QStandardItem *item = m_animationModel->itemFromIndex(indexes[0]);
    if(item == NULL)
        return;

    int frame = item->data(Qt::UserRole).toInt();

    m_tileAnimationData->deleteFrame(frame);

    populateAnimation();

    m_currentFrame = 0;

    selectAnimationFrame(m_currentAnimation, 0);
}

void TileEditorDialog::selectCurrentAnimationFrameWithoutUpdate()
{
    m_animationWidget->blockSignals(true);
    selectAnimationFrame(m_currentAnimation, m_currentFrame);
    m_animationWidget->blockSignals(false);
}

void TileEditorDialog::selectCurrentAnimationFrame()
{
    selectAnimationFrame(m_currentAnimation, m_currentFrame);
}

void TileEditorDialog::selectAnimationFrameWithoutUpdate(QString animationName, int frame)
{
    m_animationWidget->blockSignals(true);
    selectAnimationFrame(animationName, frame);
    m_animationWidget->blockSignals(false);
}

void TileEditorDialog::selectAnimationFrame(QString animationName, int frame)
{
    int row = m_animationModel->rowCount();
    bool found = false;
    QModelIndex index;
    for(int i = 0 ; i < row ; ++i)
    {
        QStandardItem *item = m_animationModel->item(i);
        if(item == NULL)
            continue;

        if(item->text() == animationName)
        {
            int animationCount = item->rowCount();
            for(int j = 0 ; j < animationCount ; ++j)
            {
                QStandardItem *child = item->child(j);
                if(child == NULL)
                    continue;
                if(child->data(Qt::UserRole).toInt() == frame)
                {
                    index = m_animationModel->indexFromItem(child);
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                index = m_animationModel->indexFromItem(item);
                found =true;
            }
            break;
        }
    }

    if(found)
    {
        m_animationWidget->selectionModel()->select(index, QItemSelectionModel::Select);
        animationItemSelected(index);
    }
}
