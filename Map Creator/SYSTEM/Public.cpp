#include "Public.h"

sf::Font FONT;
sf::Shader BLUR_SHADER;

//Convertisseurs chiffres/lettres
int toInt (QString qstring)
{
    std::string string = qstring.toStdString();
    std::istringstream number (string);
    int result;

    number >> result;

    return result;
}

QString toString (const int &number)

{
    // créer un flux de sortie
    std::ostringstream oss;
    // écrire un nombre dans le flux
    oss << number;
    // récupérer une chaîne de caractères
    QString qresult= QString::fromStdString(oss.str());
    return qresult;
}

float toFloat (QString qstring)
{
    std::string string = qstring.toStdString();
    std::istringstream number (string);
    float result;

    number >> result;

    return result;
}

QString toString (const float & number)

{
    // créer un flux de sortie
    std::ostringstream oss;
    // écrire un nombre dans le flux
    oss << number;
    // récupérer une chaîne de caractères
    QString qresult= QString::fromStdString(oss.str());
    return qresult;
}

std::string tostdString (const int &number)
{
    // créer un flux de sortie
    std::ostringstream oss;
    // écrire un nombre dans le flux
    oss << number;
    // récupérer une chaîne de caractères
    std::string result = oss.str();
    return result;
}


//Convertisseur coordonnées
sf::Vector2f toScreenCoords(const sf::Vector2f &position)
{
    sf::Vector2f screen_Coords;

    screen_Coords.x = ((position.x - position.y) * CELL_SIZE_X / 2);
    screen_Coords.y = ((position.x + position.y) * CELL_SIZE_Y / 2);

    return screen_Coords;
}

sf::Vector2f toScreenCoords (const int &x, const int &y)
{
    return toScreenCoords(sf::Vector2f(x,y));
}

sf::Vector2f toScreenCoords (float const & x, float const & y)
{
    return toScreenCoords(sf::Vector2f(x,y));
}

sf::Vector2f toScreenCoords(const sf::Vector2i &position)
{
    return toScreenCoords(sf::Vector2f(position));
}
