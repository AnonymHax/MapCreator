#ifndef PUBLIC_H
#define PUBLIC_H

#include <QRadioButton>
#include <QLabel>
#include <QMenu>
#include <QDialog>
#include <QPushButton>
#include <QFileDialog>
#include <QTreeView>
#include <QMainWindow>
#include <QDirModel>
#include <QLineEdit>
#include <QMessageBox>
#include <QColorDialog>
#include <QtCore>
#include <QtGui>
#include <string>

#include <qfile.h>
//#include <parser.h>
//#include <serializer.h>

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <stdint.h>
#include <sstream>
#include <limits>
#include <cassert>

#define REVISION 20

#define DEFAULT_TRANSPARENCY 100

#define POSITIVE_ZOOM 0.1f
#define NEGATIVE_ZOOM -0.1f
#define ZOOM_MAX 1.0f
#define ZOOM_MIN 0.09f
#define DEFAULT_ZOOM 2
#define ZOOM_TIME 500

#define CELL_SIZE_X 100 // Mesure de tiles par defaut
#define CELL_SIZE_Y 50

#define VERTICAL_SCROLL_SPEED  20
#define HORIZONTAL_SCROLL_SPEED 10
#define SCROLL_PRECISION 5

#define RENDER_FPS 60
#define EVENTS_FPS 80

#define BACKWARD_BUFFER 250
#define FORWARD_BUFFER 250

#define MAPS_FORMAT "*.map"
#define TILES_FORMAT "*.tile"
#define FORMATS TILES_FORMAT ";;"  MAPS_FORMAT

#define PNG_FORMAT "Image PNG (*.png)"
#define IMAGE_FORMATS PNG_FORMAT

#define DEFAULT_ANIMATION "default"

#define DEFAULT_FONT_PATH "datas/arial.ttf"
extern sf::Font FONT;

#define LIGHT_SMOOTH 2
#define BLUR_SHADER_PATH "datas/blur.frag"
extern sf::Shader BLUR_SHADER;

int toInt (QString qstring);
QString toString (const int & number);
std::string tostdString (const int & number);
float toFloat (QString qstring);
QString toString (const float & number);

sf::Vector2f toScreenCoords (const int & x, const int & y);
sf::Vector2f toScreenCoords (const float &x, const float &y);
sf::Vector2f toScreenCoords( const sf::Vector2i & position);
sf::Vector2f toScreenCoords(const sf::Vector2f & position);

typedef int ID;
#define NO_VALID_ID std::numeric_limits<ID>::max()

typedef enum Tool
{
    TOOL_PLACE, TOOL_DELETE, TOOL_COLLISION, TOOL_HEIGHT, TOOL_LIGHT, TOOL_NOTHING, TOOL_MOVE, TOOL_LAYER
} TOOL;

typedef enum Type
{
    SYSTEM,CELL,ENTITY,LIGHT
} TYPE;

enum MOUSE
{
    LEFT,RIGHT
};

enum ANIMATION
{
    NO_ANIMATION = -1
};


// Contient les variable constantes et les fonctions n'appartenant a aucune classe ex: convertisseur
// des positions relatives au positions reelles etc....

namespace sf
{
template <typename T>
bool operator <(const sf::Vector2<T>& left,const sf::Vector2<T>& right)

{
    if ((left.x <= right.x && left.y < right.y) || (left.x < right.x && left.y >= right.y))
        return true;
    else
        return false;
}

template <typename T>
bool operator >(sf::Vector2<T>& left,const sf::Vector2<T>& right)

{
    if ((left.x >= right.x && left.y > right.y) || (left.x > right.x && left.y <= right.y))
        return true;
    else
        return false;
}
}
#endif // PUBLIC_H
