#include "Cube.h"

Cube::Cube(ID id)
    : Effect(id)
    , m_top()
    , m_bottom()
    , m_line1()
    , m_line2()
    , m_line3()
    , m_line4()
    , m_floor()
    , m_side(0)
    , m_size(0,0)
    , m_height2(0)
    , m_cell (NULL)
{
    m_top.setPointCount(4);
    m_top.setPoint(0, sf::Vector2f (CELL_SIZE_X/2, 0));
    m_top.setPoint(1, sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2));
    m_top.setPoint(2,sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y));
    m_top.setPoint(3,sf::Vector2f(0, CELL_SIZE_Y/2));
    m_top.setOutlineThickness(1);

    m_top.setOutlineColor(sf::Color(90,170,70,255));
    m_top.setFillColor(sf::Color(0,0,0,0));

    m_bottom.setPointCount(4);
    m_bottom.setPoint(0, sf::Vector2f (CELL_SIZE_X/2, 0));
    m_bottom.setPoint(1, sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2));
    m_bottom.setPoint(2,sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y));
    m_bottom.setPoint(3,sf::Vector2f(0, CELL_SIZE_Y/2));
    m_bottom.setOutlineThickness(1);

    m_bottom.setOutlineColor(sf::Color(90,170,70,255));
    m_bottom.setFillColor(sf::Color(0,0,0,0));

    m_line1.setOutlineColor(sf::Color(90,170,70,255));
    m_line1.setOutlineThickness(1);

    m_line2.setOutlineColor(sf::Color(90,170,70,255));
    m_line2.setOutlineThickness(1);

    m_line3.setOutlineColor(sf::Color(90,170,70,255));
    m_line3.setOutlineThickness(1);

    m_line4.setOutlineColor(sf::Color(90,170,70,255));
    m_line4.setOutlineThickness(1);
}

void Cube::showEffectBehind(sf::RenderTarget &render)
{
    render.draw(m_bottom);
    render.draw(m_line4);
}

void Cube::assignElement(const Graphic_Element *element)
{
    m_element = element;
    m_cell = static_cast<const Cell*>(element);
    updateParameters();
}

void Cube::showEffectInfront(sf::RenderTarget &render)
{
    render.draw(m_top);
    render.draw(m_line1);
    render.draw(m_line3);
    render.draw(m_line2);
}

void Cube::updateParameters()
{
    int currentFrame = m_cell->getCurrentFrame();
    QString currentAnim = m_cell->getCurrentAnim();

    const Tile* tile = m_cell->tile();
    if(tile == NULL)
        return;

    const TileAnimationData* tileAnim = tile->getAnimation(currentAnim);
    if(tileAnim == NULL)
        return;

    const TileAnimationFrameData* tileAnimFram = tileAnim->getFrame(currentFrame);
    if(tileAnimFram == NULL)
        return;

    sf::Vector2i positionTile = tileAnimFram->getPosition();

    m_floor = positionTile.y;
    m_side = positionTile.x;

    const sf::Texture *texture = tileAnimFram->getTexture();
    sf::Vector2f scale = tileAnimFram->getScale();

    m_size.x = (texture->getSize().x * scale.x) - CELL_SIZE_X;
    m_size.y = (texture->getSize().y * scale.y) - CELL_SIZE_Y;

    if (m_size.y < 0)
        m_size.y = 0;

    updatePosition();
}

void Cube::updatePosition()
{
    m_vposition = m_cell->getVPosition();

    int RELATIVE_X = m_vposition.x;
    int RELATIVE_Y = m_vposition.y;

    m_line1.setSize(sf::Vector2f(0,m_size.y));
    m_line2.setSize(sf::Vector2f(0,m_size.y));
    m_line3.setSize(sf::Vector2f(0,m_size.y));
    m_line4.setSize(sf::Vector2f(0,m_size.y));

    m_top.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y + m_floor + m_height2);
    m_bottom.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x, toScreenCoords(RELATIVE_X, RELATIVE_Y).y + m_floor + m_height2);
    m_line1.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x + CELL_SIZE_X/2, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y + CELL_SIZE_Y + m_floor + m_height2);
    m_line2.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x + CELL_SIZE_X, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y +CELL_SIZE_Y/2 + m_floor + m_height2);
    m_line3.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y +CELL_SIZE_Y/2 + m_floor + m_height2);
    m_line4.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x + CELL_SIZE_X/2, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y + m_floor + m_height2);

}

void Cube::setHeight(const int &height)
{
    m_height = height*(-1)+CELL_SIZE_Y;
    updatePosition();
}

/*
#include "Cube.h"
#include <QDebug>

Cube::Cube(MapManager *manager, int layer_id)
    : Graphic_Element(SYSTEM)
    , m_toShow(true)
    , m_manager(manager)
    , m_layers()
    , m_top()
    , m_bottom()
    , m_line1()
    , m_line2()
    , m_line3()
    , m_line4()
    , m_floor(0)
    , m_side(0)
    , m_size(0,0)
    , m_height2(0)
    , m_layer_focus(layer_id)
{
    GameLayer* layer1 = m_manager->addLayer(-2);
    if(layer1 == NULL)
    {
        qDebug() << "Impossible de creer le layer -2 dans " << __FILE__ << " ligne "<<__LINE__<<": id deja prise";
        exit(0);
    }
    layer1->setName("Cube");
    layer1->setSystem(true);
    layer1->setVisible(true);

    GameLayer* layer2 = m_manager->addLayer(-3);
    if(layer2 == NULL)
    {
        qDebug() << "Impossible de creer le layer -3 dans " << __FILE__ << " ligne "<<__LINE__<<": id deja prise";
        exit(0);
    }

    layer2->setName("Cube");
    layer2->setSystem(true);
    layer2->setVisible(true);

    m_layers.append(layer1);
    m_layers.append(layer2);

    m_manager->getCell(m_vposition).add(layer1->getId(),this);
    m_manager->getCell(m_vposition).add(layer2->getId(),this);

    m_top.setPointCount(4);
    m_top.setPoint(0, sf::Vector2f (CELL_SIZE_X/2, 0));
    m_top.setPoint(1, sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2));
    m_top.setPoint(2,sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y));
    m_top.setPoint(3,sf::Vector2f(0, CELL_SIZE_Y/2));
    m_top.setOutlineThickness(1);

    m_top.setOutlineColor(sf::Color(90,170,70,255));
    m_top.setFillColor(sf::Color(0,0,0,0));

    m_bottom.setPointCount(4);
    m_bottom.setPoint(0, sf::Vector2f (CELL_SIZE_X/2, 0));
    m_bottom.setPoint(1, sf::Vector2f(CELL_SIZE_X,CELL_SIZE_Y/2));
    m_bottom.setPoint(2,sf::Vector2f(CELL_SIZE_X/2, CELL_SIZE_Y));
    m_bottom.setPoint(3,sf::Vector2f(0, CELL_SIZE_Y/2));
    m_bottom.setOutlineThickness(1);

    m_bottom.setOutlineColor(sf::Color(90,170,70,255));
    m_bottom.setFillColor(sf::Color(0,0,0,0));

    m_line1.setOutlineColor(sf::Color(90,170,70,255));
    m_line1.setOutlineThickness(1);

    m_line2.setOutlineColor(sf::Color(90,170,70,255));
    m_line2.setOutlineThickness(1);

    m_line3.setOutlineColor(sf::Color(90,170,70,255));
    m_line3.setOutlineThickness(1);

    m_line4.setOutlineColor(sf::Color(90,170,70,255));
    m_line4.setOutlineThickness(1);

    updatePosition();
    updateLayers();
}

void Cube::setVisible (bool visible)
{
    m_visible = visible;

    m_layers[0]->setVisible(m_visible);
    m_layers[1]->setVisible(m_visible);

    m_toShow = 0;

    updateLayers();
}

void Cube::setVPosition (const sf::Vector2i &position)
{   
    m_manager->getCell(m_vposition).remove(m_layers[0]->getId(),false);
    m_manager->getCell(position).add(m_layers[0]->getId(),this);

    m_manager->getCell(m_vposition).remove(m_layers[1]->getId(),false);
    m_manager->getCell(position).add(m_layers[1]->getId(),this);
    m_vposition = position;

    updateLayers();
    updatePosition();
}

void Cube::show(sf::RenderTarget &render)
{
    if (!m_toShow)
    {
        render.draw(m_bottom);
        render.draw(m_line4);
        m_toShow = true;
    }
    else
    {
        render.draw(m_top);
        render.draw(m_line1);
        render.draw(m_line3);
        render.draw(m_line2);
        m_toShow = false;
    }
}


void Cube::updatePosition ()
{
    int RELATIVE_X = m_vposition.x;
    int RELATIVE_Y = m_vposition.y;

    m_line1.setSize(sf::Vector2f(0,m_size.y));
    m_line2.setSize(sf::Vector2f(0,m_size.y));
    m_line3.setSize(sf::Vector2f(0,m_size.y));
    m_line4.setSize(sf::Vector2f(0,m_size.y));

    m_top.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y + m_floor + m_height2);
    m_bottom.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x, toScreenCoords(RELATIVE_X, RELATIVE_Y).y + m_floor + m_height2);
    m_line1.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x + CELL_SIZE_X/2, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y + CELL_SIZE_Y + m_floor + m_height2);
    m_line2.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x + CELL_SIZE_X, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y +CELL_SIZE_Y/2 + m_floor + m_height2);
    m_line3.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y +CELL_SIZE_Y/2 + m_floor + m_height2);
    m_line4.setPosition(toScreenCoords(RELATIVE_X, RELATIVE_Y).x + CELL_SIZE_X/2, toScreenCoords(RELATIVE_X, RELATIVE_Y).y - m_size.y + m_floor + m_height2);

}

void Cube::setHeight(const int &height)
{
    m_height = height*(-1)+CELL_SIZE_Y;
    updatePosition();
}

void Cube::setParameters (const Cell& cell)
{
    const Tile* tile = cell.tile();
    m_floor = tile->getSecondFloor(cell.getCurrentAnim(),cell.getCurrentFrame());
    m_side = tile->getSecondSide(cell.getCurrentAnim(),cell.getCurrentFrame());

    const sf::Texture &texture = tile->getTexture(cell.getCurrentAnim(),cell.getCurrentFrame());
    const sf::Vector2f &scale = tile->getScale(cell.getCurrentAnim(),cell.getCurrentFrame());
    m_size.x = (texture.getSize().x * scale.x) - CELL_SIZE_X;
    m_size.y = (texture.getSize().y * scale.y) - CELL_SIZE_Y;

    if (m_size.y < 0)
        m_size.y = 0;

    updatePosition();
}

void Cube::updateLayers ()
{

    QList<int> order;
    foreach (const Game_Layer &layer, m_manager->getLayers())
    {
        if (layer.id != m_layers[0].id && layer.id != m_layers[1].id)
        {
            if (layer.id == m_layer_focus)
            {

                order<<m_layers[0].id;
                order<<layer.id;
                order<<m_layers[1].id;
            }

            else
              order<<layer.id;
        }
    }

    m_manager->setLayersOrder(order);

}
*/
