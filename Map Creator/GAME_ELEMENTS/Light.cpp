#include "light.h"

Light::Light()
    : Graphic_Element(LIGHT)
    , m_actif(true)
    , m_position(0,0)
    , m_intensity(0)
    , m_radius(0)
    , m_color()
    , m_quality(0)
    , m_renderStates()
    , m_shapes()
{
    m_renderStates.blendMode = sf::BlendAdd;
}

Light::Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color)
    : Graphic_Element(LIGHT)
    , m_actif(true)
    , m_position(position)
    , m_intensity(intensity)
    , m_radius(radius)
    , m_color(color)
    , m_quality(quality)
    , m_renderStates()

{
    updatePosition();
    m_renderStates.blendMode = sf::BlendAdd;
}

Light::~Light()
{
    m_shapes.clear();
}

void Light::showObject(sf::RenderTarget &render)
{
    foreach (const sf::VertexArray &shape, m_shapes)
        render.draw(shape, m_renderStates);
}

bool Light::operator !=(const Light &compare)
{
    if (compare.m_position == m_position &&
        compare.m_color == m_color &&
        compare.m_intensity == m_intensity &&
        compare.m_radius == m_radius &&
        compare.m_quality == m_quality &&
        compare.m_height == m_height)
          return false;

    return true;
}

bool Light::operator ==(const Light &compare)
{
    return !(*this != compare);
}

sf::Vector2f Intersect(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
    sf::Vector2f i;

    if((p2.x - p1.x) == 0 && (q2.x - q1.x) == 0)
        i.x = 0, i.y = 0;
    else if((p2.x - p1.x) == 0)
    {
        i.x = p1.x;

        float c = (q2.y - q1.y) / (q2.x - q1.x);
        float d = q1.y - q1.x * c;

        i.y = c * i.x + d;
    }

    else if((q2.x - q1.x) == 0)
    {
        i.x = q1.x;

        float a = (p2.y - p1.y) / (p2.x - p1.x);
        float b = p1.y - p1.x * a;

        i.y = a * i.x + b;
    }
    else
    {
        float a = (p2.y - p1.y) / (p2.x - p1.x);
        float b = p1.y - p1.x * a;

        float c = (q2.y - q1.y) / (q2.x - q1.x);
        float d = q1.y - q1.x * c;

        i.x = (d-b)/(a-c);
        i.y = a * i.x + b;
    }

    return i;
}

sf::Vector2f Collision(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2)
{
    sf::Vector2f i;
    i = Intersect(p1, p2, q1, q2);

    if(((i.x >= p1.x - 0.1 && i.x <= p2.x + 0.1)
        || (i.x >= p2.x - 0.1 && i.x <= p1.x + 0.1))
            && ((i.x >= q1.x - 0.1 && i.x <= q2.x + 0.1)
                || (i.x >= q2.x - 0.1 && i.x <= q1.x + 0.1))
            && ((i.y >= p1.y - 0.1 && i.y <= p2.y + 0.1)
                || (i.y >= p2.y - 0.1 && i.y <= p1.y + 0.1))
            && ((i.y >= q1.y - 0.1 && i.y <= q2.y + 0.1)
                || (i.y >= q2.y - 0.1 && i.y <= q1.y + 0.1)))
        return i;
    else
        return sf::Vector2f (0,0);
}

void Light::addTriangle(sf::Vector2f pt1,sf::Vector2f pt2, int minimuwalls, QList<Wall> &walls)
{
    int w = minimuwalls;
    // On boucle sur tous les murs
    foreach (const Wall &wall, walls)
    {
        // l1 et l2 sont les positions relatives au centre de la lumière des deux extrémités du mur
        sf::Vector2f l1(wall.pt1.x-m_position.x, wall.pt1.y-m_position.y);
        sf::Vector2f l2(wall.pt2.x-m_position.x, wall.pt2.y-m_position.y);

        if(l1.x * l1.x + l1.y * l1.y < m_radius * m_radius)
        {
            sf::Vector2f i = Intersect(pt1,pt2,sf::Vector2f (0,0),l1);

            if (pt1 != i && pt2 != i)
                if((pt1.x >= i.x && pt2.x <= i.x) || (pt1.x <= i.x && pt2.x >= i.x))
                    if((pt1.y >= i.y && pt2.y <= i.y) || (pt1.y <= i.y && pt2.y >= i.y))
                        if((l1.y >= 0 && i.y >= 0) || (l1.y <= 0 && i.y <= 0))
                            if((l1.x >= 0 && i.x >= 0) || (l1.x <= 0 && i.x <= 0))
                                addTriangle(i, pt2, w, walls), pt2 = i;
        }
        if(l2.x * l2.x + l2.y * l2.y < m_radius * m_radius)
        {
            sf::Vector2f i = Intersect(pt1,pt2,sf::Vector2f (0,0),l2);

            if (pt1 != i && pt2 != i)
                if((pt1.x >= i.x && pt2.x <= i.x) || (pt1.x <= i.x && pt2.x >= i.x))
                    if((pt1.y >= i.y && pt2.y <= i.y) || (pt1.y <= i.y && pt2.y >= i.y))
                        if((l2.y >= 0 && i.y >= 0) || (l2.y <= 0 && i.y <= 0))
                            if((l2.x >= 0 && i.x >= 0) || (l2.x <= 0 && i.x <= 0))
                                addTriangle(pt1, i, w, walls), pt1 = i;
        }

        sf::Vector2f m = Collision(l1, l2, sf::Vector2f(0,0), pt1);
        sf::Vector2f n = Collision(l1, l2, sf::Vector2f(0,0), pt2);
        sf::Vector2f o = Collision(l1, l2, pt1, pt2);

        if((m.x != 0 || m.y != 0) && (n.x != 0 || n.y != 0))
            pt1 = m, pt2 = n;
        else
        {
            if((m.x != 0 || m.y != 0) && (o.x != 0 || o.y != 0))
                addTriangle(m ,o , w, walls), pt1 = o;

            if((n.x != 0 || n.y != 0) && (o.x != 0 || o.y != 0))
                addTriangle(o ,n , w, walls), pt2 = o;
        }
    }

    // Variable qui contiendra l'intensité calculée, pour le dégradé
    float intensity;
    float intensity2;

    // On ajoute un shape
    m_shapes.push_back(sf::VertexArray ());
    m_shapes.back().setPrimitiveType(sf::Triangles);

    // On lui donne comme point de départ (0,0), le centre de la lumière, avec la couleur et intensité maximal
    m_shapes.back().append(sf::Vertex(m_position,
                                     sf::Color((int)(m_intensity*m_color.r/255),
                                               (int)(m_intensity*m_color.g/255),
                                               (int)(m_intensity*m_color.b/255))));

    // On calcul ou l'on se trouve par rapport au centre, pour savoir à quel intensité on est
    intensity=m_intensity-sqrt(pt1.x*pt1.x + pt1.y*2*pt1.y*2)*m_intensity/m_radius;
    // Et on ajoute un  point au shape
    m_shapes.back().append(sf::Vertex(m_position + pt1,
                                     sf::Color((int)(intensity*m_color.r/255),
                                               (int)(intensity*m_color.g/255),
                                               (int)(intensity*m_color.b/255))));

    // Idem
    intensity2=m_intensity-sqrt(pt2.x*pt2.x + pt2.y*2*pt2.y*2)*m_intensity/m_radius;
    m_shapes.back().append(sf::Vertex(m_position + pt2,
                                     sf::Color((int)(intensity2*m_color.r/255),
                                               (int)(intensity2*m_color.g/255),
                                               (int)(intensity2*m_color.b/255))));
}

void Light::generate(QList<Wall> &walls)
{
    // On vide la mémoire
    m_shapes.clear();

    // buf est l'angle de chaque triangle, c'est donc 2pi divisé par le nombre de triangles
    float buf=(M_PI*2)/(float)m_quality;

    // On ajoute tous les triangles qui composent la lumière
    for(int i=0;i<m_quality;i++)
    {
      //  sf::Vector2f ga (sf::Vector2f((float)((float)m_radius*cos((float)i*buf))
       //                               ,(float)((float)m_radius*sin((float)i*buf))/2));
         //       qDebug()<<"X"<<ga.x<<"Y:"<<ga.y;
        addTriangle(sf::Vector2f((float)((float)m_radius*cos((float)i*buf))
                                 ,(float)((float)m_radius*sin((float)i*buf))/2) ,
                    sf::Vector2f((float)((float)m_radius*cos((float)(i+1)*buf))
                                 ,(float)((float)m_radius*sin((float)(i+1)*buf)/2)),0,walls);
    }
}

// Différentes fonctions pour modifier les attributs de la lumière, et pour les récupérer

void Light::setIntensity(float intensity)
{
    m_intensity=intensity;
}

void Light::setRadius(float radius)
{
    m_radius=radius;
}

void Light::setQuality(int quality)
{
    m_quality=quality;
}

void Light::setColor(sf::Color color)
{
    m_color=color;
}

void Light::setOtherParameter(unsigned n, float v)
{

}

float Light::getIntensity() const
{
    return m_intensity;
}

float Light::getRadius() const
{
    return m_radius;
}

int Light::getQuality() const
{
    return m_quality;
}

sf::Color Light::getColor() const
{
    return m_color;
}

void Light::updatePosition ()
{
    sf::Vector2f position = toScreenCoords(m_vposition);
    m_position = sf::Vector2f(position.x + CELL_SIZE_X/2, position.y + CELL_SIZE_Y/2 + m_height);
}


