#ifndef GAME_H
#define GAME_H

#include "SYSTEM/Public.h"
#include "GUI/Render.h"

class BaseEngine : public QWidget
{
    Q_OBJECT

public:

    BaseEngine(QWidget* Parent, const QPoint& Position, const QSize& Size);
    ~BaseEngine();

    MapManager* getManager ();
    MapRender* getRender ();

    void updateSelector ();

    void setTileChoice (int id); // Defini le tile choisi
    void selection ();  // Execute l'action choisi sur la case ou est le selecteur
    void setTool (TOOL tool); // Defini l'outil choisi

    void tool_place (); // Outil qui s'occupe de placer les tiles
    void tool_delete (); // Outil qui s'occupe de supprimer les tiles
    void tool_collision(); // Outil qui permet d'ajuster les collisions graphiquement
    void tool_height (); // Outil qui permet de donner du relief au terrain
    void tool_light (); // Outil qui permet de placer les lumières
    void tool_move (); // Outil qui permet de se deplacer grace a la souris

    void resetEngine (); // Utulisé pour remettre a zero la vue, lors de la creation d'une nouvelle carte

    void saveBackwardCell (const Container *cell, bool clear_forward = true);
    void saveForwardCell (const Container *cell);

    Container getLastCell () const;
    Selector& getSelector ();


public slots:

    void mouseClicking (MOUSE mouse_button, sf::Vector2i position);
    void mouseMoving (sf::Vector2i mouse_pos);
    virtual void wheelEvent(QWheelEvent * event); // Utulisé pour zoomer

    void setLight (int radius, int quality, int intensity, QColor color, float opening_angle, float angle);

    void loadLastCell ();
    void loadNextCell ();

    void winContextMenu(QPoint position);

    void setLayerFocus (int layer_id);

signals:
    void mapMoved();

private:

    int m_layerFocus;
    int m_tileId;
    int m_tool;

    QMenu *m_contextMenu;

    QList <sf::Vector2i> m_lastSelected;
    sf::Mouse m_mouse; // Contient les infos sur la souris : position, boutons, etc...

    sf::Vector2i m_lastMouseVPosition; // Contient la derniere tile sur laquelle la souris est passée
    sf::Vector2i m_lastCollision;

    sf::Color m_lightColor;
    int m_lightRadius;
    int m_lightQuality;
    float m_lightAngle;
    int m_lightIntensity;
    float m_lightOpeningAngle;

    sf::Vector2i m_mousePosition;
    sf::Vector2i m_mouseMove;
    float m_actualMouseHeight; // Variables appartenant à l'outil gerant la hauteur
    int m_begMouseHeight;
    bool m_isLocked;
    sf::Vector2i m_lockedCell;

    QList<Cell> m_backwardCells;
    QList<Cell> m_forwardCells;

    MapManager *m_map;

    MapRender *m_mapRender;    // Rendeurs
    ObjectLayer *m_guiRender;

    Render *m_render; // Widgets
    FPS *m_fps;
    MapGlobal *m_global;

    Selector *m_selector;
};

#endif // GAME_H
