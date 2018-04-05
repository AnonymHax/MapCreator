#ifndef UNMOVABLEITEM_H
#define UNMOVABLEITEM_H

#include "SYSTEM/Public.h"

class Unmovable_Item
{
public:

    Unmovable_Item();
    virtual ~Unmovable_Item() {}
    virtual void show(sf::RenderTarget &render) = 0;
};


#endif // UNMOVABLEITEM_H
