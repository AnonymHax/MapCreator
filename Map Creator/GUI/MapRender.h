#ifndef MAIN_H
#define MAIN_H

#include "SYSTEM/Public.h"
#include "QSFMLCanvas.h"
#include "MANAGERS/MapManager.h"
#include "FPS.h"
#include "GAME_ELEMENTS/DirectionalLight.h"

#define MAP_MARGE 10

class MapRender : public QObject, public Object
{

    Q_OBJECT

public :

    MapRender(MapManager* mapManager, sf::Vector2i render_size);

    void show (sf::RenderTarget &render);
    void updatePosition();

    void resetView (); // Remet a zero les information de la vue dynamique

    bool setZoom (const float &zoom);   // Modifie le zoom de la vue principale
    bool setZoom (const float &zoom, const unsigned int &time); // Modifie le zoom dans un intervalle de temps (ms)

    bool setViewPosition (const sf::Vector2f &position);    // Bouge la vue renvoie une bool pour confirmer
    bool setViewPosition(const sf::Vector2f &position, const unsigned int &time);

    bool setViewVPosition (const sf::Vector2i &position); //(VPosition pour position relative)
    bool setViewVPosition(const sf::Vector2i &position, const unsigned int &time); // Deplace la vue dans un intervalle de temps (ms)


    float getZoom () const;

    sf::Vector2f getViewPosition () const;
    sf::Vector2i getViewVPosition () const;

    sf::Vector2i mouseToTileCoords (const float & x, const float & y) const; // Renvoie sur quel tile est la souris
    sf::Vector2i mouseToTileCoords (const sf::Vector2f & mouseCoords) const;
    sf::Vector2i mouseToTileCoords (const sf::Vector2i & mouseCoords) const;

    sf::Vector2f mouseToViewCoords (const sf::Vector2i &point) const; // Convertie des coordones de la souris en coords dans le moteur

    sf::Vector2i viewCoordsToTileCoords(const sf::Vector2i &coords) const;

    void updateScrollBox(); // Met à jour les tiles à afficher pour economiser les performances
    void addToScrollBox(const sf::Vector2i &cell);  // Rajoute une cellule a afficher dans la scrollbox
    void removeFromScrollBox (const sf::Vector2i &cell); // Enleve une cellule a afficher dans la scrollbox

    QList <sf::Vector2i> hitList (sf::Vector2f  const & point, int layer_id, unsigned short int const alpha = 0); // Renvoi la liste tiles sur lequel la souris pointe
    bool hitTest (const sf::Sprite *sprite, sf::Vector2f const & point, unsigned short int const alpha = 0); // Verifie si les Coordsonnées de la souris sont un tile

    const QList<sf::Vector2i>& getDrawnGrid (); // Renvoi le tableau contenant les coords des cellules a afficher

    void showGrid (const bool show); // Active/Desactive la grille

    bool leftMousePressed (const sf::Vector2i &position);
    bool rightMousePressed (const sf::Vector2i &position);
    bool mouseMoved(const sf::Vector2i &position);

signals:

    void mousePressEvent(MOUSE button, sf::Vector2i position);
    void mouseMoveEvent (sf::Vector2i position);

private:

    // Fonctions permettant le bon fonctionnement du MapRender (interne)
    void updateView();
    void updateZoom();
    void updateScrollBoxF();

protected:

    MapManager *m_mapManager; // Carte source

    sf::Vector2f m_viewPosition;  // Contient la valeur de combien la vue a bouger sur l'axe vertical/horizontal

    QList<sf::Vector2i>* m_drawnGrid; // Contient toutes les positions de cellules a afficher
    bool m_updateGrid;

    sf::View m_view;
    bool m_updateView; // Variables utulisés pour la fonction setViewPosition (x, time)
    sf::Vector2f m_viewDestination;
    sf::Vector2f m_viewOriginalPosition;
    unsigned int m_viewTime;
    unsigned int m_viewElapsedTime;
    sf::Clock m_viewTimer;

    float m_zoom;  // Contient le coefficient du zoom actuel
    bool m_updateZoom; // Variables utulisés pour la fonction setZoom (x, time)
    float m_zoomDestination;
    float m_zoomOriginal;
    unsigned int m_zoomTime;
    unsigned int m_zoomElapsedTime;
    sf::Clock m_zoomTimer;

    sf::ConvexShape m_gridCell; // Defini la forme des cellules de la grille
    sf::Vector2f m_compensation;
    bool m_showGrid;

    QList<Light*> m_toDrawLights;
    QList<Wall> m_lightWalls;
    sf::RenderTexture m_lightTexture;
};

#endif // MAIN_H
