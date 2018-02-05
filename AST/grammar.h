
#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "grammar_declaration.h"
#include "visitor.h"
#include "../SymbolTable/Symbol.h"
#include <vector>
#include <string>

class Program : public Visitable {

public:

    Program(const MainClass* main_class, const ClassDeclList* other_classes) :
        _main_class(main_class), _classes(other_classes) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const MainClass* _main_class;
    const ClassDeclList* _classes;
};

class MainClass: public Visitable {

public:

    MainClass(const SymbolTable::Symbol* class_id, const SymbolTable::Symbol* main_argv_id, const Statement* main_body, Position _pos)
        : _class_id(class_id), _main_argv_id(main_argv_id), _main_body(main_body) { pos = _pos; }  

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const SymbolTable::Symbol* _class_id;
    const SymbolTable::Symbol* _main_argv_id;
    const Statement* _main_body;
};

class ClassDecl: public Visitable {

public:

    ClassDecl(const SymbolTable::Symbol* class_id, const SymbolTable::Symbol* base_class_id,
        const VarDeclList* variables, const MethodDeclList* methods, Position _pos)
        : _class_id(class_id), _base_class_id(base_class_id), _vars(variables), _methods(methods) { 
            pos = _pos;
        }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const SymbolTable::Symbol* _class_id;
    const SymbolTable::Symbol* _base_class_id;
    const VarDeclList* _vars;
    const MethodDeclList* _methods;
};

class ClassDeclList: public Visitable {

public:

    ClassDeclList(const ClassDecl* new_class, const ClassDeclList* other_classes)
        : _new_class(new_class), _other_classes(other_classes) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }


    const ClassDecl* _new_class;
    const ClassDeclList* _other_classes;
};

class VarDecl: public Visitable {

public:
    VarDecl(const Type* type, const SymbolTable::Symbol* var_id, Position _pos)
        : _type(type), _var_id(var_id) { pos = _pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Type* _type;
    const SymbolTable::Symbol* _var_id;
};

class VarDeclList: public Visitable {

public:

    VarDeclList(const VarDecl* var_decl, const VarDeclList* other_var_decls)
        : _var_dec(var_decl), _other_var_decs(other_var_decls) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const VarDecl* _var_dec;
    const VarDeclList* _other_var_decs;
};

class MethodDeclList: public Visitable {

public:

    MethodDeclList(const MethodDecl* method, const MethodDeclList* other_methods_decls)
        : method_decl_(method), other_methods_decls_(other_methods_decls) {}

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const MethodDecl* method_decl_;
    const MethodDeclList* other_methods_decls_;
};

class MethodDecl: public Visitable {

public:

    MethodDecl(const Type* return_type, const SymbolTable::Symbol* method_id, const ArgumentList* arg_list,
        const VarDeclList* var_decls, const StatementList* statements, const Expression* return_expression,
        Position _pos)
        : return_type_(return_type), method_id_(method_id), arg_list_(arg_list),
          var_decls_(var_decls), statements_(statements), return_expression_(return_expression) {
            pos = _pos;
          }
    
    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Type* return_type_;
    const SymbolTable::Symbol* method_id_;
    const ArgumentList* arg_list_;
    const VarDeclList* var_decls_;
    const StatementList* statements_;
    const Expression* return_expression_;
};

class ArgumentList: public Visitable {

public:

    ArgumentList(const Type* arg_type, const SymbolTable::Symbol* arg_id, const ArgumentList* other_args, Position _pos)
        : arg_type_(arg_type), arg_id_(arg_id), other_args_(other_args) { pos = _pos; }

    virtual void accept(Visitor* visitor) const override {
        visitor->visit(this);
    }

    const Type* arg_type_;
    const SymbolTable::Symbol* arg_id_;
    const ArgumentList* other_args_;
};


#endif

