
#include "../SymbolTable/Symbol.h"

class Type {
    
public:
    SymbolTable::Symbol* id;
};

enum BasicTypes {
    INT_, 
    BOOL_, 
    INT_ARRAY_
};

class BasicType: public Type {
public:

    BasicType(BasicTypes type_): type(type_){
        if (type == INT_) id = SymbolTable::Symbol::GetIntern("int");
        if (type == BOOL_) id = SymbolTable::Symbol::GetIntern("boolean");
        if (type == INT_ARRAY_) id = SymbolTable::Symbol::GetIntern("int[]");
    }

    BasicTypes type;
};

class ClassType: public Type {

public:
    ClassType(SymbolTable::Symbol * id_) {
        id = id_;
    }
};