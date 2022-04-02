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
        Client(std::vector<std::string> &arguments);
        ~Client() = default;

        void getArgs(std::vector<std::string> &arguments);
        void createSocket(void);
        void tryConnection(void);
        int getFd(void) const;

        const std::string ReadFromServer(void);
        bool selectEvent(void);
    private:
        int _port;
        std::string _machineName;
        int _fd;
        struct sockaddr_in saddr;
};

#endif /* CLIENT_HPP_ */