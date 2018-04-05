#ifndef MOVABLE_ITEM_H
#define MOVABLE_ITEM_H

#include "SYSTEM/Public.h"
#include "UnmovableItem.h"

class Movable_Item : public Unmovable_Item
{
public:

    Movable_Item();
    virtual ~Movable_Item() {}
    virtual void updatePosition() = 0;
};


#endif // MOVABLE_ITEM_H
