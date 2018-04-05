#ifndef ELEMENTCONTAINER_H
#define ELEMENTCONTAINER_H

#include "Collision.h"
#include "DirectionalLight.h"

class Container// Cette classe contient tous les types de tiles que contient une cellule
{
public:

    Container();
    ~Container();

    bool operator !=(const Container &compare);
    bool operator ==(const Container &compare);

    void update();

    void addElement(int layer_id, Graphic_Element *element); // Ne pas appeler ces fonctions manuellement si l'element est gere par MapManager
    Graphic_Element* remove(int layer_id);

    void setVPosition (const int &x, const int &y); // Defini la position relative de la case
    void setVPosition (const sf::Vector2i &position);
    void setHeight (const float &height);
    void setCollision (const bool &collision);

    sf::Vector2i getVPosition () const; //Renvoie la position relative de la case
    int getHeight() const;
    int getTop (const int &layer) const;
    bool isCollision () const;

    QList<Graphic_Element*> datas();
    Graphic_Element* data (int layer_id);

    Cell* cell(int layer_id);
    Light *light(int layer_id);

    bool exist (int layer_id) const;
    bool isEmpty () const;

protected:

    int m_height;
    bool m_collision;

    QMap<int, Graphic_Element*> m_data;

    sf::Vector2i m_position;
};


#endif // ELEMENTCONTAINER_H
