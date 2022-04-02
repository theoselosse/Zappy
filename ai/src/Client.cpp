/*
** EPITECH PROJECT, 2021
** Client.cpp
** File description:
** client
*/

#include <chrono>
#include <thread>
#include <sys/select.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../include/Error.hpp"
#include <string>
#include <vector>
#include "../include/Client.hpp"

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

std::string checkTeamName(std::vector<std::string> &arguments)
{
    for (unsigned int i = 0; i < arguments.size(); i++) {
        if (arguments.at(i) == "-n" && i != arguments.size()) {
            return (arguments.at(i + 1));
        }
    }
    return ("None");
}

void Client::getArgs(std::vector<std::string> &arguments)
{
    bool is_p (false), is_n (false), is_h (false);
    std::size_t pos (0);

    for (auto &i : arguments) {
        if (i == "-p")
            is_p = true;
        if (i == "-n")
            is_n = true;
        if (i == "-h")
            is_h = true;
    }
    if (is_p == false || is_n == false)
        throw Error("Invalid arguments");
    this->_port = checkPort(arguments);
    this->_teamName = checkTeamName(arguments);
    if (this->_teamName == "debug")
        this->_debugMode = true;
    if ((pos = this->_teamName.find(" ")) != std::string::npos
        || (pos = this->_teamName.find("\t")) != std::string::npos)
        throw Error("No spaces or tabs allowed in team name");
    if (is_h == true)
        this->_machineName = checkMachineName(arguments);
    if (this->_machineName == "localhost" || is_h == false)
        this->_machineName = "127.0.0.1";
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

void Client::SendToServer(std::string &command)
{
    command.append("\n");
    write(this->_fd, command.c_str(), command.size());
}

const std::string Client::ReadFromServer(void)
{
    size_t size = 0;
    char buf[4096];

    if ((size = read(this->_fd, buf, 4096)) > 0) {
        buf[size] = '\0';
        return (std::string(buf));
    }
    throw Error("EOF encountered");
}

void Client::DebugSendToServer(void)
{
    size_t size = 0;
    char buf[4096];

    if ((size = read(0, buf, 4096)) > 0) {
        buf[size] = '\0';
        write(this->_fd, buf, strlen(buf));
        return;
    }
}

class AI {
    public:
        AI(int &sock, const std::string &team_name);
        ~AI() = default;

        void SayHello(void);
        void SendToServer(std::string &command);
        void getAnswer(void);
        void adoptStrategy(void);

    // private:
        int _fd;
        std::string _teamName;
        unsigned int level;
        std::string _answer;
        std::string _last_action;
        std::string _last_answer;
        std::vector<int> inventory {0, 0, 0, 0, 0, 0, 0};
};

AI::AI(int &sock, const std::string &team_name)
{
    this->_fd = sock;
    this->_teamName = team_name;
    this->level = 1;
    this->_answer = "None";
}

void AI::SayHello(void)
{
    std::string team_msg ("team: ");
    team_msg.append(this->_teamName);
    this->SendToServer(team_msg);
}

void AI::SendToServer(std::string &command)
{
    command.append("\n");
    write(this->_fd, command.c_str(), command.size());
}

void AI::getAnswer(void)
{
    size_t size = 0;
    char buf[4096];

    if ((size = read(this->_fd, buf, 4096)) > 0) {
        buf[size] = '\0';
        this->_answer = std::string(buf);
        return;
    }
    throw Error("EOF encountered");
}

void AI::adoptStrategy(void)
{
    return;
}

void Client::startAI(void)
{
    fd_set fd_read;
    AI Bobby (this->_fd, this->_teamName);

    Bobby.SayHello();
    Bobby.getAnswer();
    std::cout << Bobby._answer;
    while (1) {
        FD_ZERO(&fd_read);
        FD_SET(this->_fd, &fd_read);
        FD_SET(STDIN_FILENO, &fd_read);
        if (select(this->_fd + 1, &fd_read, NULL, NULL, NULL) == -1) {
            throw Error("Select failed");
        }
        if (FD_ISSET(STDIN_FILENO, &fd_read)) {
            this->DebugSendToServer();
        }
        if (FD_ISSET(this->_fd, &fd_read)) {
            std::cout << this->ReadFromServer();
        }
    }
}