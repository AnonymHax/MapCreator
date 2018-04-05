#include "ObjectContainer.h"

ObjectContainer::ObjectContainer(sf::Vector2i size) : Object(size)
{
    m_focusedObject = 0;
    m_container = true;
    for (unsigned int i=0; i<sf::Keyboard::KeyCount; ++i)
        m_keyPress[i] = false;
}

void ObjectContainer::show(sf::RenderTarget &target)

{
    m_texture.clear(m_backgroundColor);

    // Loop through all objects
    for (int i=0; i<m_childs.size(); ++i)
    {
        // Draw the object if it is visible
        if (m_childs[i]->m_visible)
            m_childs[i]->show(m_texture);
    }

    m_texture.display();
    m_sprite.setTexture(m_texture.getTexture());
    target.draw(m_sprite);
}

void ObjectContainer::add(Object *child)
{
    if (!m_childs.contains(child))
    {m_childs<<child;
        if (child->m_parent != NULL)
            child->m_parent->remove(this);
        child->m_parent = this;}
}

void ObjectContainer::remove(Object *child)
{m_childs.removeOne(child);}

void ObjectContainer::clear()
{m_childs.clear();}

void ObjectContainer::setToFront(Object *child, bool front)

{
    if (front)
    { // Loop through all objects
        for (int i=0; i<m_childs.size(); ++i)
        {
            // Check if the object is found
            if (m_childs[i] == child)
            {
                // Copy the object
                m_childs.push_back(m_childs[i]);

                // Focus the correct object
                if ((m_focusedObject == 0) || (static_cast<int>(m_focusedObject) == i+1))
                    m_focusedObject = m_childs.size()-1;
                else if (static_cast<int>(m_focusedObject) > i+1)
                    --m_focusedObject;

                // Remove the old object
                m_childs.erase(m_childs.begin() + i);

                break;
            }
        }
    }

    else
    {
        // Loop through all objects
        for (int i=0; i<m_childs.size(); ++i)
        {
            // Check if the object is found
            if (m_childs[i] == child)
            {
                // Copy the object
                Object* obj = m_childs[i];
                m_childs.insert(m_childs.begin(), obj);

                // Focus the correct object
                if (static_cast<int>(m_focusedObject) == i+1)
                    m_focusedObject = 1;
                else if (m_focusedObject)
                    ++m_focusedObject;

                // Remove the old object
                m_childs.erase(m_childs.begin() + i + 1);

                break;
            }
        }
    }
}

void ObjectContainer::setFocus(Object *child, bool focus)
{
    if (focus)
    {  // Loop all the objects
        for (int i=0; i<m_childs.size(); ++i)
        {
            // Search for the object that has to be focused
            if (m_childs[i] == child)
            {
                // Only continue when the object wasn't already focused
                if (static_cast<int>(m_focusedObject) != i+1)
                {
                    // Unfocus the currently focused object
                    if (m_focusedObject)
                    {
                        m_childs[m_focusedObject-1]->m_focused = false;
                        m_childs[m_focusedObject-1]->setFocused(false);
                    }

                    // Focus the new object
                    m_focusedObject = i+1;
                    m_childs[i]->m_focused = true;
                    m_childs[i]->setFocused(true);
                }
                else
                    m_childs[i]->m_focused = true;

                // Another object is focused. Clear all key flags
                for (unsigned int j=0; j<sf::Keyboard::KeyCount; ++j)
                    m_keyPress[j] = false;

                break;
            }
        }
    }

    else
    {
        // Check if the object is focused
        if (child->m_focused)
        {
            // Focus the next object
            //  tabKeyPressed();

            // Make sure that the object gets unfocused
            if (child->m_focused)
            {
                child->m_focused = false;
                m_childs[m_focusedObject-1]->setFocused(false);
                m_focusedObject = 0;
            }
        }
    }
}

void ObjectContainer::unfocusAll()
{
    if (m_focusedObject)
    {
        m_childs[m_focusedObject-1]->m_focused = false;
        m_childs[m_focusedObject-1]->setFocused(false);
        m_focusedObject = 0;
    }
}

bool ObjectContainer::handleEvent(const sf::Event &event)
{
    // Check if a mouse button has moved
    if (event.type == sf::Event::MouseMoved)
    {
        // Loop through all objects
        for (int i=0; i<m_childs.size(); ++i)
        {
            // Check if the mouse went down on the object
            if (m_childs[i]->m_mouseLeftDown)
            {
                // Some objects should always receive mouse move events while dragging them, even if the mouse is no longer on top of them.
                if (m_childs[i]->m_draggable)
                {
                    sf::Vector2i mouse_pos;
                    mouse_pos.x = event.mouseMove.x - m_childs[i]->getPosition().x;
                    mouse_pos.y = event.mouseMove.y - m_childs[i]->getPosition().y;

                    if (m_childs[i]->mouseMoved(mouse_pos))
                        return true;
                }

                // Groups also need a different treatment
                else if (m_childs[i]->m_container)
                {
                    sf::Event _event = event;
                    _event.mouseMove.x -= m_childs[i]->getPosition().x;
                    _event.mouseMove.y -= m_childs[i]->getPosition().y;
                    _event.mouseButton.x -= m_childs[i]->getPosition().x;
                    _event.mouseButton.y -= m_childs[i]->getPosition().y;

                    // Make the event handler of the group do the rest
                    if (static_cast<ObjectContainer*>(m_childs[i])->handleEvent(_event))
                        return true;
                }
            }
        }


        unsigned int objectNr;

        // Check if the mouse is on top of an object
        if (isMouseIn(objectNr, sf::Vector2i(event.mouseMove.x, event.mouseMove.y)))
        {
            // Check if the object is a group
            if (m_childs[objectNr]->m_container)
            {
                // Make the event handler of the group do the rest
                sf::Event _event = event;
                _event.mouseMove.x -= m_childs[objectNr]->getPosition().x;
                _event.mouseMove.y -= m_childs[objectNr]->getPosition().y;
                _event.mouseButton.x -= m_childs[objectNr]->getPosition().x;
                _event.mouseButton.y -= m_childs[objectNr]->getPosition().y;


                static_cast<ObjectContainer*>(m_childs[objectNr])->handleEvent(_event);
            }
            else // Send the event to the object
            {
                sf::Vector2i mouse_pos;
                mouse_pos.x = event.mouseMove.x - m_childs[objectNr]->getPosition().x;
                mouse_pos.y = event.mouseMove.y - m_childs[objectNr]->getPosition().y;

                m_childs[objectNr]->mouseMoved(mouse_pos);
            }

        }
    }

    // Check if a mouse button was pressed
    else if (event.type == sf::Event::MouseButtonPressed)
    {
        // Check if the left mouse was pressed
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            unsigned int objectNr;

            // Check if the mouse is on top of an object
            if (isMouseIn(objectNr, sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
            {
                // Focus the object
                setFocus(m_childs[objectNr],true);

                // Check if the object is a group
                if (m_childs[objectNr]->m_container)
                {
                    // If another object was focused then unfocus it now
                    if ((m_focusedObject) && (m_focusedObject != objectNr+1))
                    {
                        m_childs[m_focusedObject-1]->setFocus(false);
                        m_focusedObject = 0;
                    }

                    sf::Event _event = event;
                    _event.mouseMove.x -= m_childs[objectNr]->getPosition().x;
                    _event.mouseMove.y -= m_childs[objectNr]->getPosition().y;
                    _event.mouseButton.x -= m_childs[objectNr]->getPosition().x;
                    _event.mouseButton.y -= m_childs[objectNr]->getPosition().y;


                    // Make the event handler of the group do the rest
                    static_cast<ObjectContainer*>(m_childs[objectNr])->handleEvent(_event);
                }
                else // The event has to be sent to an object
                {
                    sf::Vector2i mouse_pos;
                    mouse_pos.x = event.mouseButton.x - m_childs[objectNr]->getPosition().x;
                    mouse_pos.y = event.mouseButton.y - m_childs[objectNr]->getPosition().y;

                    m_childs[objectNr]->m_mouseLeftDown = true;
                    m_childs[objectNr]->leftMousePressed(mouse_pos);
                }
            }
            else // The mouse didn't went down on an object, so unfocus the focused object
                unfocusAll();
        }



        // Check if the right mouse was pressed
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            unsigned int objectNr;

            // Check if the mouse is on top of an object
            if (isMouseIn(objectNr, sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
            {
                // Focus the object
                setFocus(m_childs[objectNr],true);

                // Check if the object is a group
                if (m_childs[objectNr]->m_container)
                {
                    // If another object was focused then unfocus it now
                    if ((m_focusedObject) && (m_focusedObject != objectNr+1))
                    {
                        m_childs[m_focusedObject-1]->setFocus(false);
                        m_focusedObject = 0;
                    }

                    sf::Event _event = event;
                    _event.mouseMove.x -= m_childs[objectNr]->getPosition().x;
                    _event.mouseMove.y -= m_childs[objectNr]->getPosition().y;
                    _event.mouseButton.x -= m_childs[objectNr]->getPosition().x;
                    _event.mouseButton.y -= m_childs[objectNr]->getPosition().y;


                    // Make the event handler of the group do the rest
                    static_cast<ObjectContainer*>(m_childs[objectNr])->handleEvent(_event);
                }
                else // The event has to be sent to an object
                {
                    sf::Vector2i mouse_pos;
                    mouse_pos.x = event.mouseButton.x - m_childs[objectNr]->getPosition().x;
                    mouse_pos.y = event.mouseButton.y - m_childs[objectNr]->getPosition().y;

                    m_childs[objectNr]->m_mouseRightDown = true;
                    m_childs[objectNr]->rightMousePressed(mouse_pos);
                }
            }
            else // The mouse didn't went down on an object, so unfocus the focused object
                unfocusAll();
        }


    }

    // Check if a mouse button was released
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        // Check if the left mouse was released
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            unsigned int objectNr;

            // Check if the mouse is on top of an object
            if (isMouseIn(objectNr, sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
            {
                // Check if the object is a group
                if (m_childs[objectNr]->m_container)
                {
                    sf::Event _event = event;
                    _event.mouseMove.x -= m_childs[objectNr]->getPosition().x;
                    _event.mouseMove.y -= m_childs[objectNr]->getPosition().y;
                    _event.mouseButton.x -= m_childs[objectNr]->getPosition().x;
                    _event.mouseButton.y -= m_childs[objectNr]->getPosition().y;

                    // Make the event handler of the group do the rest
                    static_cast<ObjectContainer*>(m_childs[objectNr])->handleEvent(_event);
                }
                else // Send the event to the object
                {
                    sf::Vector2i mouse_pos;
                    mouse_pos.x = event.mouseButton.x - m_childs[objectNr]->getPosition().x;
                    mouse_pos.y = event.mouseButton.y - m_childs[objectNr]->getPosition().y;

                    m_childs[objectNr]->m_mouseLeftDown = false;
                    m_childs[objectNr]->leftMouseReleased(mouse_pos);
                }
                // Tell all the other objects that the mouse has gone up
                for (int i=0; i<m_childs.size(); ++i)
                {
                    if (i != static_cast<int>(objectNr))
                    {
                        if (m_childs[i]->m_container)
                        {
                            sf::Event _event = event;
                            _event.mouseMove.x -= m_childs[i]->getPosition().x;
                            _event.mouseMove.y -= m_childs[i]->getPosition().y;
                            _event.mouseButton.x -= m_childs[i]->getPosition().x;
                            _event.mouseButton.y -= m_childs[i]->getPosition().y;

                            static_cast<ObjectContainer*>(m_childs[i])->handleEvent(_event);
                        }
                        else
                        {
                            m_childs[i]->m_mouseLeftDown = false;
                            m_childs[i]->mouseLeftNoLongerDown();
                        }
                    }
                }
            }
            else
            {
                // Tell all the objects that the mouse has gone up
                for (int i=0; i<m_childs.size(); ++i)
                {
                    if (m_childs[i]->m_container)
                    {
                        sf::Event _event = event;
                        _event.mouseMove.x -= m_childs[i]->getPosition().x;
                        _event.mouseMove.y -= m_childs[i]->getPosition().y;
                        _event.mouseButton.x -= m_childs[i]->getPosition().x;
                        _event.mouseButton.y -= m_childs[i]->getPosition().y;

                        static_cast<ObjectContainer*>(m_childs[i])->handleEvent(_event);
                    }
                    else
                    {
                        m_childs[i]->m_mouseLeftDown = false;
                        m_childs[i]->mouseLeftNoLongerDown();
                    }
                }
            }
        }

        // Check if the right mouse was released
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            unsigned int objectNr;

            // Check if the mouse is on top of an object
            if (isMouseIn(objectNr, sf::Vector2i(event.mouseButton.x, event.mouseButton.y)))
            {
                // Check if the object is a group
                if (m_childs[objectNr]->m_container)
                {
                    sf::Event _event = event;
                    _event.mouseMove.x -= m_childs[objectNr]->getPosition().x;
                    _event.mouseMove.y -= m_childs[objectNr]->getPosition().y;
                    _event.mouseButton.x -= m_childs[objectNr]->getPosition().x;
                    _event.mouseButton.y -= m_childs[objectNr]->getPosition().y;

                    // Make the event handler of the group do the rest
                    static_cast<ObjectContainer*>(m_childs[objectNr])->handleEvent(_event);
                }
                else // Send the event to the object
                {
                    sf::Vector2i mouse_pos;
                    mouse_pos.x = event.mouseButton.x - m_childs[objectNr]->getPosition().x;
                    mouse_pos.y = event.mouseButton.y - m_childs[objectNr]->getPosition().y;

                    m_childs[objectNr]->m_mouseRightDown = false;
                    m_childs[objectNr]->rightMouseReleased(mouse_pos);
                }
                // Tell all the other objects that the mouse has gone up
                for (int i=0; i<m_childs.size(); ++i)
                {
                    if (i != static_cast<int>(objectNr))
                    {
                        if (m_childs[i]->m_container)
                        {
                            sf::Event _event = event;
                            _event.mouseMove.x -= m_childs[i]->getPosition().x;
                            _event.mouseMove.y -= m_childs[i]->getPosition().y;
                            _event.mouseButton.x -= m_childs[i]->getPosition().x;
                            _event.mouseButton.y -= m_childs[i]->getPosition().y;

                            static_cast<ObjectContainer*>(m_childs[i])->handleEvent(_event);
                        }
                        else
                        {
                            m_childs[i]->m_mouseRightDown = false;
                            m_childs[i]->mouseRightNoLongerDown();
                        }
                    }
                }
            }
            else
            {
                // Tell all the objects that the mouse has gone up
                for (int i=0; i<m_childs.size(); ++i)
                {
                    if (m_childs[i]->m_container)
                    {
                        sf::Event _event = event;
                        _event.mouseMove.x -= m_childs[i]->getPosition().x;
                        _event.mouseMove.y -= m_childs[i]->getPosition().y;
                        _event.mouseButton.x -= m_childs[i]->getPosition().x;
                        _event.mouseButton.y -= m_childs[i]->getPosition().y;

                        static_cast<ObjectContainer*>(m_childs[i])->handleEvent(_event);
                    }
                    else
                    {
                        m_childs[i]->m_mouseRightDown = false;
                        m_childs[i]->mouseRightNoLongerDown();
                    }
                }
            }
        }
    }

    // Check if a key was pressed
    else if (event.type == sf::Event::KeyPressed)
    {
        // Only continue when the character was recognised
        if (event.key.code != -1)
        {
            // Mark the key as down
            m_keyPress[event.key.code] = true;

            // Check if there is a focused object
            if (m_focusedObject)
            {
                // Check if the object is a group
                if (m_childs[m_focusedObject-1]->m_container)
                {
                    // Make the event handler of the group do the rest
                    static_cast<ObjectContainer*>(m_childs[m_focusedObject-1])->handleEvent(event);
                }
                else // The event has to be send to a normal object
                {
                    // Some keys may be repeated
                    if ((event.key.code == sf::Keyboard::Left)
                            || (event.key.code == sf::Keyboard::Right)
                            || (event.key.code == sf::Keyboard::Up)
                            || (event.key.code == sf::Keyboard::Down)
                            || (event.key.code == sf::Keyboard::BackSpace)
                            || (event.key.code == sf::Keyboard::Delete)
                            || (event.key.code == sf::Keyboard::Return))
                    {
                        // Tell the object that the key was pressed
                        m_childs[m_focusedObject-1]->keyPressed(event.key.code);
                    }
                }
            }
        }
    }

    // Check if a key was released
    else if (event.type == sf::Event::KeyReleased)
    {
        // We don't handle the tab key as it is an exception and we can't do anything with an unknown key either
        if ((event.key.code != sf::Keyboard::Tab) && (event.key.code !=-1))
        {
            // Check if nothing happend since the key was pressed
            if (m_keyPress[event.key.code] == true)
            {
                // Mark the key as released
                m_keyPress[event.key.code] = false;

                // Check if there is a focused object
                if (m_focusedObject)
                {
                    // Check if the object is a group
                    if (m_childs[m_focusedObject-1]->m_container)
                    {
                        // Make the event handler of the group do the rest
                        static_cast<ObjectContainer*>(m_childs[m_focusedObject-1])->handleEvent(event);
                    }
                    else // The event has to be send to a normal object
                    {
                        // Avoid double callback with keys that can be repeated
                        if ((event.key.code != sf::Keyboard::Left)
                                && (event.key.code != sf::Keyboard::Right)
                                && (event.key.code != sf::Keyboard::Up)
                                && (event.key.code != sf::Keyboard::Down)
                                && (event.key.code != sf::Keyboard::BackSpace)
                                && (event.key.code != sf::Keyboard::Delete)
                                && (event.key.code != sf::Keyboard::Return))
                        {
                            // Tell the object that the key was pressed
                            m_childs[m_focusedObject-1]->keyPressed(event.key.code);
                        }
                    }
                }
            }
        }
        // Also check the tab key
        else if (event.key.code == sf::Keyboard::Tab)
        {
            // Check if nothing happend since the tab key was pressed
            if (m_keyPress[sf::Keyboard::Tab] == true)
            {
                // Change the focus to another object
                //tabKeyPressed();
            }
        }
    }

    // Also chack if text was entered (not a special key)
    else if (event.type == sf::Event::TextEntered)
    {
        // Check if the character that we pressed is allowed
        if ((event.text.unicode >= 30) && (event.text.unicode != 127))
        {
            // Check if there is a focused object
            if (m_focusedObject)
            {
                // Check if the object is a group
                if (m_childs[m_focusedObject-1]->m_container)
                {
                    // Make the event handler of the group do the rest
                    static_cast<ObjectContainer*>(m_childs[m_focusedObject-1])->handleEvent(event);
                }
                else // Tell the object that the key was pressed
                    m_childs[m_focusedObject-1]->textEntered(event.text.unicode);
            }
        }
    }

    // Check for mouse wheel scrolling
    else if (event.type == sf::Event::MouseWheelMoved)
    {
        // Find the object under the mouse
        unsigned int objectNr;
        if (isMouseIn(objectNr, sf::Vector2i(event.mouseWheel.x, event.mouseWheel.y)))
        {
            // Check if the object is a group
            if (m_childs[objectNr]->m_container)
            {
                sf::Event _event = event;
                _event.mouseMove.x -= m_childs[objectNr]->getPosition().x;
                _event.mouseMove.y -= m_childs[objectNr]->getPosition().y;
                _event.mouseButton.x -= m_childs[objectNr]->getPosition().x;
                _event.mouseButton.y -= m_childs[objectNr]->getPosition().y;

                // Make the event handler of the group do the rest
                static_cast<ObjectContainer*>(m_childs[objectNr])->handleEvent(_event);
            }
            else // Send the event to the object
                m_childs[objectNr]->wheelMouseMoved(event.mouseWheel.delta);
        }
    }

    return false;
}

bool ObjectContainer::isMouseIn(const sf::Vector2i &position)

{
    if (0 <= position.x &&
            m_size.x >= position.x &&
            0 <= position.y &&
            m_size.y >= position.y)
        return true;

    return false;
}

bool ObjectContainer::isMouseIn(unsigned int& objectNr, const sf::Vector2i &mouse_pos)
{
    bool objectFound = false;
    // Loop through all objects
    for (int i=0; i<m_childs.size(); ++i)
    {
        // Check if the object is visible and enabled
        if ((m_childs[i]->m_visible) && (m_childs[i]->m_enabled))
        {
            // Ask the object if the mouse is on top of them
            if (m_childs[i]->isMouseIn(mouse_pos))
            {
                // If there already was an object then they overlap each other
                if (objectFound)
                    m_childs[objectNr]->mouseNoLongerOnObjet();

                // An object is found now
                objectFound = true;

                m_childs[i]->m_mouseHover = true;
                // Also remember what object should receive the event
                objectNr = i;
            }
            else if (m_childs[i]->m_mouseHover)
                m_childs[i]->mouseNoLongerOnObjet();
        }
    }
    // If our mouse is on top of an object then return true
    return objectFound;
}
