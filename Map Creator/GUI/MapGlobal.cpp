#include "MapGlobal.h"

MapGlobal::MapGlobal(MapManager *manager, sf::Vector2i size)
    : Object (size)
    , m_manager(manager)
    , m_overview()
    , m_view()
    , m_cellNb(0,0)
    , m_rendered(false)
    , m_switch(false)
    , m_transparency(0)
    , m_dynamic(true)

{
    m_overview << new sf::RenderTexture << new sf::RenderTexture;
    m_overview[0]->create(size.x,size.y);
    m_overview[1]->create(size.x,size.y);
}

void MapGlobal::show(sf::RenderTarget &target)
{
    int nbParsedCells = 0;

    if (m_manager->mapExist() && getElapsedTime().asMilliseconds() > UPDATE_TIME)
    {
        while (m_cellNb.y < m_manager->mapSize().y)
        {
            nbParsedCells++;

            const QList<GameLayer*>* layers = m_manager->getLayersOrder();
            foreach (const GameLayer *layer, *layers)
            {
                if (layer->isVisible())
                {
                    if (m_manager->exist(m_cellNb))
                    {
                        Container *cell = m_manager->getCell(m_cellNb);
                        if(cell == NULL)
                            continue;

                        if (cell->exist(layer->getId()))
                        {
                            m_overview[m_switch]->setView(m_view);
                            cell->data(layer->getId())->show(*m_overview[m_switch]);
                        }
                    }
                }
            }

            if (m_cellNb.x >= m_manager->mapSize().x-1)
            {
                m_cellNb.x = 0;
                m_cellNb.y++;
            }

            else
                m_cellNb.x++;


            if (nbParsedCells >= CELLS_RENDERED*(getElapsedTime().asMilliseconds()/UPDATE_TIME))
                break;
        }

        if (m_cellNb.y >= m_manager->mapSize().y -1)
        {
            m_overview[m_switch]->display();
            m_switch = !m_switch;
            m_overview[m_switch]->clear(sf::Color::Transparent);

            sf::Vector2f left;
            sf::Vector2f right;

            left.x = toScreenCoords(0,m_manager->mapSize().y-1).x;
            left.y = toScreenCoords(0,0).y;

            right.x = toScreenCoords(m_manager->mapSize().x-1,0).x+CELL_SIZE_X;
            right.y = toScreenCoords(m_manager->mapSize().x-1,m_manager->mapSize().y-1).y+CELL_SIZE_Y;

            right -= left;

            m_view.reset(sf::FloatRect(left,right));
            m_cellNb.x = 0;
            m_cellNb.y = 0;
        }

        restartTimer();
    }

    m_texture.clear(sf::Color(m_backgroundColor.r,m_backgroundColor.g,m_backgroundColor.b,m_backgroundColor.a+m_transparency));
    m_texture.draw(sf::Sprite(m_overview[!m_switch]->getTexture()));
    m_texture.display();
    m_sprite.setTexture(m_texture.getTexture());
    target.draw(m_sprite);
}

bool MapGlobal::leftMousePressed(const sf::Vector2i &position)
{
    sf::Vector2f mouseCoords;

    float width  = m_size.x;
    float height = m_size.y;
    const sf::FloatRect& process = m_view.getViewport();

    sf::IntRect viewport (0.5f + width  * process.left,
                          0.5f + height * process.top,
                          width  * process.width,
                          height * process.height);

    mouseCoords.x = -1.f + 2.f * (position.x - viewport.left) / viewport.width;
    mouseCoords.y = 1.f - 2.f * (position.y - viewport.top)  / viewport.height;

    mouseCoords = m_view.getInverseTransform().transformPoint(mouseCoords);

    sf::Vector2i tileCoords;

    tileCoords.x = round(mouseCoords.y / (((CELL_SIZE_Y))) + (mouseCoords.x / ((CELL_SIZE_X)))- 1);
    tileCoords.y = round(mouseCoords.y / (((CELL_SIZE_Y))) - (mouseCoords.x / ((CELL_SIZE_X))));

    return true;
}


void MapGlobal::setDynamic(bool choice)
{
    m_dynamic=choice;
}

bool MapGlobal::mouseMoved(const sf::Vector2i &position)
{
    if (m_dynamic)
        m_transparency = -100;

    return false;
}

void MapGlobal::mouseNoLongerOnObjet()
{
    m_transparency = 0;
}
