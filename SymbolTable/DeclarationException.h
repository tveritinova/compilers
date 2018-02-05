#ifndef DECLARATION_H
#define DECLARATION_H

#include <string>

class DeclarationException : public std::exception {
public:
    virtual char const *what() const noexcept override { return msgresult.c_str(); }

    DeclarationException(const std::string &message, Position pos) {
        msgresult += "(" + std::to_string(pos.x) + "," + std::to_string(pos.y) + "): ";
        msgresult += message + "\n";
    }
    
    virtual ~DeclarationException() throw() {}

private:
    std::string msgresult;
};

#endif //DECLARATION_Hs
