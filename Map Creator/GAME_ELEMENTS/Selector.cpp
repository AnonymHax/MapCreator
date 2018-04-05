#include "Selector.h"

Selector::Selector()
    : QObject()
    , sf::ConvexShape()
    , Graphic_Element(SYSTEM)
{
    setPointCount(4);
    setPoint(0, sf::Vector2f (CELL_SIZE_X/2, 0));
    setPoint(1, sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2));
    setPoint(2,sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y));
    setPoint(3,sf::Vector2f(0, CELL_SIZE_Y/2));
    setOutlineThickness(2);
    setOutlineColor(sf::Color(175,0,255,255));
    setFillColor(sf::Color(175,0,255,110));
}

void Selector::setVPosition (const Container *reference)
{
    if(reference == NULL)
        return;
    m_height = reference->getHeight();
    m_vposition = reference->getVPosition();

    updatePosition ();
}


void Selector::setVPosition (sf::Vector2i position)
{
    m_vposition = position;
    m_height = 0;

    updatePosition();
}

void Selector::updatePosition()
{
    setPosition(toScreenCoords(m_vposition).x, toScreenCoords(m_vposition).y + m_height);
    emit selectorMoved(m_vposition);
}

void Selector::showObject (sf::RenderTarget &render)
{
    if (m_visible)
        render.draw(*this);
}
