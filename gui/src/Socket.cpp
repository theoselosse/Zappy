/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** main.cpp
*/

#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <string>
#include <vector>
#include <iostream>
#include "Error.hpp"
#include "Socket.hpp"

Client::Client(std::vector<std::string> &arguments)
{
    this->getArgs(arguments);
    this->createSocket();
}

std::string checkMachineName(std::vector<std::string> &arguments)
{
    for (unsigned int i = 0; i < arguments.size(); i++) {
        if (arguments.at(i) == "-h" && i != arguments.size()) {
            return (arguments.at(i + 1));
        }
    }
    return ("localhost");
}

signed int checkPort(std::vector<std::string> &arguments)
{
    for (unsigned int i = 0; i < arguments.size(); i++) {
        if (arguments.at(i) == "-p" && i != arguments.size()) {
            return (std::stoi(arguments.at(i + 1)));
        }
    }
    return (-1);
}

void Client::getArgs(std::vector<std::string> &arguments)
{
    bool is_p (false), is_h (false);

    for (auto &i : arguments) {
        if (i == "-p")
            is_p = true;
        if (i == "-h")
            is_h = true;
    }
    if (is_p == false || is_h == false)
        throw Error("Invalid arguments");
    _port = checkPort(arguments);
    if (is_h == true)
        _machineName = checkMachineName(arguments);
    if (_machineName == "localhost" || is_h == false)
        _machineName = "127.0.0.1";
}

void Client::createSocket(void)
{
    if (this->_port < 1 || this->_port > 65535)
        throw Error("Invalid port number, value must be between 1 and 65535");
    this->_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->_fd == -1)
        throw Error("Error encountered while initializing the socket");
    this->saddr.sin_family = AF_INET;
    this->saddr.sin_port = htons(this->_port);
    this->saddr.sin_addr.s_addr = inet_addr(this->_machineName.c_str());
}

void Client::tryConnection(void)
{
    if (connect(this->_fd, (const struct sockaddr *)&this->saddr, sizeof(this->saddr)) == -1)
        throw Error("Can't connect to the server");
}

const std::string Client::ReadFromServer(void)
{
    size_t size = 0;
    char buf[4096];

    if (fcntl(this->_fd, F_SETFL, fcntl(this->_fd, F_GETFL) | O_NONBLOCK) < 0)
        return ("None");
    size = read(this->_fd, buf, 4096);
    if (size > 0 && size <= 4096) {
        buf[size] = '\0';
        return (std::string(buf));
    }
    return ("None");
}

bool Client::selectEvent(void)
{
    fd_set fd_read;
    std::string answer;

    FD_ZERO(&fd_read);
    FD_SET(this->_fd, &fd_read);
    if (select(this->_fd + 1, &fd_read, NULL, NULL, NULL) == -1)
        throw Error("Select failed");
    if (FD_ISSET(this->_fd, &fd_read))
        answer = ReadFromServer();
    if (answer == "refresh")
        return (true);
    return (false);
}

int Client::getFd(void) const
{
    return this->_fd;
}