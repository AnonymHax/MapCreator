#include "Cell.h"
#include "MANAGERS/TileManager.h"

Cell::Cell()
    : sf::Sprite()
    , Graphic_Element(CELL)
    , m_id(-1)
    , m_current_frame(-1)
    , m_frame_interval(NO_ANIMATION)
    , m_current_animation("")
    , m_tile(NULL)
    , m_tileAnimationData(NULL)
    , m_tileAnimationFrameData(NULL)
{
}

Cell::Cell (int x, int y)
    : sf::Sprite()
    , Graphic_Element(CELL)
    , m_id(-1)
    , m_current_frame(-1)
    , m_frame_interval(NO_ANIMATION)
    , m_current_animation("")
    , m_tile(NULL)
    , m_tileAnimationData(NULL)
    , m_tileAnimationFrameData(NULL)
{
    m_vposition = sf::Vector2i(x,y);
}

Cell::~Cell()
{
}

void Cell::setId (const int &id, bool start_animation)
{
    m_id = id;
    m_current_frame = 0;

    m_tile = TileManagerSingleton::getInstance()->get(id);

    if(m_tile == NULL)
        return;

    if (id != -1)
    {
        m_current_animation = m_tile->getDefaultAnim();
        m_tileAnimationData = m_tile->getAnimation(m_current_animation);
        if(m_tileAnimationData != NULL)
            m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_current_frame);
    }

    if (start_animation)
        startAnimation();

    else if (!start_animation && m_frame_interval != -1)
        startAnimation();

    update ();
}

int Cell::getId () const
{
    return m_id;
}

void Cell::setInfos (const int &x, const int &y, const int &id)
{
    m_vposition.x = x;
    m_vposition.y = y;
    m_id = id;
    m_current_frame = 0;

    update ();
}

void Cell::showObject(sf::RenderTarget &render)
{
    if (m_frame_interval != NO_ANIMATION && getElapsedTime().asMilliseconds() >= m_frame_interval)
    {
        int temp = (getElapsedTime().asMilliseconds())/m_frame_interval;
        if (temp >= 1)
            temp --;

        nextFrame(temp);
        restartTimer();
    }

    if (m_visible)
        render.draw(*this);
}

void Cell::updateTexture ()
{
    if(m_tileAnimationFrameData == NULL)
        return;

    const sf::Texture *texture = m_tileAnimationFrameData->getTexture();
    setTexture(*texture,true);
}

void Cell::updatePosition ()
{
    float DIFFERENCE_Y;
    float DIFFERENCE_X;

    int RELATIVE_X = getVPosition().x;
    int RELATIVE_Y = getVPosition().y;

    int size_y = getTextureRect().height;
    int size_x = getTextureRect().width;

    if(m_tileAnimationFrameData == NULL)
        return;

    sf::Vector2i positionTile = m_tileAnimationFrameData->getPosition();
    sf::Vector2f scaleTile = m_tileAnimationFrameData->getScale();

    if (size_y >= CELL_SIZE_Y)
        DIFFERENCE_Y = (CELL_SIZE_Y - size_y)  + positionTile.y + (size_y - size_y*scaleTile.y);
    else
        DIFFERENCE_Y = 0-((size_y -CELL_SIZE_Y)/2)  + positionTile.y + (size_y - size_y*scaleTile.y);

    DIFFERENCE_X = -((size_x -CELL_SIZE_X)/2) + positionTile.x+ (size_x - (size_x*scaleTile.x))/2;

    setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x+ DIFFERENCE_X, toScreenCoords(RELATIVE_X, RELATIVE_Y).y + DIFFERENCE_Y + m_height);
}

void Cell::update ()
{
    updateScale ();
    updateTexture ();
    updatePosition();
    updateEffect();
}

void Cell::setTransparent()
{
    setColor(sf::Color(255, 255, 255, DEFAULT_TRANSPARENCY));
}

void Cell::setOpaque()
{
    setColor(sf::Color(255, 255, 255, 255));
}

void Cell::updateScale()
{
    setScale(m_tileAnimationFrameData->getScale());
}

void Cell::nextFrame (int jump)
{

    if(m_tile == NULL || m_tileAnimationData == NULL || m_tileAnimationFrameData == NULL)
        return;

    if (m_current_frame + 2 + jump <= m_tileAnimationData->getNbFrame())
    {
        m_current_frame+=jump+1;
        m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_current_frame);
        m_frame_interval = m_tileAnimationFrameData->getFrameInterval();
    }

    else
    {
        if (m_tileAnimationData->isRestarting())
        {
            m_current_frame = 0;
            m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_current_frame);
            m_frame_interval = m_tileAnimationFrameData->getFrameInterval();
        }

        else
        {
            m_current_frame = m_tileAnimationData->getNbFrame()-1;
            m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_current_frame);
            m_frame_interval = NO_ANIMATION;
        }

        m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_current_frame);

    }

    update();
}

bool Cell::setFrame(int frame, bool stop_animation)
{
    if(m_tile == NULL)
        return false;

    if(m_tileAnimationData == NULL)
        return false;

    if (frame <= m_tileAnimationData->getNbFrame() && frame > -1)
    {
        if (stop_animation)
            stopAnimation();

        m_current_frame = frame;
        m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_current_frame);

        restartTimer();

        update();

        return true;
    }

    return false;
}

bool Cell::setFrame (QString animation, int frame, bool stop_animation)
{
    if(m_tile == NULL)
        return false;

    m_current_animation = animation;

    m_tileAnimationData = m_tile->getAnimation(m_current_animation);
    if(m_tileAnimationData == NULL)
        return false;

    if (frame <= m_tileAnimationData->getNbFrame() && frame > -1 && m_tile->contains(animation))
    {
        if (stop_animation)
            stopAnimation();

        m_current_frame = frame;

        if(m_tileAnimationData != NULL)
            m_tileAnimationFrameData = m_tileAnimationData->getFrame(m_current_frame);

        update();

        return true;
    }

    return false;
}

void Cell::setAnimation(QString animation, bool start_animation)
{
    if(m_tile == NULL)
        return;

    if (m_tile->contains(animation))
    {
        m_current_frame = 0;
        m_current_animation = animation;

        m_tileAnimationData = m_tile->getAnimation(animation);
        m_tileAnimationFrameData = m_tileAnimationData->getFrame(0);

        if (start_animation)
            startAnimation();

        else if (!start_animation && m_frame_interval != NO_ANIMATION)
            startAnimation();

        update();
    }
    else
        qDebug()<<"ERREUR: L'animation demandé n'existe pas";
}

void Cell::startAnimation ()
{
    if(m_tileAnimationFrameData == NULL || m_tileAnimationData == NULL)
        return;

    if (m_tileAnimationData->getNbFrame() > 1)
    {
        restartTimer();
        m_frame_interval = (m_tileAnimationFrameData->getFrameInterval());
    }

    else
        m_frame_interval = NO_ANIMATION;
}

void Cell::stopAnimation ()
{
    m_frame_interval = NO_ANIMATION;
}

bool Cell::operator !=(const Cell &compare)
{
    if (compare.m_vposition == m_vposition &&
            compare.m_id == m_id &&
            compare.m_height == m_height)
        return false;

    return true;
}

bool Cell::operator ==(const Cell &compare)
{
    return !(*this != compare);
}

const QString &Cell::getCurrentAnim() const
{
    return m_current_animation;
}

int Cell::getCurrentFrame () const
{
    return m_current_frame;
}

const Tile* Cell::tile () const
{
    return m_tile;
}
