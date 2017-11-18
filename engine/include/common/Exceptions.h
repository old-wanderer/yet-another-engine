//
// Created by Андрей on 17.11.2017.
//

#ifndef YET_ANOTHER_ENGINE_EXCEPTIONS_H
#define YET_ANOTHER_ENGINE_EXCEPTIONS_H

#include <stdexcept>
#include <string>

#define NOT_IMPLEMENTED throw NotImplementedException(std::string("in file:").append(__FILE__).append(" on line ").append(std::to_string(__LINE__)))
#define TODO(mes) throw NotImplementedException(mes)

class NotImplementedException: public std::logic_error {
public:
    NotImplementedException(): std::logic_error("not implemented") {};
    explicit NotImplementedException(const std::string &message): std::logic_error(message) {};
};

#endif //YET_ANOTHER_ENGINE_EXCEPTIONS_H
