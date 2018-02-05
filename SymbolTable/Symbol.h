#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include "../AST/visitor.h"


namespace SymbolTable {

    class Symbol: public Visitable {

    public:

        const std::string& String() const { return str; }

        Symbol(const Symbol &) = delete;
        void operator=(const Symbol &) = delete;

        static Symbol *GetIntern(const std::string &name);

        void accept(Visitor* visitor) const override {
            visitor->visit(this);
        }

    private:
    	
    	Symbol(const std::string& str_): str(str_) {}

        std::string str;
    };

}

#endif //SYMBOL_H