#ifndef CLASSINFO_H
#define CLASSINFO_H

#include "Symbol.h"
#include "MethodInfo.h"
#include "../AST/grammar.h"

class ClassInfo {

public:

    ClassInfo() {}

    ClassInfo(const Symbol* class_id_, const Symbol* base_class_id_ = nullptr): 
        class_id(class_id_), base_class_id(base_class_id_) {}

    const Symbol* get_class_id() const { return class_id; }
    const Symbol* get_base_class_id() const { return base_class_id; }

    const std::vector<std::pair<const Symbol*, const VariableInfo*>>& get_fields() const { return fields; }
    const std::vector<std::pair<const Symbol*, const MethodInfo*>>& get_methods() const { return methods; }

    void add_method(const MethodInfo* method_info);
    void add_field(const VariableInfo* variable_info);

    bool has_method(const Symbol* method_id) const;
    bool has_field(const Symbol* var_id) const;

private:
    std::vector<std::pair<const Symbol*, const VariableInfo*>> fields;
    std::vector<std::pair<const Symbol*, const MethodInfo*>> methods;

    const Symbol* class_id;
    const Symbol* base_class_id;
};

#endif //CLASS_INFO_H