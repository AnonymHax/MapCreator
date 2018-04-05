#include "SYSTEM/Public.h"
#include "Movable_Item.h"

class ObjectContainer;
class ObjectLayer;

class Object : public Movable_Item
{

friend class ObjectContainer;
friend class ObjectLayer;

public:

    Object(sf::Vector2i size);
    ~Object();

    virtual void show(sf::RenderTarget &target) = 0;

    void setPosition(const sf::Vector2i &position);
    void setSize(const sf::Vector2i &size);
    void setParent(ObjectContainer *parent);
    void setFocus(bool focus);
    void setVisible(bool visible);
    void setEnabled(bool enable);
    void setBackgroundColor(const sf::Color &color);

    sf::Vector2i getPosition() const;
    sf::Vector2i getSize() const;
    sf::Vector2i getGlobalPosition() const;
    sf::Color getBackgroundColor() const;
    int getId() const;

    void setToFront(bool front);

    virtual bool isMouseIn (const sf::Vector2i &position);

    virtual bool mouseMoved(const sf::Vector2i &position);
    virtual bool leftMousePressed(const sf::Vector2i &position);
    virtual bool rightMousePressed(const sf::Vector2i &position);
    virtual bool leftMouseReleased(const sf::Vector2i &position);
    virtual bool rightMouseReleased(const sf::Vector2i &position);
    virtual bool wheelMouseMoved(const int &delta);
    virtual bool keyPressed(const sf::Keyboard::Key &key);
    virtual bool textEntered(const sf::Uint32 &key);
    virtual void setFocused(const bool &focused);

    virtual void mouseLeftNoLongerDown();
    virtual void mouseRightNoLongerDown();
    virtual void mouseNoLongerOnObjet();


protected:

    int m_id;

    void updatePosition();
    void updateSize();

    sf::Time getElapsedTime();
    void restartTimer();

    sf::Vector2i m_position;
    sf::Vector2i m_size;
    bool m_visible;
    bool m_enabled;
    ObjectContainer *m_parent;
    bool m_mouseHover;
    bool m_mouseLeftDown;
    bool m_mouseRightDown;
    bool m_focused;
    bool m_container;
    bool m_draggable;
    sf::Sprite m_sprite;
    sf::RenderTexture m_texture;
    sf::Color m_backgroundColor;
    sf::Clock *m_clock;

private:

    static int m_nbObjects; // Ne sert qu'a attribuer un id (ne se decrmeente pas lorsqu'un objet est supprimé)
};
