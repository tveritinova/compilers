#include "Symbol.h"

#include <map>
#include <iostream>

SymbolTable::
Symbol* SymbolTable::Symbol::GetIntern(const std::string &name) {

    static std::map<std::string, Symbol*> strings;
    auto result = strings.find(name);

    if (result != strings.end()) {
    	return result->second;
    }

    Symbol* newVal = new Symbol(name);
    strings[name] = newVal;

    return newVal;
}