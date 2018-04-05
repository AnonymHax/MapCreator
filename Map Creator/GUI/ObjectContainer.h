#include "SYSTEM/Public.h"
#include "Object.h"

class ObjectContainer : public Object
{
public:

    ObjectContainer(sf::Vector2i size);

    void show(sf::RenderTarget &target);

    void add(Object *child);
    void remove(Object *child);
    void clear();

    void setToFront(Object *child, bool front);
    void setFocus(Object *child, bool focus);

    void unfocusAll();

    bool isMouseIn(const sf::Vector2i &position);
    bool handleEvent(const sf::Event &event);

protected:

    bool isMouseIn (unsigned int &ObjectNr, const sf::Vector2i &mouse_pos);
    QList<Object*> m_childs;
    unsigned int m_focusedObject;
    bool m_keyPress[sf::Keyboard::KeyCount];
};
