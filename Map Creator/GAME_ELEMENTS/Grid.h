#ifndef GRID_H
#define GRID_H

#include "SYSTEM/Public.h"
#include <QMutex>

class Grid
{
public:
    Grid(QList<sf::Vector2i> &list, float &zoom);
    void show (sf::RenderTarget &render_window);

public:
    QMutex mutex;

private:

sf::ConvexShape grid_cell;
QList<sf::Vector2i> &toDraw;
float &current_zoom;
sf::Vector2f compensation;

};

#endif // GRID_H
