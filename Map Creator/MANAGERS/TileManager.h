#ifndef TILEMANAGER_HPP
#define TILEMANAGER_HPP

#include "SYSTEM/Manager.h"
#include "GAME_ELEMENTS/Tile.h"
#include "SYSTEM/Singleton.h"

class TileManager : public Manager<Tile>
{
public:
    TileManager();

protected:
    virtual Tile *createObjet(ID id);
};

class TileManagerSingleton : public CSingleton<TileManager>
{

};

#endif // TILEMANAGER_HPP
