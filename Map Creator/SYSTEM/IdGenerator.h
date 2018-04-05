#ifndef IDGENERATOR_H
#define IDGENERATOR_H

#include <list>
#include "Public.h"

class IdGenerator
{
public:
    IdGenerator(ID min = 0, ID max = 128);

    // fonction qui recupere un ID libre dans m_ids et le supprime
    ID getId();

    // fonction qui rajoute un id dans m_ids
    void addId(const ID &id);

    // fonction qui supprime l'id dans m_ids
    void removeId(const ID &id);

protected:
    // fonction qui agrandi la liste des id libre
    void grow();

protected:
    ID m_min;
    ID m_currentMax;
    QList<ID> m_ids;
};


#endif // IDGENERATOR_H
