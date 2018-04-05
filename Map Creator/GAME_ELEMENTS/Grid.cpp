#include "Grid.h"

Grid::Grid(QList<sf::Vector2i> &list, float &zoom)
    : toDraw (list), current_zoom (zoom)
{
    grid_cell.setPointCount(4);
    grid_cell.setPoint(0, sf::Vector2f (VIRTUAL_SIZE_X/2, 0));
    grid_cell.setPoint(1, sf::Vector2f(VIRTUAL_SIZE_X,VIRTUAL_SIZE_Y/2));
    grid_cell.setPoint(2,sf::Vector2f(VIRTUAL_SIZE_X/2, VIRTUAL_SIZE_Y));
    grid_cell.setPoint(3,sf::Vector2f(0, VIRTUAL_SIZE_Y/2));
    grid_cell.setFillColor(sf::Color(128,128,128,110));
    grid_cell.setScale(sf::Vector2f(0.8,0.8));
    compensation.x = (VIRTUAL_SIZE_X*0.1);
    compensation.y = (VIRTUAL_SIZE_Y*0.1);
}


void Grid::show (sf::RenderTarget &render_window)

{
    mutex.lock();

    foreach (const sf::Vector2i &pos, toDraw)
    {
        grid_cell.setPosition(toScreenCoords(pos)+compensation);
        render_window.draw(grid_cell);
    }

    mutex.unlock();
}
