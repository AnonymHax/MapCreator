#include "Element.h"
#include "Effect.h"

/*
 *Base_Graphic_Element
 */

Base_Graphic_Element::Base_Graphic_Element(const TYPE &type)
    : Movable_Item()
    , m_vposition(0,0)
    , m_type(type)
    , m_height(0)
    , m_visible(true)
    , m_clock(NULL)
{
}


void Base_Graphic_Element::setHeight(const int &height)
{
    m_height = height;

    updatePosition();
}

void Base_Graphic_Element::setVPosition(const int &x, const int &y)
{
    setVPosition(sf::Vector2i(x,y));
}

void Base_Graphic_Element::setVPosition(const sf::Vector2i &position)
{
   m_vposition = position;

   updatePosition();
}

TYPE Base_Graphic_Element::getType () const
{
    return m_type;
}

sf::Vector2i Base_Graphic_Element::getVPosition() const
{
    return m_vposition;
}

int Base_Graphic_Element::getHeight() const
{
    return m_height;
}

bool Base_Graphic_Element::isVisible() const
{
    return m_visible;
}

void Base_Graphic_Element::setVisible(bool visible)
{
    m_visible = visible;
}

sf::Time Base_Graphic_Element::getElapsedTime()

{
    if (m_clock == NULL)
        m_clock = new sf::Clock;

    return m_clock->getElapsedTime();
}

void Base_Graphic_Element::restartTimer()

{
    if (m_clock == NULL)
        m_clock = new sf::Clock;

    m_clock->restart();
}


/* ---------------------------------------------------------------------------------------------------
 *  Graphic_Element
 */

Graphic_Element::Graphic_Element(const TYPE &type) : Base_Graphic_Element(type)
 {}

Graphic_Element::~Graphic_Element()
{
    if (m_clock != NULL)
        delete m_clock;

    QListIterator<Effect*> it(m_effects);
    while(it.hasNext())
    {
        Effect *effect = it.next();
        if(effect == NULL)
            continue;
        EffectManagerSingleton::getInstance()->remove(effect->getId());
    }
    m_effects.clear();
}

void Graphic_Element::show(sf::RenderTarget &render)
{
    showEffectBehind(render);
    showObject(render);
    showEffectInfront(render);
}

void Graphic_Element::showEffectBehind(sf::RenderTarget &render)
{
    QListIterator<Effect*> it(m_effects);
    while(it.hasNext())
    {
        Effect* effect = it.next();
        effect->setShowState(Effect::BEHIND);
        effect->show(render);
    }
}

void Graphic_Element::showEffectInfront(sf::RenderTarget &render)
{
    QListIterator<Effect*> it(m_effects);
    while(it.hasNext())
    {
        Effect* effect = it.next();
        effect->setShowState(Effect::INFRONT);
        effect->show(render);
    }
}

void Graphic_Element::setVisibleEffects(bool visible)
{
        QListIterator<Effect*> it(m_effects);
        while(it.hasNext())
        {
            it.next()->setVisible(visible);
        }
}

void Graphic_Element::addEffect(ID id)
{
    Effect *effect = EffectManagerSingleton::getInstance()->get(id);
    if(effect == NULL)
        return;

    effect->assignElement(this);
    m_effects<<effect;
}

void Graphic_Element::removeEffect(ID id)
{
    QList<Effect*>::iterator it = m_effects.begin();
    QList<Effect*>::iterator itEnd = m_effects.end();
    for( ; it != itEnd ; ++it)
    {
        if((*it)->getId() == id)
        {
            m_effects.erase(it);
            EffectManagerSingleton::getInstance()->remove(id);
            return;
        }
    }
}

void Graphic_Element::updateEffect()
{
    QListIterator<Effect*> it(m_effects);
    while(it.hasNext())
    {
        it.next()->updateParameters();
    }
}
