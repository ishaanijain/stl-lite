// Do not change this file
#ifndef VEC_EXCEPTION_H
#define VEC_EXCEPTION_H

#include <exception>
#include <string>

class VectorException : public std::exception {
private:
    std::string msg;
public:
    VectorException(const std::string& msg) : msg(msg + " on vector") { }
    
    const char* what() const noexcept override
    {
        return this->msg.c_str();
    }
};

#endif