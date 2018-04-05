#ifndef CUBE_H
#define CUBE_H

#include "Cell.h"
#include "Effect.h"

class Cube : public Effect
{
    friend class EffectManager;
protected:
    Cube(ID id);

    virtual void showEffectBehind(sf::RenderTarget &render);
    virtual void showEffectInfront(sf::RenderTarget &render);

    virtual void assignElement(const Graphic_Element *element);

    virtual void updateParameters();

    void setHeight(const int &height);

private:
    void updatePosition();

private:
    sf::ConvexShape m_top;
    sf::ConvexShape m_bottom;
    sf::RectangleShape m_line1;
    sf::RectangleShape m_line2;
    sf::RectangleShape m_line3;
    sf::RectangleShape m_line4;

    int m_floor;
    int m_side;
    sf::Vector2f m_size;
    float m_height2;
    const Cell *m_cell;
};


#endif // CUBE_H
