/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** graph
*/

#ifndef GRAPHICAL_MODULE_HPP_
#define GRAPHICAL_MODULE_HPP

#include <vector>
#include <map>
#include <regex>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Socket.hpp"

enum Resource {Food, Linemate, Deraumere, Sibur, Mendiane, Phiras, Thystame};

class Tile
{
    public:
        Tile(float x, float y, sf::Texture **tex, std::map<Resource, sf::Texture *> resTextures, sf::Font *font, sf::Texture *playerTex, sf::Texture *outlineTex);
        ~Tile() {};

        void addResource(Resource);
        void addPlayer(std::string playerInfo);
        void removePlayer(void);
        void drawItself(sf::RenderWindow *);
        void editTileResources(std::string data);
        void removeResource(Resource resource);

        sf::Sprite *sprite;
        sf::Sprite *playerSprite;
        sf::Sprite *outlineSprite;
        sf::Text *text;
        float posX;
        float posY;
        float playerOrientation = 0;
        bool hasPlayer = false;
        std::map<Resource, bool> res = {{Food, 0}, {Linemate, 0}, {Deraumere, 0}, {Sibur, 0}, {Mendiane, 0}, {Phiras, 0}, {Thystame, 0}};
        std::map<Resource, sf::Texture *> resTextures;
        std::map<Resource, sf::Sprite *> resSprite;
};

class GraphicalModule
{
    public:
        GraphicalModule();
        ~GraphicalModule();

        void createBoard(unsigned int x, unsigned int y);
        bool initMap(void);
        void refreshMap(void);
        void initResTextures(void);
        void handleTiming(Client *client);
        void editTile(std::string &instruction);

        sf::Texture *groundTex[3];
        sf::Texture *playerTex;
        sf::Texture *outlineTex;
        sf::Texture *watermarkTex;
        sf::Texture *legendTex;
        sf::Sprite *groundSprite;
        sf::Sprite *watermarkSprite;
        sf::Sprite *legendSprite;
        sf::Font *font;
        std::vector<Tile *> tiles;
        std::map<Resource, sf::Texture *> resTextures;
        std::ifstream *stream;
        std::regex *rgx;
        unsigned int mapSizeX = 0;
        unsigned int mapSizeY = 0;

};

#endif /* GRAPHICAL_MODULE_HPP_ */