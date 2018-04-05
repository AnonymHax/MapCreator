#ifndef FPS_HPP__INCLUDED
#define FPS_HPP__INCLUDED

#include "SYSTEM/Public.h"
#include "ObjectLayer.h"

#define TEXT_UPDATE_TIME 150

class FPS : public Object
{
public:

    FPS();

    unsigned int getFPS() const; // Renvoi en nombre les FPS actuel

    void show (sf::RenderTarget &render);

    void updateText();
    void changeColor();

    bool leftMousePressed (const sf::Vector2i &position);

private:

   sf::Text m_text;
   unsigned int m_text_timer;

   unsigned int m_fps;

};

#endif // FPS_HPP__INCLUDED
