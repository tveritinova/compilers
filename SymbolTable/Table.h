#ifndef TABLE_H
#define TABLE_H

#include "Symbol.h"
#include "ClassInfo.h"
#include "../AST/grammar.h"
#include <map>
#include <set>


/*struct ScopeBlock {
    ScopeBlock(const std::map<const Symbol*, const VariableInfo*>& _variableBlock,
        const std::map<const Symbol*, const MethodInfo*>& _methodBlock,
        const ClassInfo* _currentClassInfo):
            methodBlock(_methodBlock),
            variableBlock(_variableBlock),
            currentClassInfo(_currentClassInfo) {}

    const std::map<const Symbol*, const MethodInfo*>& methodBlock;
    const std::map<const Symbol*, const VariableInfo*>& variableBlock;
    const ClassInfo* currentClassInfo;
};*/

class Table {

public:
    
    void add_class(const ClassInfo* class_info, Position pos);
    //void add_class_to_scope(const ClassInfo* class_id);
    //void add_method_to_scope(const MethodInfo* method_id);
    
    bool has_class(const Symbol* class_id) const { return classes.find(class_id) != classes.end();}

    const ClassInfo* get_class(const Symbol* class_id, Position pos) const;
    const VariableInfo* get_variable(const ClassInfo*  current_class, const MethodInfo* current_method,
        const Symbol* variable_id, Position pos) const;

    //const ClassInfo* get_scoped_class() const { return blocks.size() > 0 ? blocks.rbegin()->currentClassInfo : nullptr; }

    //const std::vector<const Symbol*>& get_classes_names() const { return classesNames; }

    std::map<const Symbol*, const ClassInfo*> get_classes() const { return classes; }

    bool DoesTypeHaveSuper(const ClassInfo* classInfo, const Symbol* super, Position pos) const;

private:
    std::map<const Symbol*, const ClassInfo*> classes;
    //std::set<const Symbol*> verifiedClasses;
    //std::vector<const Symbol*> classesNames;
};

#endif //TABLE_H