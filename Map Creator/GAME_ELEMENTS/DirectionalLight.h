#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "Light.h"

enum {ANGLE, OPENING_ANGLE};

class Directional_light : public Light
{
    public:
        Directional_light();
        Directional_light(sf::Vector2f position, float intensity, float radius, float angle, float opening_angle, sf::Color colo);
        virtual ~Directional_light();

        bool operator !=(const Directional_light &compare);
        bool operator ==(const Directional_light &compare);
        void generate(QList<Wall> &m_walls);

        void setAngle(float angle);
        void setOpeningAngle(float angle);

        float getAngle () const;
        float getOpeningAngle ()const;

        void setOtherParameter(unsigned, float);

    protected:
    private:

        float m_angle;
        float m_opening_angle;
};

#endif // DIRECTIONNAL_LIGHT_H
