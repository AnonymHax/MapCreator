#include "Effect.h"

#include "Cube.h"

/*************************************
 *              EFFET
 *************************************/

Effect::Effect(ID id)
    : Base_Graphic_Element(SYSTEM)
    , m_id(id)
    , m_element(NULL)
    , m_stateShow(BEHIND)
{
    setVisible(false);
}

ID Effect::getId() const
{
    return m_id;
}

void Effect::assignElement(const Graphic_Element *element)
{
    m_element = element;
    updateParameters();
}

void Effect::show(sf::RenderTarget &render)
{
    if(m_visible)
    {
        if(m_stateShow == Effect::INFRONT)
            showEffectInfront(render);
        else if(m_stateShow == Effect::BEHIND)
            showEffectBehind(render);
    }
}

void Effect::setShowState(EffectShow state)
{
    m_stateShow = state;
}

/*************************************
 *          EFFECT MANAGER
 *************************************/

Effect* EffectManager::createObjet(ID id, int type)
{
    if(type >= Effect::SIZE_EFFECT_FORM)
        return NULL;

    switch(type)
    {
    case Effect::CUBE:
        return new Cube(id);
        break;
    }

    return NULL;
}
