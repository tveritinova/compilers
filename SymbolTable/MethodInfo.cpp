#include "MethodInfo.h"
#include "DeclarationException.h"

const Symbol* MethodInfo::get_method_id() const {
    return method_id;
}

const Symbol* MethodInfo::get_return_type_id() const {
    return return_type_id;
}

const std::map<const Symbol*, const VariableInfo*>& MethodInfo::get_args() const {
    return args;
}

const std::map<const Symbol*, const VariableInfo*>& MethodInfo::get_locals() const {
    return locals;
}

void MethodInfo::add_arg(const VariableInfo* variable_info, Position pos) {
    if (args.find(variable_info->get_id()) != args.end()) {
        throw DeclarationException("Already has var " + variable_info->get_id()->String() + " in arguments", pos);
    }

    args[variable_info->get_id()] = variable_info;
}

void MethodInfo::add_local_var(const VariableInfo* variable_info) {
    locals[variable_info->get_id()] = variable_info;
}

bool MethodInfo::has_arg(const Symbol* var_id) const {
    return args.count(var_id) == 1;
}

bool MethodInfo::has_local_var(const Symbol* var_id) const {
    return locals.count(var_id) == 1;
}

const VariableInfo* MethodInfo::get_variable(const Symbol* var_id) const {

    if (has_arg(var_id)) {
        return args.at(var_id);
    }

    return locals.at(var_id);
}