/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** main.cpp
*/

#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Error.hpp"
#include "GraphicalModule.hpp"
#include "Socket.hpp"

void GraphicalModule::initResTextures(void)
{
    std::string paths[] = {"assets/Food2.png", "assets/Linemate.png", "assets/Deraumere.png", "assets/Sibur.png", "assets/Mendiane.png", "assets/Phiras.png", "assets/Thystame.png"};
    int i = 0;

    this->resTextures[Food] = new sf::Texture;
    this->resTextures[Linemate] = new sf::Texture;
    this->resTextures[Deraumere] = new sf::Texture;
    this->resTextures[Sibur] = new sf::Texture;
    this->resTextures[Mendiane] = new sf::Texture;
    this->resTextures[Phiras] = new sf::Texture;
    this->resTextures[Thystame] = new sf::Texture;
    for (auto &x: this->resTextures) {
        if (!x.second->loadFromFile(paths[i]))
            exit(84);
        i++;
    }
}

void handleCameraMovements(sf::View *view)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        view->move(4, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        view->move(-4, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        view->move(0, -4);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        view->move(0, 4);
}

void handleZoom(sf::View *view, sf::Event *event)
{
    if (event->type == sf::Event::MouseWheelScrolled) {
        if (event->mouseWheelScroll.delta < 0)
            view->zoom(1.10);
        if (event->mouseWheelScroll.delta > 0)
            view->zoom(0.90);
    }
}

void init(sf::Window *window, sf::View *view, sf::View *hudView)
{
    srand(time(NULL));
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(true);
    view->reset(sf::FloatRect(200, 200, 1920, 1080));
    hudView->reset(sf::FloatRect(0, 0, 1920, 1080));
}

void mainLoop(GraphicalModule *graph, sf::RenderWindow *window, sf::View *view, sf::View *hudView, sf::Event *event, Client *client)
{
    while (window->isOpen()) {
        handleCameraMovements(view);
        while (window->pollEvent(*event)) {
            if (event->type == sf::Event::Closed)
                window->close();
            handleZoom(view, event);
        }
        graph->handleTiming(client);
        window->clear(); // sf::Color(20, 60, 40) to change background color
        window->setView(*view);
        for (unsigned int i = 0; i < graph->tiles.size(); i++)
            graph->tiles[i]->drawItself(window);
        window->setView(*hudView);
        window->draw(*graph->watermarkSprite);
        window->draw(*graph->legendSprite);
        window->display();
    }
}

int main(int argc,char **argv)
{
    sf::Event event;
    sf::View view;
    sf::View hudView;
    sf::Music music;
    GraphicalModule graph;
    if (argc < 5)
        return 84;
    std::vector<std::string> arguments(argv + 1, argc + argv);
    Client client(arguments);

    client.tryConnection();
    client.ReadFromServer();
    dprintf(client.getFd(), "team: debug\n");
    client.ReadFromServer();
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Zappy AGC - Awesome Graphical Client");
    init(&window, &view, &hudView);
    graph.initResTextures();
    if (graph.initMap() == 1)
        return 84;
    if (!music.openFromFile("sounds/terraria_jungle.ogg"))
        return 84;
    music.play();
    mainLoop(&graph, &window, &view, &hudView, &event, &client);
    music.stop();
    return 0;
}

/*
#include "../include/Error.hpp"
#include <iostream>

static size_t my_strlen(char const *str)
{
    size_t i = 0;

    if (str == NULL)
        return (0);
    for (; str && str[i]; i++);
    return (i);
}

static size_t my_strncmp(char const *s1, char const *s2, size_t n)
{
    size_t i = 0;

    while ((*s1 && *s2) && (i < n)) {
        *s1++;
        *s2++;
        i++;
    }
    return (*s2 - *s1);
}

int main(int argc, char **argv)
{
    if (argc == 2 && my_strncmp(argv[1], "-help", my_strlen(argv[1])) == 0) {
        std::cout << "USAGE: ./zappy_ai -p port -n name -h machine\n" <<
        "\tport\tis the port number\n" <<
        "\tmachine\tis the name of the machine; localhost by default\n";
        return (0);
    } else if (argc == 5) {
        try {
            return (0);
        }
        catch(const Error &e) {
            std::cerr << e.what() << '\n';
            return (84);
        }
    } else {
        std::cerr << "Bad args, retry with -h" << std::endl;
        return (84);
    }
    return (0);
}*/