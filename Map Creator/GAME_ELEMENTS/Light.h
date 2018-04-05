#include "SYSTEM/Public.h"
#include "Element.h"

#ifndef LIGHTH
#define LIGHTH

struct Wall
{
    Wall (sf::Vector2f p1,sf::Vector2f p2)
    {
        pt1=p1;
        pt2=p2;
    }

    // Pt1 et Pt2 sont les deux extrémités du mur
    sf::Vector2f pt1;
    sf::Vector2f pt2;
};

// Wall_Entity est une variable qui permet de représenter dans le programme un mur
struct Wall_Entity
{
    Wall_Entity (int id)
    {
        m_ID=id;
    }

    int ID() { return m_ID; }

    private:

    int m_ID;
};


// Light_Entity est une variable qui permet de représenter dans le programme une lumière
struct Light_Entity
{
    Light_Entity (){m_Dynamic=false,m_ID=0;}
    Light_Entity (int id,bool d)
    {
        m_ID=id;
        m_Dynamic=d;
    }

    int ID() { return m_ID; }
    bool Dynamic() { return m_Dynamic; }

    private:

    int m_ID;
    bool m_Dynamic;
};


class Light : public Graphic_Element
{
public :

    // Constructeur et destructeur
    Light();
    Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color);
    ~Light();

    // Afficher la lumière
    void showObject(sf::RenderTarget &render);

    bool operator !=(const Light &compare);
    bool operator ==(const Light &compare);

    // Calculer la lumière
    virtual void generate(QList<Wall> &m_wall);

    // Ajouter un triangle à la lumière, en effet, les lumières sont composée de triangles
    void addTriangle(sf::Vector2f pt1,sf::Vector2f pt2, int minimum_wall, QList<Wall> &m_wall);

    // Changer différents attributs de la lumière
    void setIntensity(float);
    void setRadius(float);
    void setQuality(int);
    void setColor(sf::Color);

    virtual void setOtherParameter(unsigned, float);


    // Retourner différents attributs de la lumière
    float getIntensity() const;
    float getRadius() const;
    int getQuality() const;
    sf::Color getColor() const;

    void updatePosition ();

    // Une petite bool pour savoir si la lumière est allumée ou éteinte
    bool m_actif;

protected :
    //Position à l'écran
    sf::Vector2f m_position;
    //Intensité, gère la transparence ( entre 0 et 255 )
    float m_intensity;
    //Rayon de la lumière
    float m_radius;
    //Couleur de la lumière
    sf::Color m_color;
    //Qualité de la lumière, c'est à dire le nombre de triangles par défaut qui la compose.
    int m_quality;

    sf::RenderStates m_renderStates;

    //Tableau dynamique de Shape, ce sont ces shapes de type triangle qui compose la lumière
    QList<sf::VertexArray> m_shapes;
};

#endif

