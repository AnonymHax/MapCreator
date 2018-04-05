#ifndef MAP_MANAGER_H
#define MAP_MANAGER_H

#include "SYSTEM/Public.h"
#include "GAME_ELEMENTS/Selector.h"
#include "GAME_ELEMENTS/Tile.h"
#include "GAME_ELEMENTS/GameLayer.h"
#include <iostream>
#include <algorithm>

class MapManager
{

public:

    MapManager (); // Constructeur
    ~MapManager (); // Destructeur pour liberer le tableau de tiles

    void setName (const QString &name); // Defini/Recupere le nom de la carte
    QString getName () const;

    void createMap (const sf::Vector2i &map_size);
    void deleteMap ();

    bool exist (const int &x, const int &y) const; // Verifie si les coordonnes existent
    bool exist (const sf::Vector2i &position) const;

    bool inProportions (const int &x, const int &y) const; // Verifie si les coordonnes se situe dans la carte
    bool inProportions (const sf::Vector2i &position) const;

    bool saveMap(const QString &path); // Sauvegarde la carte actuel
    bool loadMap (const QString &path); // Charge une carte

    bool loadTiles (const QString &file_path, const bool clear_tiles = false);
    bool saveTiles (const QString &file_path);

    bool removeTile(const int &id);

    bool mapExist () const; // Renvoi une booleen confirmant si ou non une carte existe dans la memoire actuellement
    sf::Vector2i mapSize() const; // Renvoi la taille maximale de la carte

    void addCell (int x, int y); // Ajoute une cellule si elle n'existe pas et l'initialise
    void addCell (const sf::Vector2i &position);

    void removeCell (int x, int y); // Supprime une cellule, si elle existe
    void removeCell (const sf::Vector2i &position);

    void removeCell(int x, int y, int layer_id, bool free_space = true);
    void removeCell(const sf::Vector2i &position, int layer_id, bool free_space = true);

    const QList<GameLayer*>* getLayersOrder() const;

    GameLayer* getLayer(ID layer_id);

    GameLayer* addLayer(ID id);
    GameLayer* addLayer(ID id, QString name, bool visible = true, bool system = false);
    GameLayerSystem* getLayerSystem();

    bool removeLayer(ID id);
    void removeAllLayers ();

    // Renvoi une reference à la cellule demandé,
    // iniatialise la cellule si elle n'existe pas par défaut
    Container* getCell (int x, int y,  bool initialize = true);
    Container* getCell (const sf::Vector2i &position, bool initialize = true);

    sf::Vector2i getSize() const { return m_mapSize; }

protected:

    sf::Vector2i m_mapSize;  // Contient les dimensions de la carte

    GameLayerSystem m_layers;

    bool m_mapExist;  // Booleen qui sert a liberer la memoire, si une nouvelle carte est crée par dessus
    //QMap < int, QMap < int, Container > > m_map; // Classe map qui contient tous les tiles de cartes
    QMap<sf::Vector2i, Container*> m_map;

    QString m_mapName;
};

#endif // MAP_H
