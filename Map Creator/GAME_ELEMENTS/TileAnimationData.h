#ifndef TILEANIMATIONDATA_H
#define TILEANIMATIONDATA_H

#include <QHash>
#include <QList>

#include <SFML/Graphics/Texture.hpp>
#include "SYSTEM/Public.h"

class TileAnimationFrameData
{
public:
    TileAnimationFrameData(int frameInterval = 10, sf::Texture *texture = NULL, const sf::Vector2i &position = sf::Vector2i(0,0), const sf::Vector2f &scale = sf::Vector2f(1,1));
    ~TileAnimationFrameData();

    int getTimePosition() const;
    void setTimePosition(int time);
    void increaseTimePosition();
    void decreaseTimePosition();

    int getFrameInterval() const;
    const sf::Texture* getTexture() const;
    sf::Vector2i getPosition() const;
    sf::Vector2f getScale() const;

    void setFrameInterval(int frameInterval);
    void setTexture(sf::Texture *texture);
    void setPosition(sf::Vector2i position);
    void setScale(sf::Vector2f scale);

private:
    int m_timePosition;

    int m_frameInterval;
    sf::Texture *m_texture;
    sf::Vector2i m_position;
    sf::Vector2f m_scale;
};

class TileAnimationData
{
public:
    TileAnimationData(QString name = DEFAULT_ANIMATION);
    ~TileAnimationData();

    void clear();

    void setName(QString name);
    QString name() const;

    void setRestarting(bool restart);
    bool isRestarting() const;

    TileAnimationFrameData* addFrame(sf::Texture* texture);
    bool insertFrameAfter(int numberFrame, TileAnimationFrameData *data);
    bool insertFrameBefore(int numberFrame, TileAnimationFrameData *data);
    int moveFrameToNext(int numberFrame);
    int moveFrameToPrevious(int numberFrame);

    bool deleteFrame(int numberFrame);

    TileAnimationFrameData* getFrame(int numberFrame);
    const TileAnimationFrameData* getFrame(int numberFrame) const;

    const QList<TileAnimationFrameData*>* datas() const;
    QList<TileAnimationFrameData*>* datas();

    int getNbFrame() const;

private:
    QList<TileAnimationFrameData*>::iterator getIterator(int numberFrame);
    int getIndex(int numberFrame);

private:
    QString m_name;
    bool m_restart;

    QList<TileAnimationFrameData*> m_datas;
};

#endif // TILEANIMATIONDATA_H
