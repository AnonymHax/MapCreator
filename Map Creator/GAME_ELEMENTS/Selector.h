#ifndef SELECTOR_H
#define SELECTOR_H

#include "SYSTEM/Public.h"
#include "ElementContainer.h"

class Selector : public QObject, public sf::ConvexShape, public Graphic_Element // Cette classe est specialement faite pour les/la case(s) rouges qui selectionne et place les objets sur la carte
{

    Q_OBJECT

public:

    Selector();

    void showObject (sf::RenderTarget &render);
    void updatePosition ();  // Place le sprite a sa position reelle par apport a sa position relative

    void setVPosition (const Container *reference);
    void setVPosition (sf::Vector2i position);

signals:

    void selectorMoved (sf::Vector2i position); // Envoi un signal, contenant sa position à l'interface
};

#endif // SELECTOR_H
