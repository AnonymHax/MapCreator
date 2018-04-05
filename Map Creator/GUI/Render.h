#ifndef RENDER_H
#define RENDER_H

#include "QSFMLCanvas.h"
#include "GUI/MapGlobal.h"

// Classe fusionnant Qt et SFML

class Render : public QSFMLCanvas, public ObjectContainer // Cette classe sert de base a tous layers ne voulant pas de parent
{
    Q_OBJECT

public:

    Render(QWidget* Parent, const QPoint& Position, const QSize& Size);

public slots:

    void updateRender();
    void updateEvents();

private:

   QTimer m_eventsUpdater;
   sf::Event m_events;
};

#endif // RENDER_H
