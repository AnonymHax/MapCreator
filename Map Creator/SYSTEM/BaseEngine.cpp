#include "BaseEngine.h"

BaseEngine::BaseEngine(QWidget *Parent, const QPoint &Position, const QSize &Size)
    : QWidget (Parent)
{
    m_tileId = -1;

    sf::Vector2i m_renderSize;
    m_renderSize.x = Size.width();
    m_renderSize.y = Size.height();

    m_map = new MapManager ();

    m_render = new Render (this, Position, Size);
    m_mapRender = new MapRender (m_map, m_renderSize);
    m_guiRender = new ObjectLayer (m_renderSize);
    m_fps = new FPS();
    m_global = new MapGlobal (m_map);

    m_render->add(m_mapRender);
    m_render->add(m_guiRender);
    m_guiRender->add(m_fps);
    m_guiRender->add(m_global);

    m_fps->setBackgroundColor(sf::Color::Blue);
    m_global->setBackgroundColor(sf::Color(165,165,165, 255));
    m_global->setPosition(sf::Vector2i(m_render->Object::getSize().x-m_global->getSize().x,0));

    m_selector= new Selector();

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect (this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(winContextMenu(QPoint)));
    m_contextMenu = new QMenu (this);

    m_tool = TOOL_NOTHING;

    m_lastMouseVPosition.x = -1;
    m_lastMouseVPosition.y = -1;
    m_lastCollision.x = 0;
    m_lastCollision.y = 0;

    m_actualMouseHeight = 0;
    m_isLocked = false;

    QObject::connect(m_mapRender, SIGNAL(mouseMoveEvent(sf::Vector2i)), this, SLOT(mouseMoving(sf::Vector2i)));
    QObject::connect(m_mapRender, SIGNAL(mousePressEvent(MOUSE,sf::Vector2i)), this, SLOT(mouseClicking(MOUSE, sf::Vector2i)));

    m_lightColor = sf::Color(255,255,255);
    m_lightRadius = 200;
    m_lightQuality = 30;
    m_lightAngle = 0;
    m_lightOpeningAngle = 360;
    m_lightIntensity = 150;
}

BaseEngine::~BaseEngine()
{
    delete m_mapRender;
    delete m_fps;
    delete m_global;
    delete m_guiRender;
    delete m_render;
    delete m_map;
    delete m_contextMenu;
    delete m_selector;
}

MapManager* BaseEngine::getManager ()
{
    return m_map;
}

MapRender *BaseEngine::getRender()
{
    return m_mapRender;
}

void BaseEngine::selection()
{
    if (m_layerFocus > -1)
    {
        if (m_tool == TOOL_PLACE)
            tool_place ();
        if (m_tool == TOOL_DELETE)
            tool_delete();
        if (m_tool == TOOL_COLLISION)
            tool_collision();
        if (m_tool == TOOL_HEIGHT)
            tool_height();
        if (m_tool == TOOL_LIGHT)
            tool_light();
    }
    if (m_tool == TOOL_MOVE)
        tool_move();
}

void BaseEngine::tool_light()
{
    if (m_map->mapExist())
    {
        updateSelector();

        for (int i= 0; i != m_lastSelected.size(); i++)
        {
            //map->getCell(m_lastSelected[i].x, m_lastSelected[i].y).object().setTransparent();
        }
        if (m_mouse.isButtonPressed(sf::Mouse::Left))
        {
            if (m_map->inProportions(m_selector->getVPosition()))
            {
                if (m_map->exist(m_selector->getVPosition()))

                {
                    Light light;
                    light.setColor(m_lightColor);
                    light.setIntensity(m_lightIntensity);
                    light.setRadius(m_lightRadius);
                    light.setQuality(m_lightQuality);
                    //light.setAngle(m_lightAngle);
                    //light.setOpeningAngle(m_lightOpeningAngle);
                    light.setVPosition(m_selector->getVPosition());

                    Container *container = m_map->getCell(m_selector->getVPosition());
                    if(container == NULL)
                        return;

                    Light *lightTmp = container->light(m_layerFocus);
                    if(lightTmp == NULL)
                    {
                        lightTmp = new Light();
                        container->addElement(m_layerFocus, lightTmp);
                    }

                    if (light != *(lightTmp))
                    {
                        saveBackwardCell(container);

                        lightTmp->setColor(m_lightColor);
                        lightTmp->setIntensity(m_lightIntensity);
                        lightTmp->setRadius(m_lightRadius);
                        lightTmp->setQuality(m_lightQuality);
                        //map->getCell(m_selector->getVPosition()).light(m_layerFocus).setAngle(m_lightAngle);
                        //map->getCell(m_selector->getVPosition()).light(m_layerFocus).setOpeningAngle(m_lightOpeningAngle);
                        lightTmp->setVPosition(m_selector->getVPosition());
                    }
                }

                else
                {
                    Container *container = m_map->getCell(m_selector->getVPosition());
                    if(container == NULL)
                        return;

                    Light *lightTmp = container->light(m_layerFocus);
                    if(lightTmp == NULL)
                    {
                        lightTmp = new Light();
                        container->addElement(m_layerFocus, lightTmp);
                    }

                    saveBackwardCell(container);

                    lightTmp->setColor(m_lightColor);
                    lightTmp->setIntensity(m_lightIntensity);
                    lightTmp->setRadius(m_lightRadius);
                    lightTmp->setQuality(m_lightQuality);
                    //map->getCell(m_selector->getVPosition()).light(m_layerFocus).setAngle(m_lightAngle);
                    //map->getCell(m_selector->getVPosition()).light(m_layerFocus).setOpeningAngle(m_lightOpeningAngle);
                    lightTmp->setVPosition(m_selector->getVPosition());
                }
            }
        }
    }
}

void BaseEngine::tool_move()
{
    sf::Vector2f _move = m_mapRender->getViewPosition()
            -sf::Vector2f(m_mouseMove.x/m_mapRender->getZoom(),
                          m_mouseMove.y/m_mapRender->getZoom());

    if (m_mouse.isButtonPressed(sf::Mouse::Left))
        m_mapRender->setViewPosition(_move);

    emit mapMoved();
}

void BaseEngine::tool_place ()
{
    if (m_map->mapExist() && m_tileId != -1)
    {
        updateSelector();

        if (m_mouse.isButtonPressed(sf::Mouse::Left))
        {
            if (m_map->inProportions(m_selector->getVPosition()))
            {
                Container *container = m_map->getCell(m_selector->getVPosition());
                if(container == NULL)
                    return;

                saveBackwardCell(container);
                Cell *cell = container->cell(m_layerFocus);
                if(cell == NULL)
                {
                    cell = new Cell();
                    container->addElement(m_layerFocus, cell);
                }

                cell->setId(m_tileId);
                cell->setHeight(cell->getHeight());
            }
        }
    }
}

void BaseEngine::tool_delete ()
{
    if (m_map->mapExist())
    {
        updateSelector();

        if (m_mouse.isButtonPressed(sf::Mouse::Left))
        {

            if (m_map->exist(m_selector->getVPosition()))
            {
                saveBackwardCell(m_map->getCell(m_selector->getVPosition()));

                m_map->removeCell(m_selector->getVPosition(),m_layerFocus);
            }
        }
    }
}


void BaseEngine::setTool (TOOL tool)
{
    m_tool = tool;
}

void BaseEngine::setTileChoice(int id)
{
    m_tileId = id;
}

void BaseEngine::mouseClicking(MOUSE mouse_button, sf::Vector2i position)
{
    m_mousePosition = position;
    selection();
}

void BaseEngine::tool_collision()
{
    /*  if (m_mapExist())
    {

        updateSelector();

     if (mouse.isButtonPressed(sf::Mouse::Left))
        {
         if (exist(m_selector->getVPosition()))
         {
             if (lastCollision != selector->getVPosition())
              {saveBackwardCell(m_map->getCell(m_selector->getVPosition()));
              m_map->getCell(m_selector->getVPosition().x,selector->getVPosition().y).collision().setCollision ();
               lastCollision = selector->getVPosition();}
         }
     }

     else
         lastCollision = sf::Vector2i(-1,-1);
    }*/
}



void BaseEngine::mouseMoving(sf::Vector2i mouse_pos)
{
    m_mouseMove = mouse_pos-m_mousePosition;
    m_mousePosition = mouse_pos;
    selection();
}

void BaseEngine::tool_height ()
{
    if (m_map->mapExist())
    {       
        if (m_isLocked == false)
            updateSelector();

        if (m_mouse.isButtonPressed(sf::Mouse::Left))
        {
            if (m_isLocked == false)
            {
                if (m_map->exist(m_selector->getVPosition()))
                {
                    m_isLocked = true;
                    m_actualMouseHeight = m_mapRender->mouseToViewCoords(m_mousePosition).y;
                    m_lockedCell = m_selector->getVPosition();
                    m_begMouseHeight = m_map->getCell(m_lockedCell)->getHeight();
                    saveBackwardCell(m_map->getCell(m_selector->getVPosition()));
                }
            }

            else
            {
                m_map->getCell(m_lockedCell)->setHeight(m_mapRender->mouseToViewCoords(m_mousePosition).y - m_actualMouseHeight + m_begMouseHeight);
                m_selector->setVPosition(m_map->getCell(m_lockedCell));
            }
        }

        else
            m_isLocked = false;
    }
}

void BaseEngine::resetEngine ()
{
    m_mapRender->resetView();
    m_lastMouseVPosition.x = -1;
    m_lastMouseVPosition.y = -1;
    m_backwardCells.clear();
    m_forwardCells.clear();
}

void BaseEngine::wheelEvent(QWheelEvent * event)
{
    event->accept();
    if(event->delta() > -1)
        m_mapRender->setZoom (m_mapRender->getZoom()+POSITIVE_ZOOM);

    else
        m_mapRender->setZoom (m_mapRender->getZoom()+NEGATIVE_ZOOM);
}

void BaseEngine::setLight (int radius, int quality, int intensity, QColor color, float opening_angle = 360, float angle = 0)
{
    m_lightRadius = radius;
    m_lightQuality = quality;
    m_lightOpeningAngle = opening_angle;
    m_lightAngle = angle;
    m_lightIntensity = intensity;
    m_lightColor = sf::Color (color.red(), color.green(), color.blue(), color.alpha());
}

void BaseEngine::saveBackwardCell(const Container *cell, bool clear_forward)
{
    /* if (clear_forward)
         m_forwardCells.clear();

     if (m_backwardCells.isEmpty() || m_backwardCells.last() != cell)
         m_backwardCells << cell;


    if (m_backwardCells.size() > FORWARD_BUFFER)
        m_backwardCells.removeFirst();*/
}

void BaseEngine::loadLastCell()
{
    /*
     if (!m_backwardCells.isEmpty())
     {

         saveForwardCell(m_map->getCell(m_backwardCells.last().getVPosition()));

         if (m_backwardCells.last().groundExist() || m_backwardCells.last().objectExist() || m_backwardCells.last().superpositionExist() || m_backwardCells.last().lightExist())
      { m_map->getCell (m_backwardCells.last().getVPosition()).setVPosition(m_backwardCells.last().getVPosition());

     if (m_backwardCells.last().groundExist())
   {map->getCell (m_backwardCells.last().getVPosition()).ground().setType(m_backwardCells.last().ground().getType());
    m_map->getCell (m_backwardCells.last().getVPosition()).ground().setHeight(m_backwardCells.last().ground().getHeight());}

     if (m_map->getCell(m_backwardCells.last().getVPosition()).groundExist() && !m_backwardCells.last().groundExist())
        m_map->getCell(m_backwardCells.last().getVPosition()).removeGround();

     if (m_backwardCells.last().objectExist())
    {map->getCell (m_backwardCells.last().getVPosition()).object().setType(m_backwardCells.last().object().getType());
    m_map->getCell (m_backwardCells.last().getVPosition()).object().setHeight(m_backwardCells.last().object().getHeight());}

     if (m_map->getCell(m_backwardCells.last().getVPosition()).objectExist() && !m_backwardCells.last().objectExist())
        m_map->getCell(m_backwardCells.last().getVPosition()).removeObject();

     if (m_backwardCells.last().superpositionExist())
    {map->getCell (m_backwardCells.last().getVPosition()).superposition().setType(m_backwardCells.last().superposition().getType());
    m_map->getCell (m_backwardCells.last().getVPosition()).superposition().setHeight(m_backwardCells.last().superposition().getHeight());}

     if (m_map->getCell(m_backwardCells.last().getVPosition()).superpositionExist() && !m_backwardCells.last().superpositionExist())
        m_map->getCell(m_backwardCells.last().getVPosition()).removeSuperposition();

     if (m_backwardCells.last().lightExist())
    {map->getCell (m_backwardCells.last().getVPosition()).light().setHeight(m_backwardCells.last().light().GetHeight());
    m_map->getCell (m_backwardCells.last().getVPosition()).light().setColor(m_backwardCells.last().light().GetColor());
    m_map->getCell (m_backwardCells.last().getVPosition()).light().setQuality(m_backwardCells.last().light().GetQuality());
    m_map->getCell (m_backwardCells.last().getVPosition()).light().setRadius(m_backwardCells.last().light().GetRadius());
    m_map->getCell (m_backwardCells.last().getVPosition()).light().setHeight(m_backwardCells.last().light().GetHeight());
    m_map->getCell (m_backwardCells.last().getVPosition()).light().setAngle(m_backwardCells.last().light().GetAngle());
    m_map->getCell (m_backwardCells.last().getVPosition()).light().setIntensity(m_backwardCells.last().light().GetIntensity());
    m_map->getCell (m_backwardCells.last().getVPosition()).light().setOpeningAngle(m_backwardCells.last().light().GetOpeningAngle());}

     if (m_map->getCell(m_backwardCells.last().getVPosition()).lightExist() && !m_backwardCells.last().lightExist())
        m_map->getCell(m_backwardCells.last().getVPosition()).removeLight();


     if (m_backwardCells.last().collisionExist())
     {map->getCell (m_backwardCells.last().getVPosition()).collision().setHeight(m_backwardCells.last().collision().getHeight());
    m_map->getCell (m_backwardCells.last().getVPosition()).collision().setCollision(m_backwardCells.last().collision().isCollision());}

   m_map->getCell (m_backwardCells.last().getVPosition()).update();
    addToScrollBox(m_backwardCells.last().getVPosition());}

         else
          removeCell (m_backwardCells.last().getVPosition());

    m_backwardCells.removeLast();
     }*/
}

void BaseEngine::loadNextCell ()
{
    /*   if (!m_forwardCells.isEmpty())
     {
         saveBackwardCell(m_map->getCell(m_forwardCells.last().getVPosition()),false);

         if (m_forwardCells.last().groundExist() || m_forwardCells.last().objectExist() || m_forwardCells.last().superpositionExist() || m_forwardCells.last().lightExist())
      { m_map->getCell (m_forwardCells.last().getVPosition()).setVPosition(m_forwardCells.last().getVPosition());

     if (m_forwardCells.last().groundExist())
   {map->getCell (m_forwardCells.last().getVPosition()).ground().setType(m_forwardCells.last().ground().getType());
    m_map->getCell (m_forwardCells.last().getVPosition()).ground().setHeight(m_forwardCells.last().ground().getHeight());}

     if (m_map->getCell(m_forwardCells.last().getVPosition()).groundExist() && !m_forwardCells.last().groundExist())
     {
        m_map->getCell(m_forwardCells.last().getVPosition()).removeGround();
     }



     if (m_forwardCells.last().lightExist())
    {map->getCell (m_forwardCells.last().getVPosition()).light().setHeight(m_forwardCells.last().light().GetHeight());
    m_map->getCell (m_forwardCells.last().getVPosition()).light().setColor(m_forwardCells.last().light().GetColor());
    m_map->getCell (m_forwardCells.last().getVPosition()).light().setQuality(m_forwardCells.last().light().GetQuality());
    m_map->getCell (m_forwardCells.last().getVPosition()).light().setRadius(m_forwardCells.last().light().GetRadius());
    m_map->getCell (m_forwardCells.last().getVPosition()).light().setHeight(m_forwardCells.last().light().GetHeight());
    m_map->getCell (m_forwardCells.last().getVPosition()).light().setAngle(m_forwardCells.last().light().GetAngle());
    m_map->getCell (m_forwardCells.last().getVPosition()).light().setIntensity(m_forwardCells.last().light().GetIntensity());
    m_map->getCell (m_forwardCells.last().getVPosition()).light().setOpeningAngle(m_forwardCells.last().light().GetOpeningAngle());}

     if (m_map->getCell(m_forwardCells.last().getVPosition()).lightExist() && !m_forwardCells.last().lightExist())
        m_map->getCell(m_forwardCells.last().getVPosition()).removeLight();

     if (m_forwardCells.last().collisionExist())
     {map->getCell (m_forwardCells.last().getVPosition()).collision().setHeight(m_forwardCells.last().collision().getHeight());
    m_map->getCell (m_forwardCells.last().getVPosition()).collision().setCollision(m_forwardCells.last().collision().isCollision());}

   m_map->getCell (m_forwardCells.last().getVPosition()).update();
    addToScrollBox(m_backwardCells.last().getVPosition());}

         else
          removeCell (m_forwardCells.last().getVPosition());

       m_forwardCells.removeLast();
     }*/
}


void BaseEngine::saveForwardCell (const Container *cell)
{
    /*   if (m_forwardCells.isEmpty())
      {m_forwardCells << cell;}

    if (m_forwardCells.isEmpty() || m_forwardCells.last() != cell)
     m_forwardCells << cell;

    if (m_forwardCells.size() > BACKWARD_BUFFER)
        m_forwardCells.removeFirst();*/
}

void BaseEngine::winContextMenu(QPoint position)
{
    /*   bool menu_empty = true;

     if (tool != TOOL_NOTHING)
     {if (exist(toTileCoords(sf::Vector2i(position.x(),position.y()))))
     {
         m_contextMenu->clear();


             sf::Vector2i cell = toTileCoords(sf::Vector2i(position.x(),position.y()));

             if (m_map->getCell(cell).groundExist())
             {
                 menu_empty =false;

               QMenu *ground = m_contextMenu->addMenu("Terres");
               QMenu *sub_menu = ground->addMenu("Animations");

                 foreach (QString animation,m_map->getCell(cell).ground().getAnimNames())
                {
                     QAction *action = sub_menu->addAction(animation);
                      action->setCheckable(true);
                      action->setData(QPoint(cell.x, cell.y));

                     if (m_map->getCell(cell).ground().getCurrentAnim() == animation)
                     action->setChecked(true);

                     connect (action, SIGNAL(changed()), this, SLOT(groundChangeAnim()));
                 }
             }


             if (m_map->getCell(cell).objectExist())
             {
               menu_empty =false;

               QMenu *object= m_contextMenu->addMenu("Objets");
               QMenu *sub_menu = object->addMenu("Animations");


              foreach (QString animation,m_map->getCell(cell).object().getAnimNames())
                {
                     QAction *action = sub_menu->addAction(animation);
                     action->setCheckable(true);
                     action->setData(QPoint(cell.x, cell.y));

                     if (m_map->getCell(cell).object().getCurrentAnim() == animation)
                     action->setChecked(true);

                     connect (action, SIGNAL(changed()), this, SLOT(objectChangeAnim()));
                 }
             }


             if (m_map->getCell(cell).superpositionExist())
             {
                 menu_empty =false;

               QMenu *superposition = m_contextMenu->addMenu("Superpositions");
               QMenu *sub_menu = superposition->addMenu("Animation");


                 foreach (QString animation,m_map->getCell(cell).superposition().getAnimNames())
                {
                     QAction *action = sub_menu->addAction(animation);
                     action->setCheckable(true);
                     action->setData(QPoint(cell.x, cell.y));

                     if (m_map->getCell(cell).superposition().getCurrentAnim() == animation)
                     action->setChecked(true);

                     connect (action, SIGNAL(changed()), this, SLOT(superpositionChangeAnim()));
                 }
             }

          if (!menu_empty)
         m_contextMenu->popup(m_mapToGlobal(position));
     }
    }*/
}


/* void BaseEngine::groundChangeAnim()

 {
     QAction *action;
     action = (QAction *) sender();
     sf::Vector2i position = sf::Vector2i(action->data().toPoint().x(), action->data().toPoint().y());

     if (exist(position))

     {
        m_map->getCell(position).ground().setAnimation(action->text());
      }
 }

 void BaseEngine::objectChangeAnim()

 {
     QAction *action;
     action = (QAction *) sender();
     sf::Vector2i position = sf::Vector2i(action->data().toPoint().x(), action->data().toPoint().y());

     if (exist(position))

     {
        m_map->getCell(position).object().setAnimation(action->text());
      }
 }*/

void BaseEngine::updateSelector()
{
    sf::Vector2i mouse_Vposition = m_mapRender->mouseToTileCoords(m_mousePosition);

    if (mouse_Vposition != m_lastMouseVPosition)
    {
        // on supprime la cell mais pas son contenu
        m_map->removeCell(m_lastMouseVPosition,-2, false);

        // si dans la fenetre, on enleve la cell pour ne plus la dessiner
        if (!m_map->inProportions(m_lastMouseVPosition) && !m_map->exist(m_lastMouseVPosition))
            m_mapRender->removeFromScrollBox(m_lastMouseVPosition);

        m_lastMouseVPosition =  mouse_Vposition;
        m_selector->setVPosition(mouse_Vposition);

        if (!m_map->inProportions(mouse_Vposition))
            m_mapRender->addToScrollBox(mouse_Vposition);

        m_map->getCell(mouse_Vposition)->addElement(-2, m_selector);
    }
}

void BaseEngine::setLayerFocus(int layer_id)
{
    m_layerFocus = layer_id;
}

Selector& BaseEngine::getSelector()
{
    return *m_selector;
}
