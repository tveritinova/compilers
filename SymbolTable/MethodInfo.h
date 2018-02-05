#ifndef METHODINFO_H
#define METHODINFO_H

#include <map>

#include "Symbol.h"
#include "VariableInfo.h"
#include "Position.h"

class MethodInfo {

public:

    //MethodInfo() {}
    
    MethodInfo(const SymbolTable::Symbol* _return_type_id, const SymbolTable::Symbol* _method_id, const Position _pos): 
    return_type_id(_return_type_id), method_id(_method_id), pos(_pos) {}

    const SymbolTable::Symbol* get_method_id() const;
    const SymbolTable::Symbol* get_return_type_id() const;
    const std::map<const SymbolTable::Symbol*, const VariableInfo*>& get_args() const;
    const std::map<const SymbolTable::Symbol*, const VariableInfo*>& get_locals() const;

    void add_arg(const VariableInfo* variable_info, Position pos);
    void add_local_var(const VariableInfo* variable_info);

    bool has_arg(const SymbolTable::Symbol* var_id) const;
    bool has_local_var(const SymbolTable::Symbol* var_id) const;

    const VariableInfo* get_variable(const SymbolTable::Symbol* var_id) const;

private:

    std::map<const SymbolTable::Symbol*, const VariableInfo*> args;
    std::map<const SymbolTable::Symbol*, const VariableInfo*> locals;

    const SymbolTable::Symbol* return_type_id;
    const SymbolTable::Symbol* method_id;

    const Position pos;
};

#endif //METHODINFO_H