#ifndef VARIABLEINFO_H
#define VARIABLEINFO_H

#include "Symbol.h"

using namespace SymbolTable;


class VariableInfo {
public:
	VariableInfo() {}
    VariableInfo(const Symbol* _type, const Symbol* _id): type(_type), id(_id) {}

    const Symbol* get_type() const { return type; }
    const Symbol* get_id() const { return id; }

private:
    const Symbol* type;
    const Symbol* id;
};

#endif //VARIABLEINFO_H