//
// Created by Cho Yiu Ng on 20.11.19.
//

#ifndef LRUCACHE_EXCEPTIONS_H
#define LRUCACHE_EXCEPTIONS_H

#include <exception>

class LRUCacheExceptionBase: public std::exception {
public:

    LRUCacheExceptionBase(const std::string& message): myMessage(message) {};
    virtual ~LRUCacheExceptionBase() = default;

    virtual const char* what() const noexcept {
        return myMessage.c_str();
    }

private:

    std::string myMessage;

};

class ZeroCapacityException: public LRUCacheExceptionBase {
public:

    ZeroCapacityException():
    LRUCacheExceptionBase("Attempt to resize the capacity to zero") {}

private:

    std::string myErrorMessage;

};


#endif //LRUCACHE_EXCEPTIONS_H
