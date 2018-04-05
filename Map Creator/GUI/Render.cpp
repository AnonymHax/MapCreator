#include "Render.h"

Render::Render(QWidget* Parent, const QPoint& Position, const QSize& Size) :
    QSFMLCanvas(Parent, Position, Size, 1000/RENDER_FPS), ObjectContainer(sf::Vector2i(Size.width(), Size.height()))
{
    m_size.x = Size.width();
    m_size.y = Size.height();

    m_eventsUpdater.setInterval(1000/EVENTS_FPS);
    connect (&m_eventsUpdater, SIGNAL(timeout()), this, SLOT(updateEvents()));
    m_eventsUpdater.start();
}

void Render::updateRender()
{
    ObjectContainer::show(*this);
}

void Render::updateEvents()
{
    if (pollEvent(m_events))
        handleEvent(m_events);
}
