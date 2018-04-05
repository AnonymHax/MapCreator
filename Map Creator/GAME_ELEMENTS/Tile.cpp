#include "Tile.h"

Tile::Tile(int id)
    : m_id(id)
    , m_name("")
    , m_defaultAnimation(DEFAULT_ANIMATION)
{
}

Tile::~Tile()
{
    foreach(TileAnimationData* tad , m_animations)
        delete tad;
    m_animations.clear();
}


void Tile::setName (QString name)
{
    m_name = name;
}

int Tile::getId () const
{
    return m_id;
}

QString Tile::getName() const
{
    return m_name;
}

int Tile::getNbFrames (const QString &animation) const
{
    TileAnimationData * tad = NULL;
    if(animation != "")
        tad = m_animations.value(animation);
    else
        tad = m_animations.value(m_defaultAnimation);

    if(tad == NULL)
        return 0;

    return tad->getNbFrame();
}

int Tile::getNbAnimation() const
{
    return m_animations.count();
}

bool Tile::contains(const QString &animation) const
{
    return m_animations.contains(animation);
}

QStringList Tile::getAnimNames () const
{
    QStringList names;

    foreach(QString s, m_animations.keys())
        names << s;

    return names;
}

void Tile::setDefaultAnim(QString animation)
{
    if (m_animations.contains(animation))
        m_defaultAnimation = animation;
}

QString Tile::getDefaultAnim() const
{
    return m_defaultAnimation;
}

TileAnimationData* Tile::addAnimation(QString name)
{
    TileAnimationData* tileAnim = new TileAnimationData(name);
    if(m_animations.contains(name))
        return NULL;

    m_animations.insert(name, tileAnim);
    return tileAnim;
}

const TileAnimationData* Tile::getAnimation(QString name) const
{
    if(m_animations.contains(name))
        return m_animations.value(name);
    return NULL;
}

TileAnimationData* Tile::getAnimation(QString name)
{
    if(m_animations.contains(name))
        return m_animations.value(name);
    return NULL;
}

const TileAnimationFrameData* Tile::getAnimationFrame(QString name, int frame) const
{
    const TileAnimationData *tad = getAnimation(name);
    if(tad != NULL)
        return tad->getFrame(frame);
    return NULL;
}

TileAnimationFrameData* Tile::getAnimationFrame(QString name, int frame)
{
    TileAnimationData *tad = getAnimation(name);
    if(tad != NULL)
        return tad->getFrame(frame);
    return NULL;
}

const QHash<QString, TileAnimationData*>* Tile::getAnimations()const
{
    return &m_animations;
}

QHash<QString, TileAnimationData*>* Tile::getAnimations()
{
    return &m_animations;
}
