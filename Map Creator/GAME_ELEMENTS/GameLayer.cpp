#include "GameLayer.h"

/*************************************
        GAME LAYER
  ************************************/

GameLayer::GameLayer(ID id)
    : m_visible(true)
    , m_system(false)
    , m_id(id)
    , m_name("")
    , m_position(0)
    , m_deleteContent(true)
{
}

bool GameLayer::isVisible() const
{
    return m_visible;
}

bool GameLayer::isSystem() const
{
    return m_system;
}

ID GameLayer::getId() const
{
    return m_id;
}

QString GameLayer::getName() const
{
    return m_name;
}

int GameLayer::getPosition() const
{
    return m_position;
}

void GameLayer::setVisible(bool visible)
{
    m_visible = visible;
}

void GameLayer::setSystem(bool system)
{
    m_system = system;
}

void GameLayer::setId(int id)
{
    m_id = id;
}

void GameLayer::setName(QString name)
{
    m_name = name;
}

void GameLayer::setPosition(int position)
{
    m_position = position;
}

bool GameLayer::operator!=(const GameLayer &compare) const
{
    return m_id != compare.m_id || m_name != compare.m_name || m_visible != compare.m_visible || m_system != compare.m_system || m_position != compare.m_position;
}

bool GameLayer::canDeleteContent() const
{
    return m_deleteContent;
}

void GameLayer::setDeleteContent(bool b)
{
    m_deleteContent = b;
}

/*
bool GameLayer::operator<(const GameLayer &compare) const
{
    return m_position < compare.m_position;
}
*/
/*************************************
        GAME LAYER SYSTEM
  ************************************/

GameLayerSystem::GameLayerSystem()
    : m_layers()
    , m_order()
    , m_nextPosition(0)
{
}

GameLayerSystem::~GameLayerSystem()
{
    clear();
}

GameLayer* GameLayerSystem::add(ID id)
{
    GameLayer* layer = new GameLayer(id);
    layer->setPosition(m_nextPosition++);

    if(m_layers.insert(layer->getPosition(), layer) == m_layers.end())
    {
        delete layer;
        return NULL;
    }

    updateOrder();
    return layer;
}

GameLayer* GameLayerSystem::add(ID id, int position)
{
    GameLayer* layer = new GameLayer(id);
    layer->setPosition(position);

    int savePosition = m_nextPosition;
    if(m_nextPosition <= position)
        m_nextPosition = position+1;

    if(m_layers.insert(position, layer) == m_layers.end())
    {
        delete layer;
        m_nextPosition = savePosition;
        return NULL;
    }

    updateOrder();
    return layer;
}

bool GameLayerSystem::remove(ID id)
{
    QMap<int, GameLayer*>::iterator it = m_layers.begin();
    QMap<int, GameLayer*>::iterator itEnd = m_layers.end();
    for( ; it != itEnd ; ++it)
    {
        if(it.value()->getId() == id)
            break;
    }

    if(it == m_layers.end())
        return false;

    GameLayer* layer = it.value();

    int position = layer->getPosition();
    if(m_nextPosition-1 == position)
        m_nextPosition = position;

    m_layers.erase(it);
    delete layer;

    updateOrder();
    return true;
}

const QList<GameLayer*>* GameLayerSystem::getOrderLayer() const
{
    return &m_order;
}

void GameLayerSystem::moveDown(ID id)
{
    QMap<int, GameLayer*>::iterator it = m_layers.begin();
    QMap<int, GameLayer*>::iterator itEnd = m_layers.end();
    for( ; it != itEnd ; ++it)
    {
        if(it.value()->getId() == id)
            break;
    }

    if(it == m_layers.end()) // Si on ne la pas trouvé
        return;

    GameLayer* source = it.value();
    int positionSource = source->getPosition();

    if(it == m_layers.begin()) // Si c'est le premier, il n'y en a pas avant
        return;

    QMap<int, GameLayer*>::iterator itDestination = --it;
    ++it;
    GameLayer *destination = itDestination.value();

    m_layers.erase(itDestination);
    m_layers.erase(it);

    int positionDestination = destination->getPosition();
    destination->setPosition(positionSource);
    source->setPosition(positionDestination);

    m_layers.insert(source->getPosition(), source);
    m_layers.insert(destination->getPosition(), destination);

    updateOrder();
}

void GameLayerSystem::moveUp(ID id)
{

    QMap<int, GameLayer*>::iterator it = m_layers.begin();
    QMap<int, GameLayer*>::iterator itEnd = m_layers.end();
    for( ; it != itEnd ; ++it)
    {
        if(it.value()->getId() == id)
            break;
    }

    if(it == m_layers.end()) // Si on ne l'a pas trouvé
        return;

    GameLayer* source = it.value();
    int positionSource = source->getPosition();

    ++it;
    if(it == m_layers.end()) // Si c'est le dernier il n'y en a pas après
        return;

    QMap<int, GameLayer*>::iterator itDestination = it;
    --it;
    GameLayer *destination = itDestination.value();

    m_layers.erase(it);
    m_layers.erase(itDestination);

    int positionDestination = destination->getPosition();
    destination->setPosition(positionSource);
    source->setPosition(positionDestination);

    m_layers.insert(source->getPosition(), source);
    m_layers.insert(destination->getPosition() ,destination);

    updateOrder();
}

void GameLayerSystem::updateOrder()
{
    m_order.clear();

    QMap<int, GameLayer*>::const_iterator temp = m_layers.constBegin();
    while (temp != m_layers.constEnd())
    {
        m_order<< temp.value();
        temp++;
    }
/*
    QMap<int, GameLayer*>::const_iterator temp = m_layers.constEnd();
    do
    {
        temp--;
        m_order<< temp.value();

    } while( temp != m_layers.constBegin());
    */
}

void GameLayerSystem::clear()
{
    foreach(GameLayer* gl, m_layers)
        delete gl;
    m_layers.clear();
    m_order.clear();
}

const QMap<int, GameLayer*>* GameLayerSystem::getLayers() const
{
    return &m_layers;
}

int GameLayerSystem::size() const
{
    return m_layers.size();
}

GameLayer* GameLayerSystem::getLayer(ID id)
{
    QMap<int, GameLayer*>::iterator it = m_layers.begin();
    QMap<int, GameLayer*>::iterator itEnd = m_layers.end();
    for( ; it != itEnd ; ++it)
    {
        if(it.value()->getId() == id)
            break;
    }

    if(it == m_layers.end())
        return NULL;
    return it.value();
}

const GameLayer* GameLayerSystem::getLayer(ID id) const
{
    QMap<int, GameLayer*>::const_iterator it = m_layers.begin();
    QMap<int, GameLayer*>::const_iterator itEnd = m_layers.end();
    for( ; it != itEnd ; ++it)
    {
        if(it.value()->getId() == id)
            break;
    }

    if(it == m_layers.end())
        return NULL;
    return it.value();
}
