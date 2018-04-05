#ifndef TILE_H
#define TILE_H

#include "SYSTEM/Public.h"
#include "GAME_ELEMENTS/TileAnimationData.h"

class Tile
{
    friend class TileManager;

protected:
    Tile(int id);

public:
    ~Tile();

    void setName (QString name);
    void setDefaultAnim (QString animation);

    int getId () const;
    QString getName() const;
    QString getDefaultAnim () const;
    int getNbFrames (const QString &animation) const;
    int getNbAnimation() const;

    bool contains (const QString &animation) const;
    QStringList getAnimNames () const;

    TileAnimationData* addAnimation(QString name);

    const TileAnimationData* getAnimation(QString name) const;
    TileAnimationData* getAnimation(QString name);

    const TileAnimationFrameData* getAnimationFrame(QString name, int frame) const;
    TileAnimationFrameData* getAnimationFrame(QString name, int frame);

    const QHash<QString, TileAnimationData*>* getAnimations()const;
    QHash<QString, TileAnimationData*>* getAnimations();
private:

    int m_id;
    QString m_name;
    QString m_defaultAnimation;

    QHash<QString, TileAnimationData*> m_animations;
};

#endif // TILE_H
