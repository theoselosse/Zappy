/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** main.cpp
*/

#include "../include/Client.hpp"
#include <string>
#include <vector>
#include <memory>
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
        "\tname\tis the name of the team\n" <<
        "\tmachine\tis the name of the machine; localhost by default\n";
        return (0);
    } else if (argc >= 5) {
        try {
            srand(time(NULL));
            std::vector<std::string> arguments (argv + 1, argv + argc);
            std::unique_ptr<Client> Cli (std::make_unique<Client> (arguments));
            Cli->tryConnection();
            Cli->startAI();
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
}