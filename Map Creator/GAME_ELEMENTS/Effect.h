#ifndef EFFECT_H
#define EFFECT_H

#include "SYSTEM/Manager.h"
#include "SYSTEM/Singleton.h"
#include "Element.h"

class Effect : public Base_Graphic_Element
{
    friend class EffectManager;
public:
    typedef enum { BEHIND, INFRONT } EffectShow;
    typedef enum { CUBE , SIZE_EFFECT_FORM} EffectForm;

protected:
    Effect(ID id);

public:
    // l'effet concerne la cell 'cell' -> on recalcul les parametres de l'effet
    virtual void assignElement(const Graphic_Element *element);

    virtual void show(sf::RenderTarget &render);

    // fonction pour definir quel est le coté (devant derriere) a dessiner
    void setShowState(EffectShow state);

    ID getId() const;

    // fonction appelé par assignGraphicElement pour recalculé les paramètres de l'effet
    virtual void updateParameters() = 0;

protected:
    // fonction pour dessiner le devant ou l'arriere de l'effet
    virtual void showEffectBehind(sf::RenderTarget &render) = 0;
    virtual void showEffectInfront(sf::RenderTarget &render) = 0;

protected:
    ID m_id;
    const Graphic_Element *m_element;

private:
    EffectShow m_stateShow;
};

class EffectManager : public ManagerType<Effect>
{
protected:
    virtual Effect* createObjet(ID id, int type);
};

class EffectManagerSingleton : public CSingleton<EffectManager>
{

};


#endif // EFFECT_H
