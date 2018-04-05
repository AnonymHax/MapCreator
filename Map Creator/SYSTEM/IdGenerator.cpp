#include "IdGenerator.h"

IdGenerator::IdGenerator(ID min, ID max)
    : m_min(min)
    , m_currentMax(min+max)
    , m_ids()
{
    // on ajoute des id libre dans la liste
    for(int i = m_currentMax ; i >= static_cast<int>(min) ; i--)
    {
        if( static_cast<ID>(i) != NO_VALID_ID)
           m_ids.append(i);
    }
}

ID IdGenerator::getId()
{
    if(m_ids.size() == 0)
        grow();

    ID id = m_ids.back();
    m_ids.pop_back();

    return id;
}

void IdGenerator::addId(const ID &id)
{
    if( id != NO_VALID_ID)
        m_ids.append(id);
}

void IdGenerator::removeId(const ID &id)
{
    while(m_currentMax < id)
        grow();

    QList<ID>::iterator it = m_ids.begin();
    QList<ID>::iterator itEnd = m_ids.end();
    for( ; it != itEnd ; ++it)
    {
        if( *it == id)
        {
            m_ids.erase(it);
            return;
        }
    }
}

void IdGenerator::grow()
{
    // on calcul le nouveau max
    int newMax = m_currentMax*2;
    // on rajoute les ids de nouveau max a currentMax
    for(int i = newMax ; i >= static_cast<int>(m_currentMax)+1 ; i--)
        if( static_cast<ID>(i) != NO_VALID_ID)
            m_ids.append(i);

    m_currentMax = newMax;
}
