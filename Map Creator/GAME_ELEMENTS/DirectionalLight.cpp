#include "DirectionalLight.h"

Directional_light::Directional_light() : Light()
{
    m_angle = 0;
    m_opening_angle = 0;
}

Directional_light::Directional_light(sf::Vector2f position, float intensity, float radius, float angle, float opening_angle, sf::Color colo)
    : Light(position, intensity, radius, 0, colo), m_angle(angle), m_opening_angle(opening_angle)
{
}

Directional_light::~Directional_light()
{
    //dtor
}

void Directional_light::generate(QList<Wall> &m_walls)
{
    m_shapes.clear();

    float angle     = m_angle * M_PI / 180;
    float o_angle   = m_opening_angle * M_PI / 180;

    addTriangle(sf::Vector2f((m_radius*cos(angle + o_angle * 0.5))
                             ,(m_radius*sin(angle + o_angle * 0.5))) ,
                sf::Vector2f((m_radius*cos(angle - o_angle * 0.5))
                             ,(m_radius*sin(angle - o_angle * 0.5))),0,m_walls);

}

void Directional_light::setAngle(float angle)
{
    m_angle = angle;
}

float Directional_light::getAngle() const
{
    return m_angle;
}

void Directional_light::setOpeningAngle(float angle)
{
    m_opening_angle = angle;
}

float Directional_light::getOpeningAngle() const
{
    return m_opening_angle;
}

void Directional_light::setOtherParameter(unsigned n, float v)
{
    if(n == ANGLE)
        setAngle(v);
    else if(n == OPENING_ANGLE)
        setOpeningAngle(v);
}

bool Directional_light::operator !=(const Directional_light &compare)
{
    if (compare.m_position == m_position &&
        compare.m_color == m_color &&
        compare.m_angle == m_angle &&
        compare.m_opening_angle == m_opening_angle &&
        compare.m_intensity == m_intensity &&
        compare.m_radius== m_radius &&
        compare.m_quality == m_quality &&
        compare.m_height == m_height)
          return false;

    return true;
}

bool Directional_light::operator ==(const Directional_light &compare)
{
    return !(*this != compare);
}
