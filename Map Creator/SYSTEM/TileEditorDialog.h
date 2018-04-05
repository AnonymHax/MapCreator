#ifndef TILEEDITORDIALOG_HPP
#define TILEEDITORDIALOG_HPP

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QLineEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QLCDNumber>
#include <QTreeView>
#include <QStandardItemModel>

#include "GUI/QSFMLCanvas.h"
#include "GUI/Render.h"
#include "GUI/MapRender.h"
#include "MANAGERS/MapManager.h"
#include "GAME_ELEMENTS/Tile.h"
#include "SYSTEM/Public.h"

class QHBoxLayout;
class QGroupBox;

class TileEditorDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit TileEditorDialog(QWidget *parent = 0);
    ~TileEditorDialog();

private:
    void buildGUI();
    void buildLeftPanel(QHBoxLayout *layout);
    void buildRenderSFML(QVBoxLayout *layout);
    void buildAnimation(QVBoxLayout *layout);
    void createAction();
    void createMenu();
    void createToolBar();
    void updateData();
    void populateAnimation();
    void selectCurrentAnimationFrameWithoutUpdate();
    void selectCurrentAnimationFrame();
    void selectAnimationFrameWithoutUpdate(QString animationName, int frame = 0);
    void selectAnimationFrame(QString animationName, int frame = 0);
    bool addAnimation(QString name);

signals:
    void tileAdded ();

private slots:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

    void newTile();
    void modifTile();
    void newAnimation();
    void inverserCadre(int);
    void afficherCube(int);
    void intervalRedemarrageCheckChanged(int);
    void intervalFrameChanged(int);
    void nextFrame();
    void previousFrame();
    void render();
    void addTile();
    void axeHorizontalChanged(int);
    void axeVerticalChanged(int);
    void dimensionHorizontalChanged(double);
    void dimensionVerticalChanged(double);
    void newTexture();
    void newTexture(QString animationName);
    void initAllInterval();
    void initAllAxisX();
    void initAllAxisY();
    void initAllDimensionX();
    void initAllDimensionY();
    void animationItemSelected(const QModelIndex &index);
    void upFrameAnimation();
    void downFrameAnimation();
    void deleteFrameAnimation();

private:
    QMenu* m_fileMenu;

    QAction *m_newTileAction;
    QAction *m_newAnimationAction;
    QAction *m_modifTileAction;
    QAction *m_addTextureAction;

    QGroupBox *m_boxName;
    QGroupBox *m_boxCube;
    QGroupBox *m_boxFrame;

    QLineEdit *m_name;
    QCheckBox *m_inverserCadre;
    QCheckBox *m_afficherCube;

    QSpinBox *m_axeHorizontal;
    QPushButton *m_axisxInitAll;
    QSpinBox *m_axeVertical;
    QPushButton *m_axisyInitAll;
    QDoubleSpinBox *m_dimensionHorizontal;
    QPushButton *m_dimensionxInitAll;
    QDoubleSpinBox *m_dimensionVertical;
    QPushButton *m_dimensionyInitAll;
    QSpinBox *m_intervalFrames;
    QPushButton *m_intervalInitAll;
    QCheckBox *m_intervalRedemarrageCheckBox;
    QLCDNumber *m_numberFrame;
    QPushButton *m_previousFrame;
    QPushButton *m_nextFrame;

    QPushButton *m_renduButton;
    QPushButton *m_addButton;

    Render *m_render;
    MapRender *m_mapRender;            // Pointeur sur la classe Base Engine
    MapManager *m_map;

    Tile *m_tile;

    int m_currentFrame;
    QString m_currentAnimation;
    QString m_tileName;

    QTreeView *m_animationWidget;
    QStandardItemModel *m_animationModel;

    TileAnimationData *m_tileAnimationData;
    TileAnimationFrameData *m_tileAnimationFrameData;

    QPushButton *m_newAnimationButton;
    QPushButton *m_newTextureButton;
    QPushButton *m_upFrame;
    QPushButton *m_downFrame;
    QPushButton *m_deleteFrame;

    Cell *m_cell;

    bool m_added;
};

#endif // TILEEDITORDIALOG_HPP
