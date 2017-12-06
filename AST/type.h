class Type {
    
public:
    std::string label;
};

enum BasicTypes {
    INT_, 
    BOOL_, 
    INT_ARRAY_
};

class BasicType: public Type {
public:

    BasicType(BasicTypes type_): type(type_){
        if (type == INT_) label = "int";
        if (type == BOOL_) label = "bool";
        if (type == INT_ARRAY_) label = "int[]";
    }

    BasicTypes type;
};

class ClassType: public Type {

public:
    ClassType(Symbol * id_): id(id_) {

        label = id->String();
    
    }
    
    Symbol* id;
};