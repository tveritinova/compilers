#include "IRTranslate.h"

void IRTranslate::visit(const Program* program) {

	std::cout << "in visit prog" << std::endl;

	if (program == nullptr) {
        return;
    }

    program->_main_class->accept(this);

    if (program->_classes) {
        program->_classes->accept(this);
    }

	lastTranslation = resultTranslation;

	while (lastTranslation != nullptr) {

		//std::cout << "--- result tree not nullptr ---" << std::endl;

		std::cout << std::endl << " ++++ " << std::endl << lastTranslation->fragmentName << std::endl << " ++++ " << std::endl << std::endl;

		irtree.add_record(lastTranslation->fragmentName, 
			lastTranslation->fragmentName,
			lastTranslation->body->id, lastTranslation->body->label);

		lastTranslation->body->print(irtree);

		lastTranslation = lastTranslation->next;
	}

	irtree.end_printing(); 
	
	std::cout << "after while" << std::endl;
}

void IRTranslate::visit(const MainClass* main_class) {
	
	std::cout << std::endl << "~~~~~ in visit main class ~~~~~" << std::endl << std::endl;

	main_class->_main_body->accept(this);

	resultTranslation = new CCodeFragment("Main", new AR::X86MiniJavaFrame(), lastWrapper->to_stmt());
	lastWrapper = nullptr;
	lastTranslation = resultTranslation;
}

void IRTranslate::visit(const ClassDeclList* class_decl_list) {

	//std::cout << "in visit class decl list" << std::endl;

    if (class_decl_list->_new_class) {
        class_decl_list->_new_class->accept(this);
    }

    if (class_decl_list->_other_classes) {
        class_decl_list->_other_classes->accept(this);
    }
}


void IRTranslate::visit(const ClassDecl* class_decl) {

	//std::cout << "in visit class decl" << std::endl;

	std::cout << std::endl << "~~~~~ visit class " << class_decl->_class_id->String() << " ~~~~~" << std::endl << std::endl;

    currentClassName = class_decl->_class_id;

    if (class_decl->_vars) {
        class_decl->_vars->accept(this);
    } // useless

    if (class_decl->_methods) {
        class_decl->_methods->accept(this);
    }
}


void IRTranslate::visit(const MethodDeclList* method_decl_list) {

	//std::cout << "in visit met decl list" << std::endl;

	if (!method_decl_list) {
		assert(true);
		return;
	}

    if (method_decl_list->other_methods_decls_) {
        method_decl_list->other_methods_decls_->accept(this);
    }

    if (method_decl_list->method_decl_) {
		currentFrame = get_frame_for_method(method_decl_list->method_decl_->method_id_);
		currentMethodName = nullptr;
        method_decl_list->method_decl_->accept(this);
    }
}

void IRTranslate::visit(const MethodDecl* method_decl) {

	std::cout << std::endl << "~~~~~ visit method " << method_decl->method_id_->String() << std::endl << std::endl;

	currentMethodName =  method_decl->method_id_;

    if (method_decl->arg_list_) {
        method_decl->arg_list_->accept(this);
    } // useless???

    if (method_decl->var_decls_) {
        method_decl->var_decls_->accept(this);
    } // useless???

    if (method_decl->statements_) {
        method_decl->statements_->accept(this);
        lastWrapper = nullptr;
    }

	method_decl->return_expression_->accept(this);

	std::cout << "- in visit metho decl" << std::endl;

	if (lastStmtListBody.size() == 0) std::cout << "lastStmtListBody empty" << std::endl;

	const IStm* body(new ExpStm(irtree,
		new EseqExp(irtree, lastStmtListBody[lastStmtListBody.size()-1], lastWrapper->to_exp()))); // lastWrapper for return, lastStmtListBody for stmt lists 

	lastWrapper = nullptr;

	CCodeFragment* newTranslation = new CCodeFragment(
		currentClassName->String() + "_" + method_decl->method_id_->String(), 
		currentFrame, body);

	lastTranslation->next = newTranslation;
	lastTranslation = newTranslation;
}

void IRTranslate::visit(const StatementList* statement_list) {

	std::cout << "- in visit stmnt list" << std::endl;

	if (!statement_list) {
		lastStmtListBody.push_back(new ExpStm(irtree,new ConstExp(irtree,0)));
		return;
	}

    if (statement_list->other_statements_) {
    	std::cout << "other not null" << std::endl;
        statement_list->other_statements_->accept(this);
        statement_list->statement_->accept(this);
        const IStm* lastStmtListBody_ = lastStmtListBody[lastStmtListBody.size() - 1];
        lastStmtListBody.pop_back();
        lastStmtListBody.push_back(new SeqStm(irtree,lastStmtListBody_, lastWrapper->to_stmt()));
        std::cout << "ADDED LAST WRAPPER TO STMT LIST" << std::endl;
        lastWrapper = nullptr;
    } else {
    	std::cout << "other null" << std::endl;
    	statement_list->statement_->accept(this);
    	//if (lastStmt == nullptr) std::cout << "lastStmt null" << std::endl;
    	lastStmtListBody.push_back(lastWrapper->to_stmt());
    	std::cout << "INIT STMT LIST" << std::endl;
    	lastWrapper = nullptr;
    }

}


void IRTranslate::visit(const IfStatement* if_statement) {
			std::cout << "in visit if stm" << std::endl;


    if (if_statement == nullptr) {
    	assert(true);
        return;
    }

    if_statement->if_condition_->accept(this);
    const ISubtreeWrapper* ifExpWrapper = lastWrapper;



    if_statement->statement_if_true_->accept(this);

    const ISubtreeWrapper* thenStateWrapper;
    if (typeid(*if_statement->statement_if_true_) == typeid(StatementList)) {
    	std::cout  << std::endl << "+++++++++++++LIST IN IF+++++++++++++" << std::endl << std::endl;
    	thenStateWrapper = new StmWrapper(irtree, lastStmtListBody[lastStmtListBody.size()-1]);
    	lastStmtListBody.pop_back();
    } else {
    	thenStateWrapper = lastWrapper;
    	lastWrapper = nullptr;
    }

    if_statement->statement_if_false_->accept(this);
    const ISubtreeWrapper* elseStateWrapper;
    if (typeid(*if_statement->statement_if_false_) == typeid(StatementList)) {
    	std::cout  << std::endl << "+++++++++++++LIST IN IF+++++++++++++" << std::endl << std::endl;
    	elseStateWrapper = new StmWrapper(irtree, lastStmtListBody[lastStmtListBody.size() - 1]);
    	lastStmtListBody.pop_back();
    } else {
    	elseStateWrapper = lastWrapper;
    	lastWrapper = nullptr;
    }

    if (thenStateWrapper == nullptr){
    	assert(true);
    }

    IStm* body;
	Label t("true");
	Label f("false");
	Label q("quitCondition");

	std::cout << "before create if body" << std::endl;
 
	body = new SeqStm(irtree,
		new SeqStm(irtree,
			ifExpWrapper->to_cond(t, f),
			new SeqStm(irtree,
				new SeqStm(irtree,
					new LabelStm(irtree,t),
					new SeqStm(irtree,
						thenStateWrapper->to_stmt(),
						new JumpStm(irtree,new NameExp(irtree,q), {q}))),
				new SeqStm(irtree,
					new LabelStm(irtree,f),
					elseStateWrapper->to_stmt()))), 
		new LabelStm(irtree,q));

	lastWrapper = new StmWrapper(irtree,body);

	std::cout << "end visit if" << std::endl;
}



void IRTranslate::visit(const WhileStatement* while_statement) {
	std::cout << "in visit while stm" << std::endl;

    if (while_statement == nullptr) {
    	assert(true);
        return;
    }

    while_statement->loop_condition_->accept(this);
    const ISubtreeWrapper* conditionExpWrapper = lastWrapper;
    lastWrapper = nullptr;
    while_statement->inloop_statement_->accept(this);
    const ISubtreeWrapper* inloopStmtWrapper;
    if (typeid(*(while_statement->inloop_statement_)) == typeid(StatementList)) {
    	inloopStmtWrapper = new StmWrapper(irtree, lastStmtListBody[lastStmtListBody.size()-1]);
    	lastStmtListBody.pop_back();
    } else {
    	inloopStmtWrapper = lastWrapper;
    	lastWrapper = nullptr;
    }

    IStm* body;
	Label t("true");
	Label f("false");

	body = new SeqStm(irtree,
		new SeqStm(irtree,
			conditionExpWrapper->to_cond(t, f),
			new SeqStm(irtree,
				new LabelStm(irtree,t), 
				inloopStmtWrapper->to_stmt())), 
		new LabelStm(irtree,f)); // видимо f отдастся следущему

	lastWrapper = new StmWrapper(irtree,body);
}

 void IRTranslate::visit(const PrintStatement* print_statement) {
 			std::cout << "in visit print stm" << std::endl;


    if (print_statement == nullptr) {
    	assert(true); // useless ???
        return;
    }

    std::cout << "ir translate visit print stmnt" << std::endl;

    print_statement->expression_to_print_->accept(this);

	IStm* body = new ExpStm(irtree,
		new CallExp(irtree,
			new NameExp(irtree,Label("print")), 
			new ExpList(lastWrapper->to_exp(), nullptr)));
	lastWrapper = nullptr;

	lastWrapper = new StmWrapper(irtree,body);
}

void IRTranslate::visit(const AssignStatement* assign_statement) {

	std::cout << "in visit ass stm" << std::endl;

    if (assign_statement == nullptr) {
    	assert(true); // useless ???
        return;
    }

    const IExp* dst;

	if (currentFrame->CheckLocalOrFormal(assign_statement->lhs_var_id_).first) {
		std::cout << "local" << std::endl;
		dst = currentFrame->CheckLocalOrFormal(assign_statement->lhs_var_id_).second->get_exp(irtree,currentFrame->FP());
	} else {
		std::cout << "formal" << std::endl;
		dst = get_class_var_exp(assign_statement->lhs_var_id_);
	}


    assign_statement->rhs_expression_->accept(this);

	lastWrapper = new StmWrapper(irtree,new MoveStm(irtree,dst, lastWrapper->to_exp()));
}


void IRTranslate::visit(const AssignSubscriptStatement* node) {

	std::cout << "in visit ass subscript stmt" << std::endl;

    node->subscript_->accept(this);

    const IExp* dst;
	if (currentFrame->CheckLocalOrFormal(node->lhs_array_id_).first) {

		std::cout << "local" << std::endl;

		const IExp* arr;

		dst = new MemExp(irtree,
			new BinopExp(irtree,
				IRTree_OP::OP_BIN::PLUS_,
				arr,
				new BinopExp(irtree,
					IRTree_OP::OP_BIN::PLUS_,
					new BinopExp(irtree,
						IRTree_OP::OP_BIN::MULTIPLY_,
						lastWrapper->to_exp(),
						new ConstExp(irtree, WORD_SIZE)),
					new ConstExp(irtree,intSize))),
			WORD_SIZE);
		lastWrapper = nullptr;
	
	} else {

		std::cout << "formal" << std::endl;
 
		const IExp* arr;

		arr = get_class_var_exp(node->lhs_array_id_);

		dst = new MemExp(irtree,
			new BinopExp(irtree,
				IRTree_OP::OP_BIN::PLUS_,
				arr,
				new BinopExp(irtree,
					IRTree_OP::OP_BIN::PLUS_,
					new BinopExp(irtree,
						IRTree_OP::OP_BIN::MULTIPLY_, 
						lastWrapper->to_exp(),
						new ConstExp(irtree,WORD_SIZE)),
					new ConstExp(irtree,intSize))),
			WORD_SIZE);
		lastWrapper = nullptr;
	}

	const IStm* body;

	node->rhs_expression_->accept(this);

	body = new MoveStm(irtree,dst, lastWrapper->to_exp());
	lastWrapper = nullptr;

	lastWrapper = new StmWrapper(irtree,body);
}



void IRTranslate::visit(const BinaryExpression* binary_expression) {

	std::cout << "in visit bin exp" << std::endl;

    if (binary_expression == nullptr) {
    	assert(true);
        return;
    }

    binary_expression->lhs_expression_->accept(this);
    const ISubtreeWrapper* left_wrapper = lastWrapper;
    lastWrapper = nullptr;
    binary_expression->rhs_expression_->accept(this);
    const ISubtreeWrapper* right_wrapper = lastWrapper;
    lastWrapper = nullptr;

    switch (binary_expression->binary_operator_) {
    case BinaryOperator::ADD_: 

    	lastWrapper = new ExpWrapper(irtree,new BinopExp(irtree,IRTree_OP::OP_BIN::PLUS_,
			left_wrapper->to_exp(),
			right_wrapper->to_exp()));
    	break;

    case BinaryOperator::SUB_:

    	lastWrapper = new ExpWrapper(irtree,new BinopExp(irtree,IRTree_OP::OP_BIN::MINUS_, 
    		left_wrapper->to_exp(),
			right_wrapper->to_exp()));
    	break;

    case BinaryOperator::MUL_:

    	lastWrapper = new ExpWrapper(irtree,new BinopExp(irtree,IRTree_OP::OP_BIN::MULTIPLY_,
			left_wrapper->to_exp(),
			right_wrapper->to_exp()));
    	break;

    case BinaryOperator::LESS_:
    	lastWrapper = new LessExpWrapper(irtree,left_wrapper->to_exp(), right_wrapper->to_exp());
    	break;

    case BinaryOperator::AND_: 
    	lastWrapper = new AndExpWrapper(irtree,left_wrapper->to_exp(), right_wrapper);
    	break;

    default:
        break;
    }

    std::cout << "end visit binary" << std::endl;
}


void IRTranslate::visit(const SubscriptExpression* node) {

		std::cout << "in visit subs exp" << std::endl;


    node->expression_->accept(this); // expression[subscript]
    const ISubtreeWrapper* expression_wrapper = lastWrapper;
    lastWrapper = nullptr;
    node->subscript_->accept(this);
    const ISubtreeWrapper* subscript_wrapper = lastWrapper;
    lastWrapper = nullptr;

	IExp* body = new MemExp(irtree,
			new BinopExp(irtree,
				IRTree_OP::OP_BIN::PLUS_,
				expression_wrapper->to_exp(),
				new BinopExp(irtree,
					IRTree_OP::OP_BIN::PLUS_,
					subscript_wrapper->to_exp(),
					new ConstExp(irtree,intSize))),
			WORD_SIZE);


	lastWrapper = new ExpWrapper(irtree,body);
}


void IRTranslate::visit(const LengthExpression* node) {
		std::cout << "in visit len exp" << std::endl;


	node->expression_->accept(this);
	IExp* body = new MemExp(irtree,lastWrapper->to_exp(), intSize);
	lastWrapper = nullptr;
	lastWrapper = new ExpWrapper(irtree,body);
}

void IRTranslate::visit(const MethodCallExpression* node) {
		
	std::cout << "in visit method call exp" << std::endl;

	node->expression_->accept(this);
	const ISubtreeWrapper* classWrapper = lastWrapper;
	lastWrapper = nullptr;

	std::cout << "before visit args" << std::endl;

	if (node->other_expressions_) {
		node->other_expressions_->accept(this); // args
	} else {
		std::cout << "ARGS NULL" << std::endl;
		lastExpListBody = nullptr;
	}

	std::cout << "after visit args" << std::endl;

	ExpList* list(new ExpList(classWrapper->to_exp(), lastExpListBody));
	lastExpListBody = nullptr;

	std::string class_name;
	for (auto it: table->get_classes()) {
		if (it.second->has_method(node->method_id_)) {
			class_name = it.first->String();
		}
	} 
	
	IExp* body = new CallExp(irtree,
		new NameExp(irtree,Label(class_name+"_"+node->method_id_->String())), list);
		
	lastWrapper = new ExpWrapper(irtree,body);
}

void IRTranslate::visit(const ExpressionList* expression_list) {

	std::cout << "in visit exp list" << std::endl;

	if (expression_list == nullptr) {
		lastExpListBody = nullptr;
        return;
    }

    expression_list->expression_->accept(this);
    const IExp* head = lastWrapper->to_exp();
    lastWrapper = nullptr;

    if (expression_list->other_expressions_) {
        expression_list->other_expressions_->accept(this);
        lastExpListBody = new ExpList(head, lastExpListBody);
    } else {
    	lastExpListBody = new ExpList(head, nullptr);
    }
}

void IRTranslate::visit(const IntExpression* node) {
		std::cout << "in visit int exp" << std::endl;

	lastWrapper = new ExpWrapper(irtree,new ConstExp(irtree,node->val));
}

void IRTranslate::visit(const BoolExpression* node) {
		std::cout << "in visit bool exp" << std::endl;

	lastWrapper = new ExpWrapper(irtree,new ConstExp(irtree,node->b_ ? 1 : 0));
}

void IRTranslate::visit(const IdExpression* node) {

	std::cout << "in visit id exp" << std::endl;

	const IExp* dst;
	if (currentFrame->CheckLocalOrFormal(node->id_).first) {
		std::cout << "local" << std::endl;
		const AR::IAccess* acc = currentFrame->CheckLocalOrFormal(node->id_).second;
		dst = acc->get_exp(irtree,currentFrame->FP());
	} else {
		std::cout << "formal" << std::endl;
		dst = get_class_var_exp(node->id_);
	}

	lastWrapper = new ExpWrapper(irtree,dst);
}

void IRTranslate::visit(const ThisExpression* node) {

	std::cout << "in visit this exp" << std::endl;

	lastWrapper = new ExpWrapper(irtree,
		new MemExp(irtree,
			new TempExp(irtree, Temp("r1")),
			referenceSize));

	std::cout << "in end of visit this expr" << std::endl;
}

void IRTranslate::visit(const NewIntArrayExpression* node) {

	std::cout << "in visit new int ar exp" << std::endl;

	node->subscript_expression_->accept(this);

	Temp temp("temp");

	IExp* body = new EseqExp(irtree,
		new MoveStm(irtree,
			new TempExp(irtree,temp),
			new CallExp(irtree,
				new NameExp(irtree,Label("malloc")),
				new ExpList(
					new BinopExp(irtree,
						IRTree_OP::OP_BIN::PLUS_,
						new BinopExp(irtree,
							IRTree_OP::OP_BIN::MULTIPLY_,
							lastWrapper->to_exp(),
							new ConstExp(irtree,WORD_SIZE)),
						new ConstExp(irtree,intSize)),
					nullptr))),
		new TempExp(irtree,temp));

	lastWrapper = nullptr; /// MAYBE THIS

	lastWrapper = new ExpWrapper(irtree,body);
}

void IRTranslate::visit(const NewObjectExpression* node) {

	std::cout << "in visit new obj exp" << std::endl;

	//int classSize = количество vars у node->new_object_type_ );

	int classSize = table->get_class(node->new_object_type_, {0,0})->get_fields().size();

	//std::cout << "~~~~ new object class" << std::endl;

	//std::cout << table->get_class(node->new_object_type_, {0,0})->get_class_id()->String() << std::endl;

	IExp* body= new CallExp(irtree,
			new NameExp(irtree,Label("malloc")),
			new ExpList(new ConstExp(irtree, classSize * WORD_SIZE),nullptr));

	lastWrapper = new ExpWrapper(irtree,body);
}

void IRTranslate::visit(const NegationExpression* node) {

	std::cout << "in visit neg exp" << std::endl;

	node->expression_to_negate_->accept(this);

	Temp temp("temp");
	Label t("true");
	Label f("false");
	Label q("quit");

	IExp* body= 
		new EseqExp(irtree,
			new SeqStm(irtree,
				new CJumpStm(irtree,
					IRTree_OP::OP_COMPARE::EQ_, lastWrapper->to_exp(), new ConstExp(irtree,1), t, f),
				new SeqStm(irtree,
					new SeqStm(irtree,
						new LabelStm(irtree,t),
						new SeqStm(irtree,
							new MoveStm(irtree,new TempExp(irtree,temp),new ConstExp(irtree,0)),
							new JumpStm(irtree,new NameExp(irtree,q), {q}))),
					new SeqStm(irtree,
						new LabelStm(irtree,f),
						new MoveStm(irtree,new TempExp(irtree,temp),new ConstExp(irtree,1))))),
			new EseqExp(irtree,
				new LabelStm(irtree,q),
				new MemExp(irtree,new TempExp(irtree,temp), booleanSize)));

	lastWrapper = nullptr;

	lastWrapper = new ExpWrapper(irtree,body);
}

const IExp* IRTranslate::get_class_var_exp(const Symbol* varName) {

	std::cout << std::endl << "+ + + + IN GET CLASS VAR EXP + + + + " << std::endl << std::endl;

	Position pos;
	int varOffset = 0;

	auto fields = table->get_class(currentClassName, pos)->get_fields();

	for (auto p: fields) {
		if (p.first == varName) {
			std::cout << "found " << varName->String() << std::endl << std::endl;
			return new MemExp(irtree,
				new BinopExp(irtree,
					IRTree_OP::OP_BIN::PLUS_, 
					new TempExp(irtree,Temp("r1")),
					new ConstExp(irtree,(varOffset+1)*WORD_SIZE)), 
				WORD_SIZE);
			break;
		}
		varOffset += 1;
	}


	//std::cout << varOffset << " " << fields.size() << std::endl;
	

	if (varOffset == fields.size()) {
		std::cout << "true" << std::endl;
		bool found = false;
		for (auto p: table->get_class(currentClassName, pos)->get_methods()) {
			if (p.first == currentMethodName) {
				int offset = 0;
				for (auto p2: p.second->get_args()) {
					if (p2.first == varName) {
						return new MemExp(irtree, new TempExp(irtree,Temp("r" + std::to_string(1 + 1 + offset))), WORD_SIZE);
					}
					offset += 1;
				}
				found = true;
				break;
			}
		}

		if (!found) {
			assert(false);
		}
	}

	
}


const AR::IFrame* IRTranslate::get_frame_for_method(const SymbolTable::Symbol* id) {

	Position pos;

	for (auto p: table->get_class(currentClassName, pos)->get_methods()) {
		if (p.first == id) {

			AR::IFrame* frame = new AR::X86MiniJavaFrame();

			VariableInfo thisVariable(currentClassName, SymbolTable::Symbol::GetIntern("this"));
			frame->AddFormal(thisVariable);

			auto args = p.second->get_args();
			for (auto it2 = args.begin(); it2 != args.end(); it2++) {
				frame->AddFormal(*(it2->second));
			}
			auto locals = p.second->get_locals();
			for (auto it2 = locals.begin(); it2 != locals.end(); it2++) {
				frame->AddLocal(*(it2->second));
			}

			frame->AddAddressExit();
			frame->AddAddressReturnValue();

			return frame;
		}
	}

	
}










