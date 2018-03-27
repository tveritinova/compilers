#include <iostream>

#include "typechecker.h"
#include "../AST/grammar.h"
#include "../AST/type.h"
#include "../AST/expression.h"
#include "../AST/statement.h"
#include "DeclarationException.h"


void TypeChecker::visit(const Program* program) {

    //printf("in visit program\n");

    program->_main_class->accept(this);

    if (program->_classes) {
        program->_classes->accept(this);
    }
}

void TypeChecker::visit(const MainClass* main_class) {

    current_class = table.get_class(main_class->_class_id, main_class->pos);

    //std::cout << "-------" << std::endl;
    //std::cout << "current class: " << main_class->_class_id->String() << std::endl;
    //std::cout << "-------" << std::endl;

    /*if (current_class == nullptr) {
        std::cout << "checker in visit main class, current class null" << std::endl;
    }*/

    //std::cout << "checker before loop" << std::endl;

    for (auto p: current_class->get_methods()) {

        //std::cout << "checker in for main methods" << std::endl;

        if (p.first == Symbol::GetIntern("main")) {
            current_method = p.second;
            break;
        }
    }

    //std::cout << "checker before visit main body" << std::endl;

    main_class->_main_body->accept(this);
}

void TypeChecker::visit(const ClassDeclList* class_decl_list) {

    //std::cout << "checker in visit class list" << std::endl;

    if (class_decl_list->_new_class) {
        class_decl_list->_new_class->accept(this);
    }

    if (class_decl_list->_other_classes) {
        class_decl_list->_other_classes->accept(this);
    }
}

void TypeChecker::visit(const ClassDecl* class_decl) {

    const Symbol* base_class_id = class_decl->_base_class_id;
    const Symbol* class_id = class_decl->_class_id;

    while (base_class_id != nullptr) {

        if (class_decl->_class_id == base_class_id) {
            throw DeclarationException("cyclic inheritance at " + class_decl->_class_id->String() + 
                " and " + class_id->String(), class_decl->pos);
        }

        if (table.has_class(class_decl->_base_class_id)) {
            const ClassInfo* class_info = table.get_class(class_decl->_base_class_id, class_decl->pos);
            base_class_id = class_info->get_base_class_id();
            class_id = class_info->get_class_id();
        } else {
            break;
        }
    }

    if (class_decl->_vars) {
        class_decl->_vars->accept(this);
    }

    current_class = table.get_class(class_id, class_decl->pos);

    //std::cout << "-------" << std::endl;
    //std::cout << "current class: " << class_id->String() << std::endl;
    //std::cout << "-------" << std::endl;

    if (class_decl->_methods) {
        class_decl->_methods->accept(this);
    }

}

void TypeChecker::visit(const VarDeclList* var_decl_list) {

    if (var_decl_list->_other_var_decs) {
        var_decl_list->_other_var_decs->accept(this);
    }

    if (var_decl_list->_var_dec) {
        var_decl_list->_var_dec->accept(this);
    }
}

void TypeChecker::visit(const VarDecl* node) {

    //std::cout << node->_type->id->String() << std::endl;
    
    if (node->_type->id != Symbol::GetIntern("int") && 
        node->_type->id != Symbol::GetIntern("int[]") && 
        node->_type->id != Symbol::GetIntern("boolean")) {
        table.get_class(node->_type->id, node->pos);
    }
}

void TypeChecker::visit(const MethodDeclList* method_decl_list) {

    if (method_decl_list->other_methods_decls_) {
        method_decl_list->other_methods_decls_->accept(this);
    }

    if (method_decl_list->method_decl_) {
        method_decl_list->method_decl_->accept(this);
    }
}

void TypeChecker::visit(const MethodDecl* method_decl) {

    //std::cout << "in method decl " << method_decl->method_id_->String() << std::endl;

    //table.add_method_to_scope(method_decl->method_id_, method_decl->pos);

    if (method_decl->return_type_->id != Symbol::GetIntern("int") &&
        method_decl->return_type_->id != Symbol::GetIntern("int[]") &&
        method_decl->return_type_->id != Symbol::GetIntern("boolean") &&
        !table.has_class(method_decl->return_type_->id)) {
        throw DeclarationException("Not declared return type " + method_decl->return_type_->id->String(), 
            method_decl->pos);
    }

    //current_method = current_class->get_methods().at(method_decl->method_id_);

    for (auto p: current_class->get_methods()) {
        if (p.first == method_decl->method_id_) {
            current_method = p.second;
            break;
        }
    }

    if (method_decl->arg_list_) {
        method_decl->arg_list_->accept(this);
    }

    if (method_decl->var_decls_) {
        method_decl->var_decls_->accept(this);
    }


    if (method_decl->statements_) {
        method_decl->statements_->accept(this);
    }

    method_decl->return_expression_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    if (!(type == method_decl->return_type_->id)) {
        throw DeclarationException("Wrong return type from method " + 
            method_decl->method_id_->String() + 
            ": have " + type->String() +
            " expected " + method_decl->return_type_->id->String(), 
            method_decl->pos);
    }
}


void TypeChecker::visit(const ArgumentList* node) {

    if (node == nullptr) { return; }

    //printf("in arg list\n");

    //std::cout << "to find " + node->arg_id_->String() << std::endl;

    //for (auto it: current_method->get_args()) {
    //    std::cout << it.first->String() << std::endl;
    //}

    if (current_class->has_field(node->arg_id_)) {
        throw DeclarationException("Already has var " + node->arg_id_->String(), node->pos);
    }

    if (node->arg_type_->id != Symbol::GetIntern("int") &&
        node->arg_type_->id != Symbol::GetIntern("int[]") &&
        node->arg_type_->id != Symbol::GetIntern("boolean") &&
        !table.has_class(node->arg_type_->id)) {
        throw DeclarationException("Not declared argument type " + node->arg_type_->id->String(), 
            node->pos);
    }

    node->arg_id_->accept(this);

    if (node->other_args_) {
        node->other_args_->accept(this);
    }
}


void TypeChecker::visit(const StatementList* statement_list) {

    //printf("in stmnt list\n");

    if (statement_list == nullptr) {
        return;
    }


    if (statement_list->other_statements_) {
        statement_list->other_statements_->accept(this);
    }

    statement_list->statement_->accept(this);

}

void TypeChecker::visit(const AssignSubscriptStatement* node) {

    const VariableInfo* var = table.get_variable(current_class, current_method,
        node->lhs_array_id_, node->pos);

    if (var->get_type() != Symbol::GetIntern("int[]")) {
        throw DeclarationException("Trying to subscript " + var->get_type()->String() + " as array",
            node->pos);
    }

    node->subscript_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    if (type != Symbol::GetIntern("int")) {
        throw DeclarationException("Trying to use " + type->String() + " as array index", node->pos);
    }

    node->rhs_expression_->accept(this);

    type = types.top();
    types.pop();

    if (type != Symbol::GetIntern("int")) {
        throw DeclarationException("Trying to assign type " + type->String() + " to int array element", 
            node->pos);
    }
}

void TypeChecker::visit(const PrintStatement* print_statement) {

    //printf("checker in print statement\n");

    if (print_statement == nullptr) {
        return;
    }

    print_statement->expression_to_print_->accept(this);

    //std::cout << "checker after visit expression to print" << std::endl;

    if (types.empty()) {
        std::cout << "types stack empty" << std::endl;
    }

    const Symbol* type = types.top();
    types.pop();

    if (type != Symbol::GetIntern("int") &&
        type != Symbol::GetIntern("int[]") &&
        type != Symbol::GetIntern("boolean")) {
        throw DeclarationException("Has " + type->String() + " as type to print",
                                                print_statement->pos);
    }
}

void TypeChecker::visit(const IfStatement* if_statement) {

    //printf("in if stmnt\n");

    if (if_statement == nullptr) {
        return;
    }

    if_statement->if_condition_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    //std::cout << type->String() << std::endl;

    if (type != Symbol::GetIntern("boolean")) {
        throw DeclarationException("Has " + type->String() + " as if condition",
                                                if_statement->pos);
    }

    if_statement->statement_if_true_->accept(this);
    if_statement->statement_if_false_->accept(this);
}

void TypeChecker::visit(const WhileStatement* while_statement) {
    //printf("in stmnt\n");

    if (while_statement == nullptr) {
        return;
    }

    while_statement->loop_condition_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    if (type != Symbol::GetIntern("boolean")) {
        throw DeclarationException("Has " + type->String() + " as while condition",
                                                while_statement->pos);
    }

    while_statement->inloop_statement_->accept(this);
}

void TypeChecker::visit(const AssignStatement* assign_statement) {
    //printf("in stmnt\n");

    if (assign_statement == nullptr) {
        return;
    }

    const VariableInfo* var = table.get_variable(current_class, current_method,
        assign_statement->lhs_var_id_, assign_statement->pos);

    assign_statement->rhs_expression_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    if (var->get_type() != type) {
        throw DeclarationException("Expected " + var->get_type()->String() +
            " while assigning " + assign_statement->lhs_var_id_->String() +
            ", has " + type->String(), assign_statement->pos);
    }


}

void TypeChecker::visit(const ExpressionList* expression_list) {

    if (expression_list == nullptr) {
        return;
    }

    if (expression_list->other_expressions_) {
        expression_list->other_expressions_->accept(this);
    }

    expression_list->expression_->accept(this);
    
}

void TypeChecker::visit(const LengthExpression* length_expression) {

    if (length_expression == nullptr) {
        return;
    }

    length_expression->expression_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    if (type != Symbol::GetIntern("int[]")) {
        throw DeclarationException("Trying to get length of" + type->String(),
                                    length_expression->pos);
    }

    types.push(Symbol::GetIntern("int"));
}

void TypeChecker::visit(const NewIntArrayExpression* new_array_expression) {

    //printf("in new int arr exprs\n");

    if (new_array_expression == nullptr) {
        return;
    }

    new_array_expression->subscript_expression_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    if (type != Symbol::GetIntern("int")) {
        throw DeclarationException("Trying to use type " + type->String() + " as size of array ",
                                    new_array_expression->pos);
    }

    types.push(Symbol::GetIntern("int[]"));
}

void TypeChecker::visit(const NewObjectExpression* new_object_expression) {

    if (new_object_expression == nullptr) {
        return;
    }

    //std::cout << "in new object expression" << std::endl;

    const ClassInfo* class_info = table.get_class(new_object_expression->new_object_type_, 
        new_object_expression->pos);

    if (class_info == nullptr) {
        std::cout << "classinfo in new object expr null" << std::endl;
    }

    std::cout << "before push" << std::endl;

    std::cout << "to push " << class_info->get_class_id()->String() << std::endl;

    types.push(class_info->get_class_id());
}

void TypeChecker::visit(const BinaryExpression* binary_expression) {

    if (binary_expression == nullptr) {
        return;
    }

    binary_expression->lhs_expression_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    switch (binary_expression->binary_operator_) {
        case BinaryOperator::ADD_:
        case BinaryOperator::SUB_:
        case BinaryOperator::MUL_:
        case BinaryOperator::LESS_:

            if (type != Symbol::GetIntern("int")) {
                throw DeclarationException("Trying to apply math operation to " + 
                    type->String(), binary_expression->pos);
            }

            binary_expression->rhs_expression_->accept(this);
            type = types.top();
            types.pop();

            if (type != Symbol::GetIntern("int")) {
                throw DeclarationException("Trying to apply math operation to " +
                    type->String(), binary_expression->pos);
            }

            if (binary_expression->binary_operator_ == BinaryOperator::LESS_) {
                types.push(Symbol::GetIntern("boolean"));
            } else {
                types.push(Symbol::GetIntern("int"));
            }

            break;

        case BinaryOperator::AND_:

            if (type != Symbol::GetIntern("boolean")) {

                throw DeclarationException("Trying to apply logical operation to " +
                    type->String(), binary_expression->pos);
            }

            binary_expression->rhs_expression_->accept(this);
            type = types.top();
            types.pop();

            if (type != Symbol::GetIntern("boolean")) {

                throw DeclarationException("Trying to apply logical operation to " +
                    type->String(), binary_expression->pos);
            }

            types.push(Symbol::GetIntern("boolean"));

        default:
            break;
    }
}

void TypeChecker::visit(const NegationExpression* negation_expression) {

    if (negation_expression == nullptr) {
        return;
    }

    negation_expression->expression_to_negate_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    if (type != Symbol::GetIntern("boolean")) {

        throw DeclarationException("Expected boolean type, has " + type->String(),
                                                negation_expression->pos);
    }

    types.push(Symbol::GetIntern("boolean"));
}

void TypeChecker::visit(const IntExpression*) {
    //printf("in int expr\n");
    types.push(Symbol::GetIntern("int"));
}

void TypeChecker::visit(const BoolExpression*) {
    types.push(Symbol::GetIntern("boolean"));
}

void TypeChecker::visit(const MethodCallExpression* node) {

    //printf("in method call expr\n");

    node->expression_->accept(this);

    const Symbol* type = types.top();
    types.pop();

    if (type == Symbol::GetIntern("int") ||
        type == Symbol::GetIntern("int[]") ||
        type == Symbol::GetIntern("boolean")) {
        throw DeclarationException("Trying to call method of base class " + type->String(), node->pos);
    } else {

        //std::cout << "to call method of not base class" << std::endl;

        const ClassInfo* class_info = table.get_class(type, node->pos);

        //if (class_info == nullptr) {printf("nullptr\n");} else {printf("notttt\n");}

        if (!class_info->has_method(node->method_id_)) {
            throw DeclarationException("Class " + type->String() + " doesn't have method " 
                + node->method_id_->String(), node->pos);
        } else {

            //std::cout << "has method" << std::endl;

            //std::cout << current_class->get_class_id()->String() << std::endl;

            //std::cout << "return type " << class_info->get_methods().at(node->method_id_)->get_return_type_id()->String() << std::endl;

            for (auto p: class_info->get_methods()) {
                //std::cout << "in loop" << std::endl;
                //std::cout << p.first->String() << std::endl;
                //std::cout << node->method_id_->String() << std::endl;

                if (p.first == node->method_id_) {
                    std::cout << "push return type " << p.second->get_return_type_id()->String() << std::endl;
                    types.push(p.second->get_return_type_id());
                    break;
                }
            }

            //types.push(class_info->get_methods().at(node->method_id_)->get_return_type_id());
        }
    }

    //if (node->other_expressions_) { node->other_expressions_->accept(this); }
}

void TypeChecker::visit(const SubscriptExpression* node ) {

    node->expression_->accept(this);

    const Symbol* type = types.top();
    types.pop();
    std::cout << "popped " << type->String() << std::endl;

    if (type != Symbol::GetIntern("int[]")) {
        throw DeclarationException("Trying to get element of " + type->String() +
            " as in int array", node->pos);
    }

    node->subscript_->accept(this);

    type = types.top();
    types.pop();
    std::cout << "popped " << type->String() << std::endl;

    if (type != Symbol::GetIntern("int")) {
        throw DeclarationException("Cannot use " + type->String() + " as a number of element in int[]", node->pos);
    }

    types.push(Symbol::GetIntern("int"));
        std::cout << "pushed int "  << std::endl;

}

void TypeChecker::visit(const ThisExpression* node) {
    types.push(current_class->get_class_id());
}

void TypeChecker::visit(const IdExpression* node) {

    //printf("in id expression %s\n", node->id_->String().c_str());

    if (current_method->has_arg(node->id_)) {
        for (auto p: current_method->get_args()) {
            if (p.first == node->id_) {
                types.push(p.second->get_type());
                break;
            }
        }
        return;
    }

    if (current_method->has_local_var(node->id_)) {
        for (auto p: current_method->get_locals()) {
            if (p.first == node->id_) {
                types.push(p.second->get_type());
            }
        }
        return;
    }

    if (current_class->has_field(node->id_)) {

        for (auto p: current_class->get_fields()) {
            if (p.first == node->id_) {
                types.push(p.second->get_type());
                break;
            }
        }

        //types.push(current_class->get_fields().at(node->id_)->get_type());
        return;
    }

    throw DeclarationException("Var " + node->id_->String() + " not declared", node->pos);
}


