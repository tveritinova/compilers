#include "MethodInfo.h"
#include "DeclarationException.h"

const Symbol* MethodInfo::get_method_id() const {
    return method_id;
}

const Symbol* MethodInfo::get_return_type_id() const {
    return return_type_id;
}

const std::vector<std::pair<const Symbol*, const VariableInfo*>>& MethodInfo::get_args() const {
    return args;
}

const std::vector<std::pair<const Symbol*, const VariableInfo*>>& MethodInfo::get_locals() const {
    return locals;
}

void MethodInfo::add_arg(const VariableInfo* variable_info, Position pos) {

    for (auto p: args) {
        if (p.first == variable_info->get_id()) {
            throw DeclarationException("Already has var " + variable_info->get_id()->String() + " in arguments", pos);
            break;
        }
    }

    args.push_back(std::make_pair(variable_info->get_id(), variable_info));
}

void MethodInfo::add_local_var(const VariableInfo* variable_info) {
    locals.push_back(std::make_pair(variable_info->get_id(), variable_info));
}

bool MethodInfo::has_arg(const Symbol* var_id) const {
    int cnt = 0;
    for (auto p: args) {
        if (p.first == var_id) {
            cnt += 1;
        }
    }
    
    if (cnt == 1) {
        return true;
    }

    if (cnt == 0) {
        return false;
    }

    assert(false);
    return false;
}

bool MethodInfo::has_local_var(const Symbol* var_id) const {
    int cnt = 0;
    for (auto p: locals) {
        if (p.first == var_id) {
            cnt += 1;
        }
    }
    
    if (cnt == 1) {
        return true;
    }

    if (cnt == 0) {
        return false;
    }

    assert(false);
    return false;
}

const VariableInfo* MethodInfo::get_variable(const Symbol* var_id) const {

    if (has_arg(var_id)) {
        for (auto p: args) {
            if (p.first == var_id) {
                return p.second;
            }
        }
    }

    for (auto p: locals) {
        if (p.first == var_id) {
            return p.second;
        }
    }

    assert(false);
    return nullptr;
}