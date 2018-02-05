#include "Table.h"
#include "DeclarationException.h"
#include <iostream>

/*void Table::add_class_to_scope(const ClassInfo* classToScope) {
    blocks.push_back(ScopeBlock(classToScope->get_fields(),classToScope->get_methods(), classToScope));
}

void Table::add_method_to_scope(const MethodInfo* methodToScope) {
    blocks.push_back(ScopeBlock(methodToScope->get_locals()));
}*/

const ClassInfo* Table::get_class(const Symbol* id, Position pos) const {

    auto res = classes.find(id);

    if (res != classes.end()) {
    	return res->second;
    } 

    throw DeclarationException("Not declared class " + id->String(), pos);
}

const VariableInfo* Table::get_variable(const ClassInfo*  current_class, const MethodInfo* current_method,
    const Symbol* id, Position pos) const {

    for (auto it_locals: current_method->get_locals()) {
        if (it_locals.second->get_id() == id) {
            return it_locals.second;
        }
    }

    for (auto it_fields: current_class->get_fields()) {
        if (it_fields.second->get_id() == id) {
            return it_fields.second;
        }
    }

    throw DeclarationException("Not declared var " + id->String(), pos);
}

void Table::add_class(const ClassInfo* class_info, Position pos) {

    auto found = classes.find(class_info->get_class_id());

    if (found != classes.end()) {
        throw DeclarationException("Class " + class_info->get_class_id()->String() + " already defined", pos);
    }

    classes[class_info->get_class_id()] = class_info;
}


