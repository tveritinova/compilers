#ifndef TABLE_VISITOR_H
#define TABLE_VISITOR_H

#include <iostream>
#include "../AST/visitor.h"
#include "../AST/grammar.h"
#include "../AST/type.h"
#include "../AST/expression.h"
#include "../AST/statement.h"
#include "Table.h"
#include "DeclarationException.h"

class TableVisitor : public Visitor {

public:
    TableVisitor() {};
    ~TableVisitor() {};

    virtual void visit(const Symbol*)  {};

    virtual void visit(const StatementList*) {};
    virtual void visit(const AssignSubscriptStatement*) {};
    virtual void visit(const PrintStatement*) {};
    virtual void visit(const IfStatement*) {};
    virtual void visit(const WhileStatement*) {};
    virtual void visit(const AssignStatement*) {};

    virtual void visit(const ExpressionList*) {};
    virtual void visit(const LengthExpression*) {};
    virtual void visit(const IdExpression*) {};
    virtual void visit(const ThisExpression*) {};
    virtual void visit(const IntExpression*) {};
    virtual void visit(const BoolExpression*) {};
    virtual void visit(const MethodCallExpression*) {};
    virtual void visit(const SubscriptExpression*) {};
    virtual void visit(const NewIntArrayExpression*) {};
    virtual void visit(const NewObjectExpression*) {};
    virtual void visit(const BinaryExpression*) {};
    virtual void visit(const NegationExpression*) {};

    virtual void visit(const VarDeclList*) {};
    virtual void visit(const VarDecl*) {};
    virtual void visit(const MethodDeclList*) {};
    virtual void visit(const MethodDecl*) {};
    virtual void visit(const ArgumentList*) {};

    Table get_table() const { return table;}

    void visit(const Program *node) {
        //std::cout << "before visit main class" << std::endl;
        node->_main_class->accept(this);
        //std::cout << "before visit other classes" << std::endl;
        if (node->_classes) {
            node->_classes->accept(this);
        }
        //std::cout << "after visit other classes" << std::endl;
    }

    void visit(const MainClass *node) {

        auto new_class = new ClassInfo(node->_class_id);

        auto method = new MethodInfo(Symbol::GetIntern("void"), Symbol::GetIntern("main"), node->pos);

        method->add_arg(new VariableInfo(Symbol::GetIntern("String[]"), node->_main_argv_id), node->pos);

        new_class->add_method(method);

        table.add_class(new_class, node->pos);
    }

    void visit(const ClassDeclList* class_decl_list) {

        if (class_decl_list->_new_class) {
            class_decl_list->_new_class->accept(this);
        }

        if (class_decl_list->_other_classes) {
            class_decl_list->_other_classes->accept(this);
        }
    }

    void visit(const ClassDecl *class_decl) {

        auto class_info = new ClassInfo(class_decl->_class_id, class_decl->_base_class_id);

        std::vector<const VarDecl*> class_fields_list_inverted;
        auto var_decs = class_decl->_vars;

        while (var_decs) {
            class_fields_list_inverted.push_back(var_decs->_var_dec);
            var_decs = var_decs->_other_var_decs;
        }

        for (int i=class_fields_list_inverted.size()-1; i >=0; i--) {
            class_info->add_field(new VariableInfo(class_fields_list_inverted[i]->_type->id, 
                class_fields_list_inverted[i]->_var_id));
        }

        auto method_decs = class_decl->_methods;

        while (method_decs) {
            
            auto method_decl = method_decs->method_decl_;

            if (class_info->has_method(method_decl->method_id_)) {
                throw DeclarationException("class " + class_info->get_class_id()->String() +
                    " already has method " + method_decl->method_id_->String(), method_decl->pos);
            }

            auto new_method = new MethodInfo(method_decl->return_type_->id, 
                method_decl->method_id_, method_decl->pos);

            auto arglist = method_decl->arg_list_;
            while (arglist) {
                new_method->add_arg(new VariableInfo(arglist->arg_type_->id, arglist->arg_id_), arglist->pos);
                arglist = arglist->other_args_;
            }

            /*auto vardecs = method_decl->var_decls_;
            while (vardecs) {
                new_method->add_local_var(new VariableInfo(vardecs->_var_dec->_type->id, 
                    vardecs->_var_dec->_var_id));

                vardecs = vardecs->_other_var_decs;
            }*/

            std::vector<const VarDecl*> vars_list_inverted;
            auto vardecs = method_decl->var_decls_;
            while (vardecs) {
                vars_list_inverted.push_back(vardecs->_var_dec);
                vardecs = vardecs->_other_var_decs;
            }

            for (int i=vars_list_inverted.size()-1; i >=0; i--) {
                new_method->add_local_var(new VariableInfo(vars_list_inverted[i]->_type->id, 
                    vars_list_inverted[i]->_var_id));
            }

            class_info->add_method(new_method);

            method_decs = method_decs->other_methods_decls_;
        }

        table.add_class(class_info, class_decl->pos);
    }

private:

    Table table;

};

#endif //TABLE_VISITOR_H
