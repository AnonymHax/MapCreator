#include "TileAnimationData.h"
#include "SYSTEM/Public.h"

/************************************************************
 *              TILE ANIMATION FRAME DATA
 ************************************************************/

TileAnimationFrameData::TileAnimationFrameData(int frameInterval, sf::Texture *texture, const sf::Vector2i &position, const sf::Vector2f &scale)
    : m_timePosition(-1)
    , m_frameInterval(frameInterval)
    , m_texture(texture)
    , m_position(position)
    , m_scale(scale)
{
}

TileAnimationFrameData::~TileAnimationFrameData()
{
    delete m_texture;
}

int TileAnimationFrameData::getTimePosition() const
{
    return m_timePosition;
}

void TileAnimationFrameData::setTimePosition(int time)
{
    m_timePosition = time;
}

void TileAnimationFrameData::increaseTimePosition()
{
    m_timePosition++;
}

void TileAnimationFrameData::decreaseTimePosition()
{
    m_timePosition--;
}

int TileAnimationFrameData::getFrameInterval() const
{
    return m_frameInterval;
}

const sf::Texture* TileAnimationFrameData::getTexture() const
{
    return m_texture;
}

sf::Vector2i TileAnimationFrameData::getPosition() const
{
    return m_position;
}

sf::Vector2f TileAnimationFrameData::getScale() const
{
    return m_scale;
}

void TileAnimationFrameData::setFrameInterval(int frameInterval)
{
    if(frameInterval < 5)
        return ;

    m_frameInterval = frameInterval;
}

void TileAnimationFrameData::setTexture(sf::Texture *texture)
{
    m_texture = texture;
}

void TileAnimationFrameData::setPosition(sf::Vector2i position)
{
    m_position = position;
}

void TileAnimationFrameData::setScale(sf::Vector2f scale)
{
    m_scale = scale;
}


/************************************************************
 *              TILE ANIMATION DATA
 ************************************************************/

TileAnimationData::TileAnimationData(QString name)
    : m_name(name)
    , m_restart(true)
    , m_datas()
{
}

TileAnimationData::~TileAnimationData()
{
    clear();
}

void TileAnimationData::clear()
{
    foreach(TileAnimationFrameData* f, m_datas)
        delete f;

    m_datas.clear();
    m_name = "";
}

void TileAnimationData::setName(QString name)
{
    m_name = name;
}

QString TileAnimationData::name() const
{
    return m_name;
}

void TileAnimationData::setRestarting(bool restart)
{
    m_restart = restart;
}

bool TileAnimationData::isRestarting() const
{
    return m_restart;
}

TileAnimationFrameData* TileAnimationData::addFrame(sf::Texture* texture)
{
    TileAnimationFrameData *data = new TileAnimationFrameData();
    data->setTexture(texture);

    TileAnimationFrameData* last = 0;
    if(!m_datas.isEmpty())
        last = m_datas.back();
    int timePosition = 0;
    if(last != 0)
        timePosition = last->getTimePosition()+1;

    m_datas.append(data);
    data->setTimePosition(timePosition);

    return data;
}

QList<TileAnimationFrameData*>::iterator TileAnimationData::getIterator(int numberFrame)
{
    QList<TileAnimationFrameData*>::iterator it = m_datas.begin();
    QList<TileAnimationFrameData*>::iterator itEnd = m_datas.end();
    for( ; it != itEnd ; ++it)
    {
        if((*it)->getTimePosition() == numberFrame)
            return it;
    }
    return itEnd;
}

bool TileAnimationData::insertFrameAfter(int numberFrame, TileAnimationFrameData *data)
{
    QList<TileAnimationFrameData*>::iterator it = getIterator(numberFrame);
    QList<TileAnimationFrameData*>::iterator itEnd = m_datas.end();
    if(it == itEnd)
        return false;

    // on se place sur l'it suivant
    ++it;
    if(it == itEnd)
        return false;

    int timePosition = (*it)->getTimePosition();

    QList<TileAnimationFrameData*>::iterator tmp = it;
    for( ; tmp != itEnd ; ++it)
        (*tmp)->increaseTimePosition();

    m_datas.insert(it, data);
    data->setTimePosition(timePosition);

    return true;
}

bool TileAnimationData::insertFrameBefore(int numberFrame, TileAnimationFrameData *data)
{
    QList<TileAnimationFrameData*>::iterator it = getIterator(numberFrame);
    QList<TileAnimationFrameData*>::iterator itEnd = m_datas.end();
    if(it == itEnd)
        return false;

    int timePosition = (*it)->getTimePosition();

    QList<TileAnimationFrameData*>::iterator tmp = it;
    for( ; tmp != itEnd ; ++it)
        (*tmp)->increaseTimePosition();

    m_datas.insert(it, data);
    data->setTimePosition(timePosition);

    return true;
}

int TileAnimationData::moveFrameToNext(int numberFrame)
{
    int sourceIndex = getIndex(numberFrame);
    if(sourceIndex < 0)
        return numberFrame;
    TileAnimationFrameData *source = m_datas[sourceIndex];
    if(sourceIndex+1 == m_datas.size())
        return numberFrame;

    TileAnimationFrameData *destination = m_datas[sourceIndex+1];

    int timePositionSource = source->getTimePosition();
    int timePositionDestination = destination->getTimePosition();

    source->setTimePosition(timePositionDestination);
    destination->setTimePosition(timePositionSource);

    m_datas[sourceIndex] = destination;
    m_datas[sourceIndex+1] = source;

    return source->getTimePosition();
}

int TileAnimationData::moveFrameToPrevious(int numberFrame)
{
    int sourceIndex = getIndex(numberFrame);
    if(sourceIndex < 0)
        return numberFrame;
    TileAnimationFrameData *source = m_datas[sourceIndex];
    if(sourceIndex-1 < 0)
        return numberFrame;

    TileAnimationFrameData *destination = m_datas[sourceIndex-1];

    int timePositionSource = source->getTimePosition();
    int timePositionDestination = destination->getTimePosition();

    source->setTimePosition(timePositionDestination);
    destination->setTimePosition(timePositionSource);

    m_datas[sourceIndex] = destination;
    m_datas[sourceIndex-1] = source;

    return source->getTimePosition();
}

bool TileAnimationData::deleteFrame(int numberFrame)
{
    QList<TileAnimationFrameData*>::iterator it = getIterator(numberFrame);
    QList<TileAnimationFrameData*>::iterator itEnd = m_datas.end();
    if(it == itEnd)
        return false;

    QList<TileAnimationFrameData*>::iterator tmp = it;
    for( ; tmp != itEnd ; ++tmp)
        (*tmp)->decreaseTimePosition();

    delete *it;

    m_datas.erase(it);
    return true;
}

int TileAnimationData::getIndex(int numberFrame)
{
    for( int i = 0   ; i < m_datas.size() ; ++i)
        if(m_datas[i]->getTimePosition() == numberFrame)
            return i;
    return -1;
}

const QList<TileAnimationFrameData*>* TileAnimationData::datas() const
{
    return &m_datas;
}

QList<TileAnimationFrameData*>* TileAnimationData::datas()
{
    return &m_datas;
}

TileAnimationFrameData* TileAnimationData::getFrame(int numberFrame)
{
    TileAnimationFrameData* tafd = NULL;
    if(numberFrame < m_datas.size())
    {
        tafd = m_datas[numberFrame];
        assert(numberFrame == tafd->getTimePosition());
    }
    return tafd;
}

const TileAnimationFrameData* TileAnimationData::getFrame(int numberFrame) const
{
    TileAnimationFrameData* tafd = NULL;
    if(numberFrame < m_datas.size())
    {
        tafd = m_datas[numberFrame];
        assert(numberFrame == tafd->getTimePosition());
    }
    return tafd;
}

int TileAnimationData::getNbFrame() const
{
    return m_datas.size();
}
