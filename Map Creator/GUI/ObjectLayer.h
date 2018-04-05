#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "SYSTEM/Public.h"
#include "ObjectContainer.h"

class ObjectLayer : public ObjectContainer
{
public:

    ObjectLayer(sf::Vector2i size);

    bool isMouseIn(const sf::Vector2i &position);
};

#endif // OBJECTLAYER_H
