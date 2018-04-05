#include "MapRender.h"

#include <cmath>

MapRender::MapRender(MapManager *mapManager, sf::Vector2i render_size) :
    Object (render_size),
    m_view (sf::FloatRect(0,0, m_size.x, m_size.y))
{   
    m_draggable = true;

    m_backgroundColor = sf::Color::Black;
    m_drawnGrid = new QList<sf::Vector2i>;

    m_mapManager = mapManager;

    m_lightTexture.create(m_size.x,m_size.y);

    m_showGrid = true;
    m_updateGrid = true;

    m_view.setCenter(0,0);
    m_view.zoom(DEFAULT_ZOOM);
    m_viewPosition.x = 0;
    m_viewPosition.y = 0;
    m_updateView = true;
    m_viewTime = 0;
    m_viewElapsedTime = 0;
    m_viewOriginalPosition = m_viewPosition;
    m_viewDestination = m_viewPosition;

    m_zoom = 1;
    m_zoom /= DEFAULT_ZOOM;
    m_updateZoom= false;
    m_zoomDestination = m_zoom;
    m_zoomOriginal = m_zoom;
    m_zoomTime = 0;
    m_zoomElapsedTime = 0;

    m_gridCell.setPointCount(4);
    m_gridCell.setPoint(0, sf::Vector2f (CELL_SIZE_X/2, 0));
    m_gridCell.setPoint(1, sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2));
    m_gridCell.setPoint(2,sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y));
    m_gridCell.setPoint(3,sf::Vector2f(0, CELL_SIZE_Y/2));
    m_gridCell.setFillColor(sf::Color(128,128,128,150));
    m_gridCell.setScale(sf::Vector2f(0.8,0.8));
    m_compensation.x = (CELL_SIZE_X*0.1);
    m_compensation.y = (CELL_SIZE_Y*0.1);
}

void MapRender::show (sf::RenderTarget &render)
{
    sf::RenderStates renderStates(sf::BlendAdd);
    renderStates.shader = &BLUR_SHADER;

    if (m_updateView)
        updateView();

    if (m_updateZoom)
        updateZoom();

    if (m_updateGrid)
        updateScrollBoxF();

    // On affiche la carte

    m_toDrawLights.clear();
    m_lightWalls.clear();

    m_texture.clear(m_backgroundColor);
    m_lightTexture.clear(sf::Color::Transparent);

    m_texture.setView(m_view);
    m_lightTexture.setView(m_view);

    for (int i =0; i != m_drawnGrid->size();i++)
    {
        sf::Vector2i pos = m_drawnGrid->at(i);

        if (m_mapManager->exist(pos))
        {
            const QList<GameLayer*> * layers = m_mapManager->getLayersOrder();
            foreach (const GameLayer *layer, *layers)
            {
                Container *container = m_mapManager->getCell(pos, false);

                if (container->isCollision() || container->getHeight() != 0)
                {
                    sf::Vector2f position = toScreenCoords(container->getVPosition())+sf::Vector2f(0,container->getHeight());

                    m_lightWalls<<Wall(sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2)+position,
                                       sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y)+position);

                    m_lightWalls<<Wall(sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y)+position,
                                       sf::Vector2f(0, CELL_SIZE_Y/2)+position);

                    m_lightWalls<<Wall(sf::Vector2f(0, CELL_SIZE_Y/2)+position,
                                       sf::Vector2f(CELL_SIZE_X/2, 0)+position);

                    m_lightWalls<<Wall(sf::Vector2f (CELL_SIZE_X/2, 0)+position,
                                       sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2)+position);

                }

                if (m_showGrid && layer->getId() == -1) // Tracer la grille avant le sol (le niveau -1 represente le sol)
                {
                    m_gridCell.setPosition(toScreenCoords(pos)+
                                           m_compensation+
                                           sf::Vector2f(0,container->getHeight()));
                    m_texture.draw(m_gridCell);
                }

                if (layer->isVisible() &&
                        container->exist(layer->getId()))
                {
                    if (container->data(layer->getId())->getType() != LIGHT)
                        container->data(layer->getId())->show(m_texture);

                    else
                        m_toDrawLights<<container->light(layer->getId());
                }
            }

        }

        else if (m_showGrid)
         m_gridCell.setPosition(toScreenCoords(pos)+m_compensation), m_texture.draw(m_gridCell);

    }

    foreach (Light *light, m_toDrawLights)
     light->generate(m_lightWalls), light->show(m_lightTexture);

    m_texture.display();
    m_sprite.setTexture(m_texture.getTexture(),true);
    render.draw(m_sprite);

    m_lightTexture.display();
    m_sprite.setTexture(m_lightTexture.getTexture(),true);
    render.draw(m_sprite,renderStates);
}

void MapRender::updatePosition()
{
    m_sprite.setPosition(sf::Vector2f(m_position));
}


void MapRender::updateScrollBox()
{
    m_updateGrid = true;
}

void MapRender::updateScrollBoxF()
{
    if(m_mapManager->mapExist())
    {
        m_drawnGrid->clear();

        int margeX =  CELL_SIZE_X*MAP_MARGE;
        int margeY =  CELL_SIZE_Y*MAP_MARGE;

        sf::Vector2f view = m_view.getCenter();
        sf::Vector2i viewHG;
        viewHG.x = view.x - m_view.getSize().x/2 - margeX;
        viewHG.y = view.y - m_view.getSize().y/2 - margeY;

        viewHG = viewCoordsToTileCoords(viewHG);

        sf::Vector2i current;

        int nbCellWidth = std::ceil(m_view.getSize().x / CELL_SIZE_X + 2*MAP_MARGE);
        int nbCellHeight = std::ceil(m_view.getSize().y / CELL_SIZE_Y + 2*MAP_MARGE);

        bool gx = false, gy = true;

        for(int i = 0 ; i < nbCellHeight*2 ; ++i)
        {
            current = viewHG;
            for(int j = 0 ; j < nbCellWidth ; ++j)
            {
                if(m_mapManager->inProportions(current))
                    *m_drawnGrid << current;
                current.x++;
                current.y--;
            }
            if(gx) { gy = true; gx = false; viewHG.x++;}
            else if(gy) { gx = true; gy = false; viewHG.y++;}
        }
    }

    m_updateGrid = false;
}

void MapRender::addToScrollBox(const sf::Vector2i &cell)
{
    if (!m_drawnGrid->contains(cell))
    {
        *m_drawnGrid<<cell;
        qSort(*m_drawnGrid);
    }
}

void MapRender::removeFromScrollBox(const sf::Vector2i &cell)
{
    int i = m_drawnGrid->indexOf(cell);
    if (i != -1)
        m_drawnGrid->removeAt(i);
}

sf::Vector2i MapRender::mouseToTileCoords (const float &x, const float &y) const
{
    return mouseToTileCoords(sf::Vector2f(x,y));
}

sf::Vector2i MapRender::mouseToTileCoords (const sf::Vector2f &mouseCoords) const
{
    return MapRender::mouseToTileCoords(sf::Vector2i(mouseCoords));
}

sf::Vector2i MapRender::mouseToTileCoords (const sf::Vector2i &mouseCoords) const
{
    sf::Vector2i tileCoords;
    sf::Vector2f _mouseCoords = mouseToViewCoords(mouseCoords);

    tileCoords.x = round(_mouseCoords.y / CELL_SIZE_Y + (_mouseCoords.x / CELL_SIZE_X)-1);
    tileCoords.y = round(_mouseCoords.y / CELL_SIZE_Y - (_mouseCoords.x / CELL_SIZE_X));

    return tileCoords;
}

sf::Vector2i MapRender::viewCoordsToTileCoords(const sf::Vector2i &coords) const
{
    sf::Vector2i tileCoords;

    tileCoords.x = round(coords.y / CELL_SIZE_Y + (coords.x / CELL_SIZE_X)-1);
    tileCoords.y = round(coords.y / CELL_SIZE_Y - (coords.x / CELL_SIZE_X));

    return tileCoords;
}

void MapRender::resetView()
{   m_viewPosition.x = 0;
    m_viewPosition.y = 0;
    m_view.setCenter(0,0);
}

void MapRender::showGrid (const bool show)
{
    m_showGrid = show;
}

QList <sf::Vector2i> MapRender::hitList (sf::Vector2f const & point, int layer_id, const unsigned short alpha)
{
    QList <sf::Vector2i> sprite_list;

    for (int i =0; i != m_drawnGrid->size();i++)
    {
        sf::Vector2i pos = m_drawnGrid->at(i);

        if (m_mapManager->exist (pos))
        {
            Container* container = m_mapManager->getCell(pos, false);
            if (container->exist(layer_id))
            {
                if (hitTest(container->cell(layer_id), point, alpha))
                {
                    sprite_list << pos;
                }
            }
        }
    }
    return sprite_list;
}

bool MapRender::hitTest(const sf::Sprite *sprite, sf::Vector2f const & point, unsigned short int const alpha)
{
    /*************************************************************/
    // Cette méthode test si un clic souris a été fait dans un
    // sprite, qu'il soit droit ou incliné.
    // Ce test est effectif pour n'importe quel angle de rotation.
    // Si la transparence du pixel est sous le seuil fixé, le test
    // retourne faux. Le seuil valant de 0 à 255.
    /*************************************************************/

    sf::Vector2f pointT = sprite->getInverseTransform().transformPoint(mouseToViewCoords(sf::Vector2i(point)));

    sf::IntRect rect = sprite->getTextureRect();

    if (pointT.x <= 0)
        return false;
    else if (pointT.x >= rect.width)
        return false;
    else if (pointT.y <= 0)
        return false;
    else if (pointT.y >= rect.height)
        return false;

    return (sprite->getTexture()->copyToImage().getPixel(pointT.x + rect.left,
                                                        pointT.y + rect.top)).a >= alpha;
}



bool MapRender::setZoom(const float &zoom)
{
    if (zoom > ZOOM_MIN && zoom <= ZOOM_MAX)
    {
        m_view.zoom(1/(zoom/getZoom()));
        m_zoom *= (zoom/getZoom());
        updateScrollBox();
        return true;
    }

    return false;
}

bool MapRender::setZoom(const float &zoom, const unsigned int &time)

{
    if (zoom > ZOOM_MIN && zoom <= ZOOM_MAX)
    {
        m_updateZoom= true;
        m_zoomDestination = zoom - m_zoom;
        m_zoomOriginal = m_zoom;
        m_zoomTime = time;
        m_zoomElapsedTime = 0;
        m_zoomTimer.restart();

        return true;
    }

    return false;
}

bool MapRender::setViewPosition (const sf::Vector2f &position)
{

    sf::Vector2f left;
    sf::Vector2f right;

    sf::Vector2i mapSize = m_mapManager->mapSize();

    left.x = toScreenCoords(0,mapSize.y-1).x;
    left.y = toScreenCoords(0,0).y;

    right.x = toScreenCoords(mapSize.x-1,0).x+CELL_SIZE_X;
    right.y = toScreenCoords(mapSize.x-1,mapSize.y-1).y+CELL_SIZE_Y;

    right -= left;


    if (position.x >= left.x &&
            position.x <= right.x &&
            position.y >= left.y &&
            position.y <= right.y)
    {
        sf::Vector2i move;

        move.x = position.x - m_viewPosition.x ;
        move.y = position.y - m_viewPosition.y;
        m_viewPosition = position;

        updateScrollBox();
        m_view.move(move.x,move.y);

        return true;
    }

    return false;
}

sf::Vector2f MapRender::mouseToViewCoords (const sf::Vector2i &point) const
{
    sf::Vector2f coords;

    float width  = m_size.x;
    float height = m_size.y;
    const sf::FloatRect& process = m_view.getViewport();

    sf::IntRect viewport (0.5f + width  * process.left,
                          0.5f + height * process.top,
                          width  * process.width,
                          height * process.height);

    coords.x = -1.f + 2.f * (point.x - viewport.left) / viewport.width;
    coords.y = 1.f - 2.f * (point.y - viewport.top)  / viewport.height;

    return m_view.getInverseTransform().transformPoint(coords);
}


float MapRender::getZoom() const
{
    return m_zoom;
}

bool MapRender::setViewVPosition(const sf::Vector2i &position)
{
    if (m_mapManager->inProportions(position))
    {setViewPosition(toScreenCoords(position));
        return true;}

    return false;
}

bool MapRender::setViewVPosition(const sf::Vector2i &position, const unsigned int &time)
{
    return setViewPosition(toScreenCoords(position)+sf::Vector2f(CELL_SIZE_X/2,CELL_SIZE_Y/2),time);
}

bool MapRender::setViewPosition(const sf::Vector2f &position, const unsigned int &time)
{
    if (m_mapManager->inProportions(sf::Vector2i(round(position.y / CELL_SIZE_Y + (position.x / CELL_SIZE_X))-1,
                                                 round(position.y / CELL_SIZE_Y - (position.x / CELL_SIZE_X))))
            && !m_updateView)
    {
        m_updateView = true;
        m_viewTime = time;
        m_viewElapsedTime = 0;
        m_viewOriginalPosition = m_viewPosition;
        m_viewDestination = position - m_viewPosition;
        m_viewTimer.restart();

        return true;
    }

    return false;
}

void MapRender::updateZoom()

{
    m_zoomElapsedTime = m_zoomTimer.getElapsedTime().asMilliseconds();

    if (m_zoomElapsedTime < m_zoomTime &&
            m_zoom != m_zoomDestination+m_zoomOriginal)
        setZoom(m_zoomOriginal+(m_zoomDestination*m_zoomElapsedTime)/m_zoomTime);


    else
    {
        setZoom(m_zoomDestination+m_zoomOriginal);
        m_updateZoom = false;
    }
}

void MapRender::updateView()
{
    m_viewElapsedTime = m_viewTimer.getElapsedTime().asMilliseconds();

    if (m_viewElapsedTime < m_viewTime && m_viewPosition != m_viewDestination+m_viewOriginalPosition)
        setViewPosition(m_viewOriginalPosition+
                        sf::Vector2f((m_viewDestination.x*m_viewElapsedTime)/m_viewTime,
                                     (m_viewDestination.y*m_viewElapsedTime)/m_viewTime));

    else
    {
        setViewPosition(m_viewDestination+m_viewOriginalPosition);
        m_updateView = false;
    }
}

sf::Vector2i MapRender::getViewVPosition() const
{
    return mouseToTileCoords(m_viewPosition);
}

sf::Vector2f MapRender::getViewPosition() const
{
    return m_viewPosition;
}

const QList<sf::Vector2i>& MapRender::getDrawnGrid ()
{
    return *m_drawnGrid;
}

bool MapRender::leftMousePressed(const sf::Vector2i &position)
{
    setFocus(true);
    emit mousePressEvent(LEFT, position);
    return true;
}

bool MapRender::rightMousePressed(const sf::Vector2i &position)
{
    emit mousePressEvent(RIGHT, position);
    return true;
}

bool MapRender::mouseMoved(const sf::Vector2i &position)
{
    emit mouseMoveEvent(position);
    return true;
}
