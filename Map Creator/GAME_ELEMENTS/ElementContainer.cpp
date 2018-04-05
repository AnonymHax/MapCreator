#include "ElementContainer.h"
#include "Light.h"

Container::Container() 
    : m_height(0)
    , m_collision(false)
    , m_data()
    , m_position(sf::Vector2i(-1,-1))
{
}

Container::~Container ()
{
    /*QList<Graphic_Element*> deletedPointers;

    QMapIterator<int,Graphic_Element*> i(m_data);
    while (i.hasNext())
    {
        i.next();
        if (!deletedPointers.contains(i.value()))
        {
            deletedPointers<<i.value();
            Graphic_Element *p = i.value();
            delete p;
            p = NULL;
        }
    }
    */
    m_data.clear();
}

bool Container::operator !=(const Container &compare)
{
    if (compare.m_position == m_position &&
        compare.m_height == m_height &&
        compare.m_data == m_data)
          return false;

    return true;
}

bool Container::operator ==(const Container &compare)
{
    return !(*this != compare);
}

void Container::update ()
{}

void Container::setVPosition (const int &x, const int &y)
{
    setVPosition(sf::Vector2i(x,y));
}

void Container::setVPosition (const sf::Vector2i &position)
{
    m_position = position;
}

sf::Vector2i Container::getVPosition() const
{
    return m_position;
}

void Container::setHeight(const float &height)
{
    QMapIterator<int, Graphic_Element*> iterator1(m_data);
    while (iterator1.hasNext())
    {
        iterator1.next();
        iterator1.value()->setHeight(iterator1.value()->getHeight()-m_height+height);
    }

    m_height = height;
}

void Container::setCollision(const bool &collision)
{
    m_collision = collision;
}

int Container::getHeight () const
{
    return m_height;
}

Light *Container::light(int layer_id)
{
    if (!m_data.contains(layer_id) || m_data[layer_id]->getType() != LIGHT)
        return NULL;

    return dynamic_cast<Light*>(m_data[layer_id]);
}

Cell *Container::cell(int layer_id)
{
    if (!m_data.contains(layer_id) || m_data[layer_id]->getType() != CELL)
        return NULL;

    return dynamic_cast<Cell*>(m_data[layer_id]);
}

QList<Graphic_Element*> Container::datas()
{
    QList<Graphic_Element*> l;
    foreach(Graphic_Element* ge, m_data)
        l << ge;

    return l;
}

Graphic_Element* Container::data (int layer_id)
{
    if (m_data.contains(layer_id))
        return m_data[layer_id];

    else
        qDebug()<<"ERREUR: L'objet demandé n'existe pas";
}

int Container::getTop(const int &layer) const
{
    int top = m_height;

    if (m_data.contains(layer))
    {
        QMap<int, Graphic_Element*>::const_iterator element = m_data.constBegin();
        while (element != m_data.constEnd()) {

            if (element.value()->getType() == CELL)
            {
                const Cell &cell = dynamic_cast<const Cell&>(*element.value());
                const TileAnimationFrameData *tafd = cell.tile()->getAnimationFrame(cell.getCurrentAnim(), cell.getCurrentFrame());
                if(tafd == NULL)
                    continue;

                top += tafd->getTexture()->getSize().y
                       + tafd->getPosition().y
                       - CELL_SIZE_Y;
            }

            if (element.key() == layer)
                break;

            element++;
        }
    }

    return top;
}

bool Container::isCollision() const
{
    return m_collision;
}


void Container::addElement(int layer_id, Graphic_Element *element)
{
    if (!m_data.contains(layer_id))
    {
        m_data.insert(layer_id,element);
        element->setVPosition(m_position);
    }
    else
        qDebug()<<"ERREUR: L'element existe deja sous ce layer";
}

Graphic_Element* Container::remove(int layer_id)
{
   Graphic_Element* element = m_data[layer_id];

   m_data.remove(layer_id);

   return element;
}

bool Container::exist (int layer_id) const
{
    if (m_data.contains(layer_id))
        return true;

    return false;
}

bool Container::isEmpty () const
{    
    if (m_data.size() <= 1) // Quand il ne reste plus que la classe collision le container est vide
        return true;

   return false;
}
