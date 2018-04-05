#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "Public.h"
#include "IdGenerator.h"

template <typename X, typename T>
class ManagerAbstract
{
    template <class TT> friend class ManagerID;
    template <class TT> friend class ManagerQString;
protected:
    ManagerAbstract()
        : m_data()
    {
    }

public:
    virtual ~ManagerAbstract()
    {
        clear();
    }

    T* get(X key)
    {
        return m_data[key];
    }

    const T* get(X key) const
    {
        return m_data[key];
    }

    virtual X getKeyObject(T* object)const = 0;
    virtual void removeKeyObject(X key) = 0;

    bool add(T* object)
    {
        if(m_data.find(getKeyObject(object)) == m_data.end())
        {
            m_data[getKeyObject(object)] = object;
            removeKeyObject(getKeyObject(object));
            return true;
        }
        else
            qDebug() << "tentative d'ajout d'un objet échoué";

        return false;
    }

    bool remove(X id)
    {
        typename QHash<X, T*>::iterator it = m_data.find(id);
        if(it != m_data.end())
        {
            delete it.value();
            m_data.erase(it);
            return true;
        }
        return false;
    }

    void clear()
    {
        typename QHash<X, T*>::iterator it = m_data.begin();
        typename QHash<X, T*>::iterator itEnd = m_data.end();
        for( ; it!= itEnd ; ++it)
            delete it.value();
        m_data.clear();
    }

    const QHash<X, T*> *data() const
    {
        return &m_data;
    }

    QHash<X, T*> *data()
    {
        return &m_data;
    }

    bool contains(X id)
    {
        return m_data.contains(id);
    }

protected:
    QHash<X, T*> m_data;
};

template <typename T>
class ManagerID : public ManagerAbstract<ID, T>
{
    template <class TT> friend class Manager;
    template <class TT> friend class ManagerType;
protected:
    ManagerID()
        : ManagerAbstract<ID, T>()
        , m_idGenerator()
    {
    }

    ID getKeyObject(T *object) const
    {
        return object->getId();
    }

    void removeKeyObject(ID key)
    {
        m_idGenerator.removeId(key);
    }

protected:
    ID getID()
    {
        return m_idGenerator.getId();
    }

protected:
    IdGenerator m_idGenerator;
};

template <typename T>
class ManagerQString : public ManagerAbstract<QString, T>
{
    template <class TT> friend class ManagerSimpleQString;
protected:
    ManagerQString()
        : ManagerAbstract<QString, T>()
    {
    }

    QString getKeyObject(T *object) const
    {
        return object->getQString();
    }

    void removeKeyObject(QString)
    {

    }
};

template<typename T>
class ManagerSimpleQString : public ManagerQString<T>
{
public:
    ManagerSimpleQString()
        : ManagerQString<T>()
    {}

    T* create(QString name)
    {
        QString n = name;
        T* o = createObjet(n);
        if(!add(o))
        {
            delete o;
            return NULL;
        }
        return o;
    }

protected:
    virtual T* createObjet(QString id) = 0;
};

template<typename T>
class Manager : public ManagerID<T>
{
public:
    Manager()
        : ManagerID<T>()
    {}

    T* create()
    {
        ID id = ManagerID<T>::getID();
        T* o = createObjet(id);
        if(!add(o))
        {
            delete o;
            return NULL;
        }
        return o;
    }

protected:
    virtual T* createObjet(ID id) = 0;
};

template<typename T>
class ManagerType : public ManagerID<T>
{
public:
    ManagerType()
        : ManagerID<T>()
    {}

    T* create(int type)
    {
        ID id = ManagerID<T>::getID();
        T* o = createObjet(id, type);
        if(!add(o))
        {
            delete o;
            return NULL;
        }
        return o;
    }

protected:
    virtual T* createObjet(ID id, int type) = 0;
};

#endif // MANAGER_HPP
