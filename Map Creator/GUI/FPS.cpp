#include "FPS.h"

FPS::FPS()
    : Object(sf::Vector2i(50,30))
    , m_text()
    , m_text_timer(0)
    , m_fps(0)
{
    m_text.setFont(FONT);
    m_text.setColor(sf::Color(255,0,0));
}

void FPS::show (sf::RenderTarget &render)
{
    if (m_visible)
    {
        m_texture.clear(m_backgroundColor);

        m_fps = 1 / (getElapsedTime().asMilliseconds() * 0.001);

        m_text_timer += getElapsedTime().asMilliseconds();
        if (m_text_timer >= TEXT_UPDATE_TIME)
        {
            m_text_timer = 0;
            updateText();
        }

        m_texture.draw (m_text);
        m_texture.display();
        m_sprite.setTexture(m_texture.getTexture());
        render.draw(m_sprite);
    }

    restartTimer();
}

unsigned int FPS::getFPS() const
{
    return m_fps;
}

void FPS::updateText()
{
    m_text.setString(tostdString(m_fps));
}

void FPS::changeColor()
{
    if (m_text.getColor() == sf::Color(100,255,100))
        m_text.setColor(sf::Color(255,100,100));

    else
        m_text.setColor(sf::Color(100,255,100));

    setToFront(true);
}

bool FPS::leftMousePressed (const sf::Vector2i &position)
{
    changeColor();
    return true;
}
