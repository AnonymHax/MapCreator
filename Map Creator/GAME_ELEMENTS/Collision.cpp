#include "Collision.h"

Collision::Collision(int x, int y)
    : Graphic_Element(SYSTEM)
    , m_collision(false)
{
    m_vposition.x = x;
    m_vposition.y = y;

    setPointCount(4);
    setPoint(0, sf::Vector2f (CELL_SIZE_X/2, 0));
    setPoint(1, sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2));
    setPoint(2,sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y));
    setPoint(3,sf::Vector2f(0, CELL_SIZE_Y/2));
    setOutlineThickness(2);

    updateTexture();
    updatePosition();
}

void Collision::setCollision(bool collision)
{
    m_collision = collision;
    updateTexture();
}

void Collision::setCollision ()
{
    if (m_collision)
        m_collision = false;

    else
        m_collision = true;

    updateTexture();
}

bool Collision::isCollision() const
{
    return m_collision;
}

void Collision::update()
{
    updatePosition();
    updateTexture();
}

void Collision::updateTexture()
{
    if (m_collision)
    {
        setOutlineColor(sf::Color(255,40,30,255));
        setFillColor(sf::Color(255,40,30,110));
    }
    else
    {
        setOutlineColor(sf::Color(5,85,255,255));
        setFillColor(sf::Color(5,85,255,110));
    }
}

void Collision::updatePosition ()
{
    int RELATIVE_X = getVPosition().x;
    int RELATIVE_Y = getVPosition().y;

    setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x, toScreenCoords(RELATIVE_X, RELATIVE_Y).y + m_height);
}

void Collision::showObject (sf::RenderTarget &render)
{
    if (m_visible)
        render.draw(*this);
}

bool Collision::operator!= (const Collision &compare)
{
    if (m_vposition != compare.getVPosition())
        return true;

    if (m_collision != compare.isCollision())
        return true;

    if (m_height != compare.getHeight())
        return true;

    return false;
}
