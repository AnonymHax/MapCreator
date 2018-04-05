#include "TileManager.h"

TileManager::TileManager()
{

}

Tile *TileManager::createObjet(ID id)
{
    return new Tile(id);
}
