#ifndef GAMELAYER_H
#define GAMELAYER_H

#include "SYSTEM/Manager.h"
#include "SYSTEM/Singleton.h"

class GameLayer
{
    friend class GameLayerSystem;
protected:
    GameLayer(ID id = -1);

public:
    bool isVisible() const;
    bool isSystem() const;
    int getId() const;
    QString getName() const;

    void setVisible(bool visible);
    void setSystem(bool system);
    void setId(int id);
    void setName(QString name);

    void setPosition(int position);
    int getPosition() const;

    bool operator!=(const GameLayer &compare) const;
    bool operator<(const GameLayer &compare) const;

    bool canDeleteContent() const;
    void setDeleteContent(bool b);

private:
    bool m_visible;
    bool m_system;
    ID m_id;
    QString m_name;
    int m_position;
    bool m_deleteContent;
};

class GameLayerSystem
{
public:
    GameLayerSystem();
    ~GameLayerSystem();

    GameLayer* add(ID id);
    GameLayer* add(ID id, int position);
    bool remove(ID id);

    const QList<GameLayer*>* getOrderLayer() const;

    void moveUp(ID id);
    void moveDown(ID id);

    void clear();

    const QMap<int, GameLayer*>* getLayers() const;

    int size() const;

    GameLayer* getLayer(ID id);
    const GameLayer* getLayer(ID id) const;

private:
    void updateOrder();

private:
    QMap<int, GameLayer*> m_layers;
    QList<GameLayer*> m_order;
    int m_nextPosition;
};


#endif // GAMELAYER_H
