
#ifndef H_IRCLASSES
#define H_IRCLASSES

#include "IRTree.h"
#include "Temp.h"
#include "IStm.h"
#include "IExp.h"
#include "Label.h"


class ExpList {
public:

	const IExp* cur;
	const ExpList* others;

	ExpList(const IExp* _cur, const ExpList* _others): cur(_cur), others(_others) {};

	void print(/*IRTree& tree*/) const {
		std::cout << "in print exp list" << std::endl;

		if (!cur) {
			std::cout << "cur null" << std::endl;
			return;
		}

		cur->print(tree);
		std::cout << "after cur" << std::endl;
		if (others != nullptr) {
			others->print(tree);
		}
	}
};




class StmList {
public:
	const IStm* cur;
	const StmList* others;

	StmList(const IStm* _cur, const StmList* _others) : cur(_cur), others(_others) {};
};



//
// EXPRESSIONS
//


class ConstExp: public IExp {
public:
	int value;

	ConstExp(IRTree& tree, int _value): value(_value) {
		label = "CONST";
		id = tree.get_tree_name(label);
		std::cout << "create const expr " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print const exp" << std::endl;
		tree.add_record(id, label, 
			tree.get_tree_name("const_" + std::to_string(value)), 
			std::to_string(value));
	}
};

class NameExp: public IExp {
public:
	const Label label_class;

	NameExp(IRTree& tree, const Label _label): label_class(_label) {
		label = "NAME";
		id = tree.get_tree_name(label);
		std::cout << "create name expr " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print name exp" << std::endl;
		tree.add_record(id, label, tree.get_tree_name(label_class.lName), label_class.lName);
		std::cout << "end print name exp" << std::endl;
	}

};

class BinopExp : public IExp {
public:
	const IRTree_OP::OP_BIN binop;
	const IExp* left;
	const IExp* right;

	BinopExp(IRTree& tree, IRTree_OP::OP_BIN _binop, const IExp* _left, const IExp* _right): 
		binop(_binop), left(_left), right(_right){
		label = IRTree_OP::bin_to_string(_binop);
		id = tree.get_tree_name(label);
		std::cout << "create binop expr " << id << std::endl;
	};

	void print(IRTree& tree) const {
		std::cout << "in print binop exp" << std::endl;
		tree.add_record(id, label, left->id, left->label);
		tree.add_record(id, label, right->id, right->label);
		left->print(tree);
		right->print(tree);
	}

};


class CallExp : public IExp {
public:
	const IExp* func;
	ExpList* args;

	CallExp(IRTree& tree, const IExp* _func, ExpList* _args): func(_func),args(_args) {
		label = "CALL";
		id = tree.get_tree_name(label);
		std::cout << "create call expr " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print call exp" << std::endl;
		tree.add_record(id, label, func->id, func->label);

		func->print(tree);

		const ExpList* cur_list = args;
		while (cur_list) {
			tree.add_record(id, label, cur_list->cur->id, cur_list->cur->label);
			cur_list = cur_list->others;
		}

		args->print(tree);
	}
};


class EseqExp : public IExp {
public:
	const IStm* stm;
	const IExp* exp;

	EseqExp(IRTree& tree, const IStm* _stm, const IExp* _exp) : stm(_stm), exp(_exp) {
		label = "ESEQ";
		id = tree.get_tree_name(label);
		std::cout << "create eseq expr " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print eseq exp" << std::endl;

		if (stm == nullptr) std::cout << "stm null" << std::endl;
		if (exp == nullptr) std::cout << "exp null" << std::endl;

		tree.add_record(id, label, stm->id, stm->label);
		tree.add_record(id, label,  exp->id, exp->label);
		stm->print(tree);
		exp->print(tree);
	}
};



//
// STATEMENTS
//




class MoveStm : public IStm {
public:
	const IExp* left;
	const IExp* right;

	MoveStm(IRTree& tree, const IExp* _left, const IExp* _right) : left(_left), right(_right) {
		label = "MOVE";
		id = tree.get_tree_name(label);
		//std::cout << std::endl << "++++++" << std::endl << std::endl;
		std::cout << "create move stmnt " << id << std::endl;
		//std::cout << std::endl << "++++++" << std::endl << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print move stmnt" << std::endl;
		tree.add_record(id, label, left->id, left->label);
		tree.add_record(id, label, right->id, right->label);
		left->print(tree);
		right->print(tree);
	}
};


class JumpStm : public IStm {
public:
	const IExp* exp; 
	const std::vector<Label> targets; 

	JumpStm(IRTree& tree, const IExp* _exp, const std::vector<Label> _targets): 
		exp(_exp), targets(_targets) {
		label = "JUMP";
		id = tree.get_tree_name(label);
		std::cout << "create jump stmt " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print jump stmnt" << std::endl;
		tree.add_record(id, label, exp->id, exp->label);
		for (int i = 0; i < targets.size(); i++)
			tree.add_record(id, label, tree.get_tree_name(targets[i].lName), targets[i].lName);
		exp->print(tree);
	}
};


class CJumpStm : public IStm {
public:
	const IRTree_OP::OP_COMPARE relop;
	const IExp* left;
	const IExp* right;
	Label iftrue;
	Label iffalse;

	CJumpStm(IRTree& tree, const IRTree_OP::OP_COMPARE _relop, const IExp* _left, const IExp* _right, 
		Label _iftrue, Label _iffalse) :
		relop(_relop), left(_left), right(_right), 
		iftrue(_iftrue), iffalse(_iffalse) {
		label = "CJUMP";
		id = tree.get_tree_name(label);
		std::cout << "create c jump stmt " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print c jump stmnt" << std::endl;
		tree.add_record(id, label, tree.get_tree_name(IRTree_OP::compare_to_string(relop)), IRTree_OP::compare_to_string(relop));
		tree.add_record(id, label, left->id, left->label);
		tree.add_record(id, label, right->id, left->label);
		tree.add_record(id, label, tree.get_tree_name(iftrue.lName), iftrue.lName);
		tree.add_record(id, label, tree.get_tree_name(iffalse.lName), iffalse.lName);
		left->print(tree);
		right->print(tree);
	}
};


class SeqStm :public IStm {
public:
	const IStm* left;
	const IStm* right;

	SeqStm(IRTree& tree, const IStm* _left, const IStm* _right) : left(_left), right(_right) {
		label = "SEQ";
		id = tree.get_tree_name(label);
		std::cout << "create seq stmt " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print seq stmnt" << std::endl;

		if (left) {
			tree.add_record(id, label, left->id, left->label);
		}

		if (right) {
			tree.add_record(id, label, right->id, right->label);
		}

		if (left) {
			left->print(tree);
		}
		
		if (right) {
			right->print(tree);
		}
	}
};


class LabelStm: public IStm {
public:
	const Label label_class;

	LabelStm(IRTree& tree, const Label _label) : label_class(_label) {
		label = "LABEL";
		id = tree.get_tree_name(label);
		std::cout << "create label stmt " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print label stmnt" << std::endl;
		//std::cout << "() " << label_class.lName << std::endl;
		tree.add_record(id, label, tree.get_tree_name(label_class.lName), label_class.lName);
	}
};

#endif
