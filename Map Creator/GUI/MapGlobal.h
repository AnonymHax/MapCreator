#ifndef MAPGLOBAL_H
#define MAPGLOBAL_H

#include "SYSTEM/Public.h"
#include "MANAGERS/MapManager.h"
#include "MapRender.h"

#define CELLS_RENDERED 100 // Nombre de cellules dessine par boucle apres avoir depassé le UPDATE_TIME (ms)
#define UPDATE_TIME 10

class MapGlobal : public Object
{
public:

    MapGlobal(MapManager *manager, sf::Vector2i size = sf::Vector2i (200,100));

    void setDynamic (bool choice); // Active ou non la transparence lorsque la souris passe

    void show(sf::RenderTarget &target);

    bool leftMousePressed(const sf::Vector2i &position);
    bool mouseMoved(const sf::Vector2i &position);
    void mouseNoLongerOnObjet();

private:

    MapManager *m_manager;

    QList<sf::RenderTexture*> m_overview;

    sf::View m_view;

    sf::Vector2i m_cellNb;

    bool m_rendered;
    bool m_switch;

    int m_transparency;
    bool m_dynamic; // Active ou non la transparence quand la souris passe
};

#endif // MAPGLOBAL_H
