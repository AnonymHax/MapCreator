#ifndef LIGHTMANAGERH
#define LIGHTMANAGERH

#include "SYSTEM/Singleton.h"
#include "GAME_ELEMENTS/DirectionalLight.h"
/*
class Light_Manager : public CSingleton<Light_Manager>
{
    protected :

    Light_Manager();
    ~Light_Manager();

     // Les tableaux de murs, lumières statiques et dynamiques
    std::vector <Wall> m_wall;
    std::vector <Light*> m_StaticLight;
    std::vector <Light*> m_DynamicLight;

    public :
    // Constructeur et destructeur
    friend Light_Manager* CSingleton<Light_Manager>::getInstance();
    friend void CSingleton<Light_Manager>::clear();


    //Différents moyen d'ajouter une lumière dynamique, soit on l'ajoute sans aucune valeur par défaut, soit on lui donne une lumière par défaut, soit on lui donne ses valeurs "à la main"
    Light_Entity Add_Dynamic_Light();
    Light_Entity Add_Dynamic_Light(Light);
    Light_Entity Add_Dynamic_Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color);

    Light_Entity Add_Dynamic_Directional_Light();
    Light_Entity Add_Dynamic_Directional_Light(Directional_light);
    Light_Entity Add_Dynamic_Directional_Light(sf::Vector2f position, float intensity, float radius, float angle, float o_angle, sf::Color color);

    Light_Entity Add_Static_Light(Light);
    Light_Entity Add_Static_Light(sf::Vector2f position, float intensity, float radius, int quality, sf::Color color);

    Light_Entity Add_Static_Directional_Light(Directional_light);
    Light_Entity Add_Static_Directional_Light(sf::Vector2f position, float intensity, float radius, float angle, float o_angle, sf::Color color);

    // Ajouter un mur
    Wall_Entity Add_Wall(sf::Vector2f pt1,sf::Vector2f pt2);

    // Désactiver une lumière ou supprimer un mur
    void Delete_Light(Light_Entity);
    void Delete_Wall(Wall_Entity);

    void Delete_All_Wall();
    void Delete_All_Light();

    // Calculer toutes les lumières dynamiques
    void Generate();
    void Generate(Light_Entity);

    // Afficher toutes les lumières à l'écran
    void DrawLights(sf::RenderTarget *App, sf::View &View);
    void DrawLightsT (sf::RenderTarget &App);

    // Différentes méthodes pour modifier les attributs d'une lumière, ou les récupérer. Il faut à chaque fois envoyer une Light_Entity en paramètre pour
    // savoir de quelle lumière on parle/

    void setPosition(Light_Entity, sf::Vector2f );
    void setQuality(Light_Entity, int );
    void setRadius(Light_Entity, int );
    void setColor(Light_Entity, sf::Color );
    void setIntensity(Light_Entity, int);

    void setOtherParameter(Light_Entity , unsigned, float);

    float getIntensity(Light_Entity);
    float getRadius(Light_Entity);
    int getQuality(Light_Entity);
    sf::Color getColor(Light_Entity);
    sf::Vector2f getPosition(Light_Entity);

    void setPosition(Wall_Entity, sf::Vector2f );

    sf::Color m_basicLight;
    int m_lightSmooth;

    private:

    sf::Shader BlurEffect;
    std::vector<Light*>::iterator Iter;
    sf::RenderTexture m_renderImg;

};
*/
#endif
