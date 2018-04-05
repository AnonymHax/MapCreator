#ifndef COLLISION_H
#define COLLISION_H

#include "SYSTEM/Public.h"
#include "Cell.h"

class Collision : public sf::ConvexShape, public Graphic_Element
{
public:

    Collision(int x, int y);
    ~Collision() {}

    bool operator!= (const Collision &compare);

    void setCollision ();           // Defini l'inverse de l'etat de collision actuel
    void setCollision(const bool collision); // Defini si il y a collision

    bool isCollision () const;// Renvoie une bool confirmant ou non la collision sur cette cellule

    void showObject (sf::RenderTarget &render);
    void update();
    void updatePosition ();  // Place le sprite a sa position reelle par apport a sa position relative
    void updateTexture (); // Rassemble tous les updates

protected:

    bool m_collision;     // Indique si le personnage peut passer par dessus
};

#endif // COLLISION_H
