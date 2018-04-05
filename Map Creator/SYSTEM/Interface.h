#ifndef INTERFACE_H
#define INTERFACE_H

#include "Public.h"
#include "BaseEngine.h"
#include "GAME_ELEMENTS/Tile.h"
#include "TileEditor.h"
#include "assert.h"

namespace Ui {
class Interface;
}

class Interface : public QMainWindow
{

    Q_OBJECT
    
public:

    explicit Interface(QWidget *parent = 0);
    ~Interface();           // Destructeur

    void keyPressEvent ( QKeyEvent * event ); // Se declenche si le fleches sont utulisés

private:
    void populateLayerModel();

private slots:

    void showTiles ();  // Affiche les tiles dans les onglets
    void openTile (QModelIndex index);

    void on_version_triggered ();    // Fonctions appelés quand le bouton leur appartenant est cliqué
    void on_createMap_triggered ();
    void on_saveMap_triggered ();
    void on_loadMap_triggered ();
    void on_sendMap_triggered ();

    void on_addTile_triggered ();
    void on_loadTiles_triggered ();
    void on_saveTiles_triggered ();
    void on_deleteTiles_triggered ();
    void deleteTile (int id);
    void deleteTile_disconnect();

    void on_VBar_valueChanged(int value);
    void on_HBar_valueChanged(int value);

    void on_tool_delete_clicked (bool checked);
    void on_tool_place_clicked (bool checked);
    void on_tool_collision_clicked (bool checked);
    void on_tool_height_clicked (bool checked);
    void on_tool_light_clicked(bool checked);
    void on_tool_move_clicked(bool checked);

    void on_tool_place_clicked();
    void on_tool_delete_clicked();
    void on_tool_height_clicked();
    void on_tool_light_clicked();
    void on_tool_collision_clicked();
    void on_tool_move_clicked();

    void setMapSizeX (int x);
    void setMapSizeY (int y);

    void setMapName (QString name);

    void newMap ();          // Creer un objet de classe "Graphism" et appelle sa fonction heritée pour creer une nouvelle carte
    void tileSelected (int id); // Cherche et defini quel tiles ont été choisi dans le menu
    void tileSelected (const QModelIndex &tile);
    void sendLightParameters ();
    void update_Light_Color ();

    void status_bar_position (sf::Vector2i position);

    void on_save_asMap_triggered();
    void on_save_asTiles_triggered();

    void on_getBack_triggered();
    void on_getForward_triggered();

    void on_enableGrid_triggered();
    void on_zoomIn_triggered();
    void on_zoomOut_triggered();
    void on_goto_cell_triggered();

    void setDestinationX (int x);
    void setDestinationY (int y);
    void goToCell();

    void on_tab_selector_currentChanged(int index);

    void on_layer_add_clicked();
    void on_layer_delete_clicked();
    void on_layer_up_clicked();
    void on_layer_down_clicked();

    void layerSelected (const QModelIndex &index);

    void closeEvent(QCloseEvent *);
    void ItemLayerChanged(QStandardItem*);

    void mapMoved();

signals:

    void tileSelection (int id);

private:

    sf::Vector2i m_mapSize;
    sf::Vector2i m_destinationCell;

    Ui::Interface *ui;
    //QMap< int, Tile*> *m_tiles;
    BaseEngine *m_engine;            // Pointeur sur la classe Base Engine
    TileEditor *m_editor;

    int m_lastChoice;

    QColor m_lightColor;

    QString m_mapPath;
    QString m_tilesPath;
    QString m_mapName;

    QLabel m_statusPosition;

    // Modeles servant a gerer les layers
    QStandardItemModel *m_layersModel;
    QItemSelectionModel *m_slayersModel; // Modele de selection (clic)

    // Modele permettant de choisir les fichiers tiles
    QFileSystemModel *m_filesModel;
    QStandardItemModel *m_tilesModel;
};

#endif // INTERFACE_H
