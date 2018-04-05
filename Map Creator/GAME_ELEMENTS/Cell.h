#ifndef CELL_H
#define CELL_H

#include "SYSTEM/Public.h"
#include "GAME_ELEMENTS/Tile.h"
#include "Element.h"



class Cell : public sf::Sprite, public Graphic_Element // Classe abstraite
{
public:

    Cell ();              // Constructeur par défaut
    Cell(int x, int y); // Constructeur secondaire

    ~Cell();

    bool operator== (const Cell &compare);
    bool operator!= (const Cell &compare);

    void setId (const int &id, bool start_animation = true); // Defini le type d'objet auquel apartient la case
    void setInfos (const int &x, const int &y, const int &type);  // Defini la position relative et le type
    bool setFrame (int frame, bool stop_animation = true);
    bool setFrame (QString animation, int frame, bool stop_animation = true);
    void setAnimation (QString animation, bool start_animation = true);
    void setTransparent (); // Rend le sprite transparent
    void setOpaque ();  // Rend le sprite opaque

    int getId() const;//Renvoie le type d'objet que est la case en un chiffre
    const QString &getCurrentAnim () const;
    int getCurrentFrame () const;

    void showObject (sf::RenderTarget &render);
    void updateTexture (); // Defini l'image au sprite par apport a son type (numero)
    void updatePosition ();  // Place le sprite a sa position reelle par apport a sa position relative
    void updateScale (); // Redimensionne le sprite dans sa taille correcte
    void update (); // Rassemble tous les updates

    void stopAnimation ();
    void startAnimation ();

    const Tile *tile() const;

private :

     void nextFrame (int jump = 0);

protected:

    int m_id; // Indique le type de l'objet (ex: Chaise) par un numero representant l'objet
    int m_current_frame;
    int m_frame_interval;
    QString m_current_animation;
    Tile *m_tile;

    TileAnimationData *m_tileAnimationData;
    TileAnimationFrameData *m_tileAnimationFrameData;
};

#endif // CELL_H
