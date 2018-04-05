#ifndef ELEMENT_H
#define ELEMENT_H

#include "SYSTEM/Public.h"
#include "GUI/Movable_Item.h"

class Base_Graphic_Element : public Movable_Item
{
public:
    Base_Graphic_Element(const TYPE &type);

    virtual void setHeight (const int &height);
    virtual void setVPosition(const int &x, const int &y);
    virtual void setVPosition (const sf::Vector2i &position);
    virtual void setVisible (bool visible);

    TYPE getType () const;
    virtual sf::Vector2i getVPosition() const;
    virtual int getHeight() const;
    virtual bool isVisible () const;


protected:

    sf::Time getElapsedTime();
    void restartTimer();

    sf::Vector2i m_vposition;

    TYPE m_type; // Variable  informant la nature de l'element

    int m_height;

    bool m_visible;

    sf::Clock *m_clock;
};

class Effect;

class Graphic_Element : public Base_Graphic_Element
{
public:
    Graphic_Element(const TYPE &type);
    virtual ~Graphic_Element();

    void show(sf::RenderTarget &render);

    void setVisibleEffects (bool visible);

    void addEffect(ID id);
    void removeEffect(ID id);
    void updateEffect();


protected:  

    void showEffectBehind(sf::RenderTarget &render);
    void showEffectInfront(sf::RenderTarget &render);
    virtual void showObject (sf::RenderTarget &render) = 0;

    QList<Effect*> m_effects;
};

#endif // ELEMENT_H
