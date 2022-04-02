/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <vector>

class Client {
    public:
        Client() = default;
        Client(std::vector<std::string> &arguments);
        ~Client() = default;

        void getArgs(std::vector<std::string> &arguments);
        void createSocket(void);
        void tryConnection(void);
        void startAI(void);

        const std::string ReadFromServer(void);
        void DebugSendToServer(void);
        void SendToServer(std::string &command);
    // private:
        int _port;
        std::string _teamName;
        std::string _machineName;
        bool _debugMode = false;
        int _fd;
        struct sockaddr_in saddr;
};

#endif /* CLIENT_HPP_ */