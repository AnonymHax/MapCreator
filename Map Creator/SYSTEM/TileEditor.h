#ifndef TILEEDITOR_H
#define TILEEDITOR_H

#include "SYSTEM/Public.h"
#include "SYSTEM/BaseEngine.h"
#include "GAME_ELEMENTS/Tile.h"
#include "GAME_ELEMENTS/Cube.h"


namespace Ui {
    class TileEditor;
}

/*
  La classe TileEditor, permet de rajouter des tiles, celle-ci est basé sur la classe Interface. C'est pour cela que certaines fonctions, sont
  un peu bricolées, mais malgré cela, l'editeur fonctionne.
  */

class TileEditor : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit TileEditor(BaseEngine *engine, QWidget *parent);
    ~TileEditor();

    bool loadTiles (QString animation_name, QStringList textures_paths);     // Charge les tiles dans la memoire (appartient normalement à la classe MapManager)

private slots:

  void keyPressEvent ( QKeyEvent * event ); // Se declenche si le fleches sont utulisés
//void wheelEvent(QWheelEvent * event);
  void on_tile_secondFloor_valueChanged(int secondFloor);
  void on_tile_secondSide_valueChanged (int secondSide);
  void on_tile_add_clicked ();
  void on_tile_scalex_valueChanged (double x);
  void on_tile_scaley_valueChanged (double y);
  void on_frame_previous_clicked ();
  void on_frame_next_clicked ();
  void on_tile_play_clicked ();
  void on_frame_interval_valueChanged (int frameInterval);
  void on_frame_restart_valueChanged (int frameRestart);
  void on_check_restart_stateChanged (int checked);
  virtual void wheelEvent(QWheelEvent * event);
  void on_newTile_triggered();
  void on_newAnimation_triggered();

  void itemSelected (const QModelIndex &index);

  void resetUi ();
  void disableUi ();
  void activateUi ();
  void addAnimation (const QString &name, const QStringList &paths = QStringList());
  void setAnimName (QString name);
  void animationConfirm ();

  void on_cube_show_clicked();
  void on_cube_inverse_clicked();

signals:

    void tileAdded ();

private:

  Ui::TileEditor *ui;
  Tile* m_tile;
  sf::Vector2i m_mapSize;       // La carte a une taille de 1

  int m_currentFrame;
  QString m_currentAnimation;

  TileAnimationData *m_tileAnimationData;
  TileAnimationFrameData *m_tileAnimationFrameData;

  QString m_tileName;

  MapRender *m_mapRender;            // Pointeur sur la classe Base Engine
  MapManager *m_map;
  Render *m_render;

  BaseEngine *m_actualEngine;

  QStringList m_toAddPaths;
  QString m_toAddName;
  QStandardItemModel *m_animationsModel;

  //Cube *m_cube;
  bool m_added;
};

#endif // TILEEDITOR_H
