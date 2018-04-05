#include "ObjectLayer.h"

ObjectLayer::ObjectLayer(sf::Vector2i size) : ObjectContainer (size)
{
}

bool ObjectLayer::isMouseIn(const sf::Vector2i &position)
{    
    for (int i=0; i<m_childs.size(); ++i)
    {
        if (m_childs[i]->isMouseIn(position))
            return true;

        // Si l'objet avait la souris precedemment, il l'en est informé
        else if (m_childs[i]->m_mouseHover)
        {
            m_childs[i]->m_mouseHover = false;
            m_childs[i]->mouseNoLongerOnObjet();
        }
    }

    return false;
}
