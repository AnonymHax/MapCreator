#include "MapManager.h"
#include "TileManager.h"

MapManager::MapManager()
{
    m_mapExist = false;
    m_mapName = "no name";
}

MapManager::~MapManager ()
{
    foreach(Container* c, m_map)
        delete c;
    m_map.clear();
}

void MapManager::setName(const QString &name)
{
    m_mapName = name;
}

QString MapManager::getName() const
{
    return m_mapName;
}

void MapManager::createMap (const sf::Vector2i &map_size)
{
    m_mapSize = map_size;

    if (m_mapExist)
        deleteMap ();

    m_mapExist = true;
}

void MapManager::deleteMap ()
{
    m_map.clear();
}

bool MapManager::exist(const int &x, const int &y) const
{
    return exist(sf::Vector2i(x,y));
}

bool MapManager::exist(const sf::Vector2i &position) const
{
    return (m_map.find(position) != m_map.end());
}

bool MapManager::inProportions (const int &x, const int &y) const
{
    return inProportions(sf::Vector2i(x,y));
}

bool MapManager::inProportions (const sf::Vector2i &position) const
{
    if (mapSize().x - 1 >= position.x &&
            -1 < position.x &&
            mapSize().y - 1 >= position.y &&
            -1 < position.y)
        return true;

    else
        return false;
}


bool MapManager::saveMap(const QString &path)
{
    /*   if (m_mapExist == true)
    {
        QFile file(path);
        if  (file.open(QIODevice::WriteOnly))
        {

            QVariantMap list;
         QVariantList tile;


            QMap <int, Tile*> i;
            foreach (i, m_tiles)
            {

                foreach (Tile *i2, i)
                {

                    if (i2->getLayer() != SYSTEM)
                    {
                        list.clear();
                        list.insert("nbFrames", i2->getNbFrames());
                        int frames = 0;
                        while (frames != i2->getNbFrames())
                        {
                            QByteArray ba;
                            QBuffer buffer(&ba);
                            buffer.open(QIODevice::WriteOnly);
                            i2->getImage(frames).save(&buffer, "PNG"); // writes image into ba in PNG format
                            QString image_encoded = QString(ba.toBase64());

                            list.insert("image_"+toString(frames), image_encoded);
                            list.insert("second_floor_"+toString(frames), i2->getSecondFloor(frames));
                            list.insert("second_side_"+toString(frames), i2->getSecondSide(frames));
                            list.insert("scale_x_"+toString(frames), toString(i2->getScale(frames).x));
                            list.insert("scale_y_"+toString(frames), toString (i2->getScale(frames).y));

                            frames++;
                        }

                    list.insert("layer", i2->getLayer());
                    list.insert("id", i2->getName());
                    list.insert("frame_interval",i2->getFrameInterval());
                    list.insert("frame_restart",i2->getFrameRestart());

                    tile << list;
                    }
                 }
          }

           QVariantMap cell;
            QVariantList map;

            QMap < int, Map > x_iterator;
            foreach (x_iterator, m_map)
            {
                foreach (Map y_iterator, x_iterator)
                {
                    cell.clear();

                    cell.insert("x",y_iterator.getVPosition().x);
                    cell.insert("y",y_iterator.getVPosition().y);

                    if (y_iterator.collisionExist())
                   { cell.insert("collision", y_iterator.collision().isCollision());
                    cell.insert("collision_height", y_iterator.collision().getHeight());}


                    if (y_iterator.groundExist())
                   {cell.insert("ground_id",y_iterator.ground().getName());
                    cell.insert("ground_scale_x",y_iterator.ground().getScale().x);
                    cell.insert("ground_scale_y",y_iterator.ground().getScale().y);
                    cell.insert("ground_height", y_iterator.ground().getHeight());}

                    if (y_iterator.objectExist())
                    {cell.insert("object_id",y_iterator.object().getName());
                    cell.insert("object_scale_x",y_iterator.object().getScale().x);
                    cell.insert("object_scale_y",y_iterator.object().getScale().y);
                    cell.insert("object_height", y_iterator.object().getHeight());}

                    if (y_iterator.superpositionExist())
                   {cell.insert("superposition_id",y_iterator.superposition().getName());
                   cell.insert("superposition_scale_x",y_iterator.superposition().getScale().x);
                   cell.insert("superposition_scale_y",y_iterator.superposition().getScale().y);
                   cell.insert("superposition_height", y_iterator.superposition().getHeight());}

                    if (y_iterator.lightExist())
                    {
                        cell.insert("light_exist", true);
                        cell.insert("light_radius",y_iterator.light().GetRadius());
                        cell.insert("light_intensity",y_iterator.light().GetIntensity());
                        cell.insert("light_quality",y_iterator.light().GetQuality());
                        cell.insert("light_color_red",y_iterator.light().GetColor().r);
                        cell.insert("light_color_green",y_iterator.light().GetColor().g);
                        cell.insert("light_color_blue",y_iterator.light().GetColor().b);
                         cell.insert("light_height", y_iterator.light().GetHeight());
                    }

                   map << cell;
                }

            }


            QVariantMap size;
            size.insert("x", m_mapSize.x);
            size.insert("y", m_mapSize.y);


             QVariantMap container;

             container.insert("tiles", tile);
             container.insert("size", size);
            container.insert("map",map);

                QJson::Serializer serializer;
                file.write(qCompress(serializer.serialize(container)));


             return true;
        }
        else
       return false;

         file.close();

    } */

}

bool MapManager::mapExist() const
{
    return m_mapExist;
}

bool MapManager::loadMap(const QString &path)
{

    /*  loadTiles(path, true);
    QFile file (path);
    file.open(QIODevice::ReadOnly);

    bool ok;


      QJson::Parser parser;
    QVariantMap result = parser.parse (qUncompress(file.readAll()), &ok).toMap();
    if (ok) {
    file.close();

    QVariantMap size = result["size"].toMap();
    createMap( sf::Vector2i (size["x"].toInt(),size["y"].toInt()) );
    foreach(QVariant record, result["map"].toList())
    {
        QVariantMap nestedMap = record.toMap();
        addCell(nestedMap["x"].toInt(), nestedMap["y"].toInt());

        m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].collision().setCollision(nestedMap["collision"].toBool());
        m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].collision().setHeight(nestedMap["collision_height"].toInt());
        m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].setHeight(nestedMap["collision_height"].toInt());


        if (nestedMap["ground_id"].toString() != "")
        {m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].ground().setid(getGroundid(nestedMap["ground_id"].toString()));
        m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].ground().setHeight(nestedMap["ground_height"].toInt());}

        if (nestedMap["object_id"].toString() != "")
       {m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].object().setid(getObjectid(nestedMap["object_id"].toString()));
        m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].object().setHeight(nestedMap["object_height"].toInt());}

        if (nestedMap["superposition_id"].toString() != "")
        {m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].superposition().setid(getSuperpositionid(nestedMap["superposition_id"].toString()));
        m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].superposition().setHeight(nestedMap["superposition_height"].toInt());}


        if (nestedMap["light_exist"].toBool() == true)
        {
            m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].light().SetRadius(nestedMap["light_radius"].toFloat());
            m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].light().SetIntensity(nestedMap["light_intensity"].toInt());
            m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].light().SetQuality(nestedMap["light_quality"].toInt());
            m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].light().SetColor(sf::Color(nestedMap["light_color_red"].toInt(),
                                                                                              nestedMap["light_color_green"].toInt(),
                                                                                              nestedMap["light_color_blue"].toInt()));
             m_map[nestedMap["x"].toInt()][nestedMap["y"].toInt()].light().SetHeight(nestedMap["light_height"].toFloat());
        }

    }

    return true;
    }
    else
    return false; */
}

sf::Vector2i MapManager::mapSize () const
{
    return m_mapSize;
}

void MapManager::addCell (int x, int y)
{
    addCell(sf::Vector2i(x,y));
}

void MapManager::addCell (const sf::Vector2i &position)
{
    if (!exist (position))
    {
        m_map.insert(position, new Container());
        m_map[position]->setVPosition(position.x, position.y);
        m_map[position]->addElement(-1,new Collision (position.x, position.y));
    }
}

void MapManager::removeCell (int x, int y)
{
    removeCell(sf::Vector2i(x,y));
}

void MapManager::removeCell (const sf::Vector2i &position)
{
    if(m_map.contains(position))
    {
        Container *container = m_map[position];
        QList<Graphic_Element*> l = container->datas();
        foreach(Graphic_Element* ge, l)
            delete ge;

        delete m_map[position];
        m_map.remove(position);
    }
}

void MapManager::removeCell(int x, int y, int layer_id, bool free_space)
{
    removeCell(sf::Vector2i(x,y),layer_id, free_space);
}

void MapManager::removeCell(const sf::Vector2i &position, int layer_id, bool free_space)
{
    if(m_map.contains(position))
    {
        Container *container = m_map[position];

        Graphic_Element *ge = container->remove(layer_id);
        if(free_space)
            delete ge;

        if (m_map[position]->isEmpty())
            m_map.remove(position);
    }
}

const QList<GameLayer*> *MapManager::getLayersOrder() const
{
    return m_layers.getOrderLayer();
}

GameLayer* MapManager::getLayer(ID layer_id)
{
    return m_layers.getLayer(layer_id);
}

GameLayer* MapManager::addLayer(ID id)
{
    return m_layers.add(id);
}

GameLayer* MapManager::addLayer(ID id, QString name, bool visible, bool system)
{
    GameLayer *layer = m_layers.add(id);
    layer->setName(name);
    layer->setVisible(visible);
    layer->setSystem(system);

    return layer;
}

bool MapManager::removeLayer(ID id)
{
    foreach(Container* c, m_map)
    {
        if(c->exist(id))
            removeCell(c->getVPosition(), id);
    }
    return m_layers.remove(id);
}


void MapManager::removeAllLayers ()
{
    m_layers.clear();
}

Container* MapManager::getCell (int x, int y, bool initialize)
{
    return getCell(sf::Vector2i(x,y), initialize);
}

Container* MapManager::getCell(const sf::Vector2i &position, bool initialize)
{
    if (initialize && !exist(position))
        addCell (position);

    return m_map[position];
}

bool MapManager::loadTiles(const QString &file_path, const bool clear_tiles)
{
    /* if (clear_tiles)
     {m_tiles.clear();
    m_Ground.clear();
    m_Object.clear();
    m_Superposition.clear();}

    QFile *file = new QFile (file_path);
    file->open(QIODevice::ReadOnly);
    QJson::Parser parser;
    QByteArray uncompressedData = qUncompress(file->readAll());
    file->close();
    bool ok;

    QVariantMap result = parser.parse (uncompressedData, &ok).toMap();
    if (ok) {

   loadSystem();


    foreach(QVariant record, result["tiles"].toList())
    {
        QVariantMap nestedMap = record.toMap();


            int nbFrames = nestedMap["nbFrames"].toInt();
            int frames = 0;
            QList<int> secondFloors;
            QList<int> secondSides;
            QList<QImage> images;
            QList<sf::Vector2f> scales;
            QByteArray image_decoded;
            while (frames != nbFrames)
            {
                image_decoded = QByteArray::fromBase64(nestedMap["image_"+toString(frames)].toByteArray());
             images << QImage::fromData(image_decoded, "PNG");


             scales << sf::Vector2f (toFloat(nestedMap["scale_x_"+toString(frames)].toString()),toFloat(nestedMap["scale_y_"+toString(frames)].toString()));
             secondFloors << nestedMap["second_floor_"+toString(frames)].toInt();
             secondSides << nestedMap["second_side_"+toString(frames)].toInt();

             frames++;
            }

             addTile(nestedMap["layer"].toInt(),nestedMap["id"].toString(),images,nestedMap["frame_interval"].toInt(), nestedMap["frame_restart"].toInt(), secondFloors,secondSides, scales);
    }
    return true;
    }

    else
        return false; */
}

bool MapManager::saveTiles(const QString &file_path)
{
    /*  QFile file(file_path);
    if  (file.open(QIODevice::WriteOnly))
    {

        QVariantMap list;
     QVariantList tile;


        QMap <int, Tile*> i;
        foreach (i, m_tiles)
        {

            foreach (Tile *i2, i)
            {

                if (i2->getLayer() != SYSTEM)
                {

                 list.clear();

                list.insert("nbFrames", i2->getNbFrames());
                int frames = 0;
                while (frames != i2->getNbFrames())
                {
                    QByteArray ba;
                    QBuffer buffer(&ba);
                    buffer.open(QIODevice::WriteOnly);
                    i2->getImage(frames).save(&buffer, "PNG"); // writes image into ba in PNG format
                    QString image_encoded = QString(ba.toBase64());

                    list.insert("image_"+toString(frames), image_encoded);
                    list.insert("second_floor_"+toString(frames), i2->getSecondFloor(frames));
                    list.insert("second_side_"+toString(frames), i2->getSecondSide(frames));
                    list.insert("scale_x_"+toString(frames), toString(i2->getScale(frames).x));
                    list.insert("scale_y_"+toString(frames), toString (i2->getScale(frames).y));

                    frames++;
                }

                list.insert("layer", i2->getLayer());
                list.insert("id", i2->getName());
                list.insert("frame_interval",i2->getFrameInterval());
                list.insert("frame_restart",i2->getFrameRestart());

                tile << list;
                }
             }
      }



         QVariantMap container;

         container.insert("tiles", tile);

            QJson::Serializer serializer;
            file.write(qCompress(serializer.serialize(container)));


         return true;
    }
    else
   return false;

     file.close(); */
}

bool MapManager::removeTile(const int &id)
{
    if (TileManagerSingleton::getInstance()->contains(id))
    {
        foreach(Container *container, m_map)
        {
            const QList<GameLayer*>* layers = m_layers.getOrderLayer();
            foreach(GameLayer* gl, *layers)
            {
                ID gameLayerId = gl->getId();
                if (container->exist(gameLayerId)
                     && container->data(gameLayerId)->getType()== CELL
                     && container->cell(gameLayerId)->getId() == id)
                {
                    removeCell(container->getVPosition(),gameLayerId);
                }
            }
        }

        TileManagerSingleton::getInstance()->remove(id);

        return true;
    }

    return false;
}

GameLayerSystem *MapManager::getLayerSystem()
{
    return &m_layers;
}
