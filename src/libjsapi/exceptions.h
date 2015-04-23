#ifndef RS_JSAPI_EXCEPTIONS_H
#define RS_JSAPI_EXCEPTIONS_H

#include <exception>
#include <string>

#include <jsapi.h>

namespace rs {
namespace jsapi {

class Exception : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "An exception in JSAPI occurred";
    }
};

class RuntimeWrongThreadException : public Exception {
public:
    virtual const char* what() const noexcept override {
        return "Runtime call made from the wrong thread";
    }
};

class RuntimeThreadInstanceException : public Exception {
public:
    virtual const char* what() const noexcept override {
        return "A runtime is already active on this thread";
    }
};

class ScriptException : public Exception {
public:
    ScriptException(const char* message, JSErrorReport* error) :
        message(message != nullptr ? message : ""),
        filename(error->filename != nullptr ? error->filename : ""), 
        lineno(error->lineno),
        column(error->column), 
        linebuf(error->linebuf != nullptr ? error->linebuf : ""),
        tokenOffset(error->tokenptr - error->linebuf),
        uclinebuf(error->uclinebuf != nullptr ? error->uclinebuf : u""),
        uctokenOffset(error->uctokenptr - error->uclinebuf),
        errorNumber(error->errorNumber),
        exnType(error->exnType) {
    }
        
    virtual const char* what() const noexcept override {
        return message.length() > 0 ? message.c_str() : "An error or exception happened in JSAPI";
    }
    
    const std::string message;
    const std::string filename;
    const unsigned lineno;
    const unsigned column;
    const std::string linebuf;
    const unsigned tokenOffset;
    const std::u16string uclinebuf;
    const unsigned uctokenOffset;
    const unsigned errorNumber;
    const int16_t exnType;
};

class ValueCastException : public Exception {
public:
    virtual const char* what() const noexcept override {
        return "Invalid object or value cast";
    }    
};

class FunctionArgumentsIndexException : public Exception {
public:
    virtual const char* what() const noexcept override {
        return "The FunctionArguments index value was invalid";
    }    
};
    
}}
    
#endif	/* RS_JSAPI_EXCEPTIONS_H */

