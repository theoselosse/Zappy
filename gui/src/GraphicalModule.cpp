/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** graph
*/

#include <iostream>
#include <map>
#include <fstream>
#include "../include/Socket.hpp"
#include "../include/Error.hpp"
#include "../include/GraphicalModule.hpp"

Tile::Tile(float x, float y, sf::Texture **tex, std::map<Resource, sf::Texture *> resTex, sf::Font *font, sf::Texture *playerTex, sf::Texture *outlineTex) : posX(x), posY(y)
{
    int randomNb = rand() % 3;

    this->text = new sf::Text;
    this->sprite = new sf::Sprite(*tex[randomNb]);
    this->playerSprite = new sf::Sprite(*playerTex);
    this->outlineSprite = new sf::Sprite(*outlineTex);

    this->sprite->setPosition(x, y);
    this->playerSprite->setOrigin(16, 16);
    this->playerSprite->setPosition(x + 64, y + 64);
    this->outlineSprite->setOrigin(16, 16);
    this->outlineSprite->setPosition(x + 64, y + 64);
    this->resTextures = resTex;

    this->resSprite[Food] = new sf::Sprite(*this->resTextures[Food]);
    this->resSprite[Linemate] = new sf::Sprite(*this->resTextures[Linemate]);
    this->resSprite[Deraumere] = new sf::Sprite(*this->resTextures[Deraumere]);
    this->resSprite[Sibur] = new sf::Sprite(*this->resTextures[Sibur]);
    this->resSprite[Mendiane] = new sf::Sprite(*this->resTextures[Mendiane]);
    this->resSprite[Phiras] = new sf::Sprite(*this->resTextures[Phiras]);
    this->resSprite[Thystame] = new sf::Sprite(*this->resTextures[Thystame]);

    this->resSprite[Food]->setPosition(x + 72, y + 72);
    this->resSprite[Linemate]->setPosition(x + 32, y + 13);
    this->resSprite[Deraumere]->setPosition(x + 56, y + 13);
    this->resSprite[Sibur]->setPosition(x + 80, y + 13);
    this->resSprite[Mendiane]->setPosition(x + 12, y + 37);
    this->resSprite[Phiras]->setPosition(x + 12, y + 61);
    this->resSprite[Thystame]->setPosition(x + 12, y + 85);

    this->text->setFont(*font);
    this->text->setString("");
    this->text->setCharacterSize(20);
    this->text->setOutlineThickness(2);
    this->text->setPosition(x + 8, y + 99);
}

void Tile::addResource(Resource resource)
{
    this->res[resource] = true;
}

void Tile::removeResource(Resource resource)
{
    this->res[resource] = false;
}

void Tile::addPlayer(std::string playerInfo)
{
    sf::Color teamColors[8] = {{50, 50, 50}, {50, 100, 50}, {50, 50, 100}, {100, 50, 50}, {100, 50, 100}, {100, 100, 50}, {50, 100, 100}, {100, 100, 100}};
    sf::Color elevationColors[8] = {{200, 0, 0}, {200, 100, 0}, {200, 200, 0}, {100, 200, 0}, {0, 200, 0}, {0, 200, 100}, {0, 200, 200}, {255, 255, 255}};
    int step = 0;
    int offset = 0;
    std::string temp;

    try {
        if (std::stoi(playerInfo.substr(0, playerInfo.find('|'))) > 0) {
            this->hasPlayer = true;
            this->text->setString(playerInfo.substr(0, playerInfo.find('|')));
        }
        offset = playerInfo.find('|') + 1;
        for (unsigned int i = playerInfo.find('|') + 1; i < playerInfo.size() && step < 2; i++) {
            if (playerInfo[i] == ';') {
                switch (step) {
                    case 0:
                        this->playerSprite->setColor(teamColors[playerInfo.substr(offset, i - offset)[0] % 9]);
                        break;
                    case 1:
                        this->outlineSprite->setColor(elevationColors[std::stoi(playerInfo.substr(offset, i - offset)) % 8]);
                        break;
                }
                step++;
                offset = i + 1;
            }
        }
        this->playerSprite->setRotation((std::stoi(playerInfo.substr(offset)) - 1) * -90);
        this->outlineSprite->setRotation((std::stoi(playerInfo.substr(offset)) - 1) * -90);
    } catch (const std::exception &e) {
        std::cerr << "Parsing error in file sent by server (the game's display may not update properly)\n---> Error located in " << e.what() << "\n";
        return;
    }
}

void Tile::removePlayer(void)
{
    this->hasPlayer = false;
    this->text->setString("0");
}

void Tile::drawItself(sf::RenderWindow *window)
{
    window->draw(*this->sprite);
    for (auto &x: this->res) {
        if (x.second == true)
            window->draw(*this->resSprite[x.first]);
    }
    if (this->hasPlayer) {
        window->draw(*this->outlineSprite);
        window->draw(*this->playerSprite);
    }
    window->draw(*this->text);
}

void Tile::editTileResources(std::string data)
{
    if (data.size() != 7)
        return;
    for (unsigned int i = 0; i < data.size(); i++)
        data[i] == '1' ? this->res[(Resource)i] = true : this->res[(Resource)i] = false;
}

void exitIfPathNotFound(const std::string path, sf::Texture *tex)
{
    if (!tex->loadFromFile(path)) {
        std::cerr << "A texture can't be found\n";
        exit(84);
    }
}

GraphicalModule::GraphicalModule()
{
    this->watermarkTex = new sf::Texture;
    this->legendTex = new sf::Texture;

    if (!this->watermarkTex->loadFromFile("assets/Zappy.png")) {
        std::cerr << "watermark texture missing: probably removed. AL Lib will clean up opened soundbuffers.\n";
        exit(84);
    }
    if (!this->legendTex->loadFromFile("assets/Legende.png")) {
        std::cerr << "Legend texture missing: probably removed. AL Lib will clean up opened soundbuffers.\n";
        exit(84);
    }
    this->watermarkSprite = new sf::Sprite(*this->watermarkTex);
    this->legendSprite = new sf::Sprite(*this->legendTex);
    this->watermarkSprite->setPosition(20, 920);
    this->legendSprite->setPosition(25, 25);
}

GraphicalModule::~GraphicalModule()
{
    // ??
}

void GraphicalModule::createBoard(unsigned int x, unsigned int y)
{
    for (int i = 0; i < 3; i++)
        this->groundTex[i] = new sf::Texture;
    this->font = new sf::Font;
    this->playerTex = new sf::Texture;
    this->outlineTex = new sf::Texture;

    this->mapSizeX = x;
    this->mapSizeY = y;
    exitIfPathNotFound("assets/Tile1.png", this->groundTex[0]);
    exitIfPathNotFound("assets/Tile2.png", this->groundTex[1]);
    exitIfPathNotFound("assets/Tile3.png", this->groundTex[2]);
    exitIfPathNotFound("assets/Fleche.png", this->playerTex);
    exitIfPathNotFound("assets/Outline.png", this->outlineTex);
    if (!this->font->loadFromFile("fonts/Elektronik.ttf"))
        exit(84);
    for (unsigned int i = 0; i < x * y; i++)
        this->tiles.push_back(new Tile(64 + 128 * (i % x), 64 + 128 * (i / x), this->groundTex, this->resTextures, this->font, this->playerTex, this->outlineTex));
}

bool GraphicalModule::initMap(void)
{
    std::ifstream *filestream = new std::ifstream;
    std::regex *regex = new std::regex("[0-9]+,[0-9]+#[0-1][0-1][0-1][0-1][0-1][0-1][0-1]|[0-9]+:[0-9]+;[1-6];[1-4]");
    std::string buffer;

    filestream->open("../server/map.txt", std::fstream::in);
    if (!filestream->is_open())
        return (1);
    this->stream = filestream;
    this->rgx = regex;
    std::getline(*this->stream, buffer);
    try {
        this->createBoard(std::stoi(buffer.substr(0, buffer.find(':'))), std::stoi(buffer.substr(buffer.find(':') + 1)));
    } catch (const std::exception &e) {
        std::cerr << "Parsing error in file sent by server (first line could be wrong)\n";
        return (1);
    }
    this->stream->close();
    this->refreshMap();
    return (0);
}

void GraphicalModule::editTile(std::string &instruction)
{
    int step = 0;
    int offset = 0;
    int x = 0;
    int y = 0;
    std::string parts[4];

    try {
        for (unsigned int i = 0; i < instruction.size() && step < 3; i++) {
            if (instruction[i] == ',' || instruction[i] == '#' || instruction[i] == ':') {
                switch (step) {
                    case 0:
                        x = std::stoi(instruction.substr(offset, i - offset));
                        break;
                    case 1:
                        y = std::stoi(instruction.substr(offset, i - offset));
                        break;
                    case 2:
                        this->tiles[x + y * this->mapSizeX]->editTileResources(instruction.substr(offset, i - offset));
                        break;
                }
                offset = i + 1;
                step++;
            }
        }
        if (std::stoi(instruction.substr(offset)) > 0)
            this->tiles[x + y * this->mapSizeX]->addPlayer(instruction.substr(offset));
        else
            this->tiles[x + y * this->mapSizeX]->removePlayer();
    } catch (const std::exception &e) {
        std::cerr << "Parsing error in file sent by server (the game's display won't update)\n---> Error located in " << e.what() << "\n";
        return;
    }
}

void GraphicalModule::refreshMap(void)
{
    std::string buffer;

    this->stream->open("../server/map.txt", std::fstream::in);
    if (!this->stream->is_open())
        return;
    while (std::getline(*this->stream, buffer)) {
        if (std::regex_search(buffer, *this->rgx))
            editTile(buffer);
    }
    this->stream->clear();
    this->stream->seekg(0);
    this->stream->close();
}

void GraphicalModule::handleTiming(Client *client)
{
    static unsigned int counter = 0;

    if (counter % 60 == 0) {
        if (this->watermarkSprite->getTextureRect().left < 1920)
            this->watermarkSprite->setTextureRect(sf::IntRect(this->watermarkSprite->getTextureRect().left + 384, 0, 384, 128));
        else
            this->watermarkSprite->setTextureRect(sf::IntRect(0, 0, 384, 128));
    }
    if (counter % 120 == 0)
            this->refreshMap();
    counter++;
}

// if (client->ReadFromServer() != "None") ---> vérif pas fonctionnelle