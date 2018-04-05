#include "LightManager.h"
/*
Light_Manager::Light_Manager()
{
    m_lightSmooth=0;

    // Chargement du postFX pour adoucir les bords.
    if (BlurEffect.loadFromFile("blur.frag", sf::Shader::Fragment))

        BlurEffect.setParameter("texture", sf::Shader::CurrentTexture);
}

Light_Manager::~Light_Manager()
{
    for(unsigned i = 0 ; i < m_DynamicLight.size() ; ++i)
        delete m_DynamicLight[i];

    for(unsigned i = 0 ; i < m_StaticLight.size() ; ++i)
        delete m_StaticLight[i];

    m_DynamicLight.clear();
    m_StaticLight.clear();
}

// Les différents moyens d'ajouter des lumières

Light_Entity Light_Manager::Add_Dynamic_Light()
{
    m_DynamicLight.push_back(new Light());
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}
Light_Entity Light_Manager::Add_Dynamic_Light(Light light)
{
    m_DynamicLight.push_back(new Light(light));
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}
Light_Entity Light_Manager::Add_Dynamic_Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color)
{
    m_DynamicLight.push_back(new Light (position,intensity,radius,quality,color));
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}

// Les différents moyens d'ajouter des lumières directionelles

Light_Entity Light_Manager::Add_Dynamic_Directional_Light()
{
    m_DynamicLight.push_back(new Directional_light ());
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}
Light_Entity Light_Manager::Add_Dynamic_Directional_Light(Directional_light light)
{
    m_DynamicLight.push_back(new Directional_light(light));
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}
Light_Entity Light_Manager::Add_Dynamic_Directional_Light(sf::Vector2f position, float intensity, float radius, float angle, float o_angle, sf::Color color)
{
    m_DynamicLight.push_back(new Directional_light (position,intensity,radius,angle, o_angle,color));
    return Light_Entity((int)m_DynamicLight.size()-1,true);
}


// Notez bien qu'on calcule les lumières statiques lors de leur ajout.

Light_Entity Light_Manager::Add_Static_Light(Light light)
{
    m_StaticLight.push_back(new Light(light));
    m_StaticLight.back()->Generate(m_wall);
    return Light_Entity((int)m_StaticLight.size()-1,false);
}
Light_Entity Light_Manager::Add_Static_Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color)
{
    m_StaticLight.push_back(new Light (position,intensity,radius,quality,color));
    m_StaticLight.back()->Generate(m_wall);
    return Light_Entity((int)m_StaticLight.size()-1,false);
}

// Notez bien qu'on calcule les lumières statiques lors de leur ajout.

Light_Entity Light_Manager::Add_Static_Directional_Light(Directional_light light)
{
    m_StaticLight.push_back(new Directional_light(light));
    m_StaticLight.back()->Generate(m_wall);
    return Light_Entity((int)m_StaticLight.size()-1,false);
}
Light_Entity Light_Manager::Add_Static_Directional_Light(sf::Vector2f position, float intensity, float radius, float angle, float o_angle, sf::Color color)
{
    m_StaticLight.push_back(new Directional_light (position,intensity,radius,angle,o_angle,color));
    m_StaticLight.back()->Generate(m_wall);
    return Light_Entity((int)m_StaticLight.size()-1,false);
}

// Ajouter un mur

Wall_Entity Light_Manager::Add_Wall(sf::Vector2f pt1,sf::Vector2f pt2)
{
    for(int i=0;i<(int)m_wall.size();i++)
        if((pt1.y-pt2.y)/(pt1.x-pt2.y)==(m_wall[i].pt1.y-m_wall[i].pt2.y)/(m_wall[i].pt1.x-m_wall[i].pt2.y))
            if(pt1==m_wall[i].pt1 || pt2==m_wall[i].pt1 || pt1==m_wall[i].pt2 || pt2==m_wall[i].pt2)
            {
                sf::Vector2f min=pt1,max=pt2;

                if(pt2.x<min.x)
                    min.x=pt2.x;
                if(pt1.x>max.x)
                    max.x=pt2.x;

                if(m_wall[i].pt1.x<min.x)
                    min.x=m_wall[i].pt1.x;
                if(m_wall[i].pt2.x<min.x)
                    min.x=m_wall[i].pt2.x;

                if(m_wall[i].pt1.x>max.x)
                    max.x=m_wall[i].pt1.x;
                if(m_wall[i].pt2.x>max.x)
                    max.x=m_wall[i].pt2.x;


                if(pt2.y<min.y)
                    min.y=pt2.y;
                if(pt1.y>max.y)
                    max.y=pt2.y;

                if(m_wall[i].pt1.y<min.y)
                    min.y=m_wall[i].pt1.y;
                if(m_wall[i].pt2.y<min.y)
                    min.y=m_wall[i].pt2.y;

                if(m_wall[i].pt1.y>max.y)
                    max.y=m_wall[i].pt1.y;
                if(m_wall[i].pt2.y>max.y)
                    max.y=m_wall[i].pt2.y;

                m_wall[i].pt1=min;
                m_wall[i].pt2=max;

                return Wall_Entity(i);

            }

    m_wall.push_back(Wall (pt1,pt2));
    return Wall_Entity(m_wall.size()-1);
}

// On désactive une lumière
void Light_Manager::Delete_Light(Light_Entity e)
{
    if(e.Dynamic())
    {
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()]->m_actif = false;
    }
    else
        if(e.ID()>=0&&e.ID()<(int)m_StaticLight.size())
            m_StaticLight[e.ID()]->m_actif  = false;
}

// On supprime un mur
void Light_Manager::Delete_Wall(Wall_Entity e)
{
    m_wall.erase(m_wall.begin()+e.ID());
}

void Light_Manager::Delete_All_Wall()
{
    m_wall.clear();
}
void Light_Manager::Delete_All_Light()
{
    for(unsigned i = 0 ; i < m_DynamicLight.size() ; ++i)
        delete m_DynamicLight[i];

    for(unsigned i = 0 ; i < m_StaticLight.size() ; ++i)
        delete m_StaticLight[i];

    m_DynamicLight.clear();
    m_StaticLight.clear();
}


// On calcule toutes les lumières dynamiques actives
void Light_Manager::Generate()
{
    m_renderImg.clear(m_basicLight);
    BlurEffect.setParameter("offset",0.005 * m_lightSmooth);

    for(Iter=m_DynamicLight.begin();Iter!=m_DynamicLight.end();++Iter)
        if((*Iter)->m_actif)
            (*Iter)->Generate(m_wall), (*Iter)->Draw(m_renderImg);

    for(Iter=m_StaticLight.begin();Iter!=m_StaticLight.end();++Iter)
        if((*Iter)->m_actif)
            (*Iter)->Draw(m_renderImg);

    m_renderImg.display();
}


void Light_Manager::Generate(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()]->Generate(m_wall);
}

// On crée une image avec toutes les lumières actives
void Light_Manager::DrawLights(sf::RenderTarget *App, sf::View &View)
{
    sf::RenderStates r(sf::BlendMultiply);
    r.shader = &BlurEffect;
    m_renderImg.create(View.getSize().x, View.getSize().y,true);
    App->draw(sf::Sprite (m_renderImg.getTexture()),r);
}


void Light_Manager::DrawLightsT(sf::RenderTarget &App)
{
    for(Iter=m_DynamicLight.begin();Iter!=m_DynamicLight.end();++Iter)
        if((*Iter)->m_actif)
            (*Iter)->Generate(m_wall), (*Iter)->Draw(App);

    for(Iter=m_StaticLight.begin();Iter!=m_StaticLight.end();++Iter)
        if((*Iter)->m_actif)
            (*Iter)->Draw(App);
}

// On modifie ou récupère les attributs de lumières dynamiques

void Light_Manager::setPosition(Light_Entity e, sf::Vector2f p)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()]->setPosition(p);
}
void Light_Manager::setQuality(Light_Entity e, int q)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()]->setQuality(q);
}
void Light_Manager::setRadius(Light_Entity e, int r)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()]->setRadius(r);
}
void Light_Manager::setColor(Light_Entity e, sf::Color c)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()]->setColor(c);
}
void Light_Manager::setIntensity(Light_Entity e, int i)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()]->setIntensity(i);
}

void Light_Manager::setOtherParameter(Light_Entity e, unsigned no, float v)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            m_DynamicLight[e.ID()]->setOtherParameter(no, v);
}


float Light_Manager::getIntensity(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()]->getIntensity();
    return 0;
}

float Light_Manager::getRadius(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()]->getRadius();
    return 0;
}

int Light_Manager::getQuality(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()]->getQuality();

    return 0;
}

sf::Color Light_Manager::getColor(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()]->getColor();

    return sf::Color (0,0,0);
}
sf::Vector2f Light_Manager::getPosition(Light_Entity e)
{
    if(e.Dynamic())
        if(e.ID()>=0&&e.ID()<(int)m_DynamicLight.size())
            return m_DynamicLight[e.ID()]->getPosition();

    return sf::Vector2f (0,0);
}

// On modifie ou récupère différents attributs des murs

void Light_Manager::setPosition(Wall_Entity e, sf::Vector2f p)
{
    if(e.ID()>=0&&e.ID()<(int)m_wall.size())
    {
        sf::Vector2f buffer=m_wall[e.ID()].pt1;
        m_wall[e.ID()].pt1=p;
        m_wall[e.ID()].pt2.x= m_wall[e.ID()].pt2.x + (p.x-buffer.x);
        m_wall[e.ID()].pt2.y= m_wall[e.ID()].pt2.y + (p.y-buffer.y);
    }
}
*/
