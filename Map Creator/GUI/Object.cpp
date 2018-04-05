#include "ObjectContainer.h"

int Object::m_nbObjects = 0;

Object::Object(sf::Vector2i size)
    : Movable_Item()
    , m_id(++m_nbObjects)
    , m_position(0,0)
    , m_size(size)
    , m_visible(true)
    , m_enabled(true)
    , m_parent(NULL)
    , m_mouseHover(false)
    , m_mouseLeftDown(false)
    , m_mouseRightDown(false)
    , m_focused(false)
    , m_container(false)
    , m_draggable(false)
    , m_sprite()
    , m_texture()
    , m_backgroundColor(sf::Color::Transparent)
    , m_clock(NULL)
{
    updatePosition();
    updateSize();
}

Object::~Object()
{
    if (m_parent != NULL)
        m_parent->remove(this);

    delete m_clock;
    m_clock = NULL;
}

sf::Vector2i Object::getPosition() const
{
    return m_position;
}

sf::Vector2i Object::getGlobalPosition() const
{
    if (m_parent != NULL)
        return m_position+m_parent->getGlobalPosition();
    else
        return m_position;
}

sf::Vector2i Object::getSize() const
{
    return m_size;
}

int Object::getId() const
{
    return m_id;
}

void Object::setToFront(bool front)
{
    if (m_parent != NULL)
    {
        m_parent->setToFront(this, front);
    }
}

void Object::setSize(const sf::Vector2i &size)
{
    m_size = size;
    updateSize();
}

void Object::setParent(ObjectContainer *parent)
{
    if (m_parent != NULL && parent != NULL)
        parent->add(this);

    else
        m_parent = NULL;
}

void Object::setPosition(const sf::Vector2i &position)
{
    m_position = position;
    updatePosition();
}

void Object::setFocus(bool focus)
{
    if (m_parent != NULL)
    { if (focus)
            m_parent->setFocus(this, true);

        else
            m_parent->unfocusAll(); }
}

void Object::setVisible(bool visible)
{
    m_visible = visible;
}

void Object::setEnabled(bool enable)
{
    m_enabled = enable;

    if (!m_enabled)
    {
        // Change the mouse button state.
        m_mouseHover = false;
        m_mouseLeftDown = false;
        m_mouseRightDown = false;

        // If the object is focused then it must be unfocused
        if (m_parent != NULL)
            m_parent->setFocus(this, false);
    }
}

void Object::setBackgroundColor(const sf::Color &color)
{
    m_backgroundColor=color;
}

sf::Color Object::getBackgroundColor() const
{
    return m_backgroundColor;
}

void Object::updatePosition()
{
    m_sprite.setPosition(sf::Vector2f(m_position));
}

void Object::updateSize()
{
    m_texture.create(m_size.x, m_size.y);
}

bool Object::isMouseIn (const sf::Vector2i &position)
{
    if (getGlobalPosition().x <= position.x &&
            getGlobalPosition().x +getSize().x >= position.x &&
            getGlobalPosition().y <= position.y &&
            getGlobalPosition().y +getSize().y >= position.y)
        return true;

    else
        return false;
}

bool Object::mouseMoved(const sf::Vector2i &position)
{return true;}

bool Object::leftMousePressed (const sf::Vector2i &position)
{return true;}

bool Object::rightMousePressed (const sf::Vector2i &position)
{return true;}

bool Object::leftMouseReleased (const sf::Vector2i &position)
{return true;}

bool Object::rightMouseReleased (const sf::Vector2i &position)
{return true;}

bool Object::wheelMouseMoved (const int &delta)
{return true;}

bool Object::keyPressed (const sf::Keyboard::Key &key)
{return true;}

bool Object::textEntered(const sf::Uint32 &key)
{return true;}

void Object::setFocused(const bool &focused)
{
    if (m_parent != NULL)
        m_parent->setFocus(this, focused);
}

sf::Time Object::getElapsedTime()

{
    if (m_clock == NULL)
        m_clock = new sf::Clock;

    return m_clock->getElapsedTime();
}

void Object::restartTimer()

{
    if (m_clock == NULL)
        m_clock = new sf::Clock;

    m_clock->restart();
}

void Object::mouseLeftNoLongerDown()
{}
void Object::mouseRightNoLongerDown()
{}
void Object::mouseNoLongerOnObjet()
{}
