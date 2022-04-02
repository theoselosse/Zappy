/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** Error.hpp
*/

#ifndef ERROR_HPP_
#define ERROR_HPP_

#include <stdexcept>

class Error : public std::exception {
    public:
        Error(const std::string &msg);
        ~Error() = default;

        const char *what(void) const noexcept override;
    private:
        std::string _msg;
};

#endif /* ERROR_HPP_ */