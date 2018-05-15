
#ifndef H_IRCLASSES
#define H_IRCLASSES

class ExpList;
class StmList;
class ConstExp;
class NameExp;
class TempExp;
class BinopExp;
class CallExp;
class EseqExp;
class MoveStm;
class JumpStm;
class CJumpStm;
class SeqStm;
class LabelStm;
class ExpStm;
class MemExp;

#include "IRTree.h"
#include "Temp.h"
#include "../Canonizer/IRTreeVisitor.h"


struct Label {
	std::string lName;
	Label(std::string _lName): lName(_lName) { /*std::cout << "init label " << lName << std::endl;*/ }
};


class IExp {
public:
	std::string id="";
	virtual ~IExp() {}
	virtual void print(IRTree& tree) const= 0;
	std::string label;

	virtual void accept(IRTreeVisitor* visitor) const = 0;
	virtual bool IsCommutative() const = 0;
	virtual bool IsAbsolutelyCommutative() const = 0;
};


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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }

};


class IStm {
public:
	std::string id = "";
	virtual ~IStm() {}
	virtual void print(IRTree& tree) const = 0;
	std::string label;


	virtual void accept(IRTreeVisitor* visitor) const = 0;

};

class StmList {
public:
	const IStm* cur;
	const StmList* others;

	StmList(const IStm* _cur, const StmList* _others) : cur(_cur), others(_others) {};

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }

    bool IsCommutative() const override { return true; }
    bool IsAbsolutelyCommutative() const override { return true; }
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }

    bool IsCommutative() const override { return true; }
    bool IsAbsolutelyCommutative() const override { return true; }
};

class TempExp : public IExp {
public:
	Temp temp;

	TempExp(IRTree& tree, Temp _temp): temp(_temp) {
		//std::cout << "create temp exp" << std::endl;
		label = "TEMP";
		id = tree.get_tree_name(label);
		std::cout << "create temp expr " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print temp exp" << std::endl;
		std::cout << "000000     " << temp.tName << std::endl;
		tree.add_record(id, label, tree.get_tree_name(temp.tName), temp.tName);
	}

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }

    bool IsCommutative() const override { return true; }
    bool IsAbsolutelyCommutative() const override { return Temp.tName == "TempHolderLocalId"; }
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }

    bool IsCommutative() const override { return false; }
    bool IsAbsolutelyCommutative() const override { return false; }
};


class MemExp : public IExp {
public:
	const IExp* exp; 
	const int size; 

	MemExp(IRTree& tree, const IExp* _exp, int _size): exp(_exp), size(_size){
		//std::cout << "create mem exp" << std::endl;
		label = "MEM";
		id = tree.get_tree_name(label);
		std::cout << "create mem expr " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print mem exp" << std::endl;
		tree.add_record(id, label, exp->id, exp->label);
		tree.add_record(id, label, 
			tree.get_tree_name("memzize_" + std::to_string(size)), 
			std::to_string(size));
		exp->print(tree);
	}

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }

    virtual bool IsCommutative() const override { return exp->IsAbsolutelyCommutative(); }
    virtual bool IsAbsolutelyCommutative() const override { return false; }

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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }

    bool IsCommutative() const override { return false; }
    bool IsAbsolutelyCommutative() const override { return false; }
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }

    bool IsCommutative() const override { return false; }
    bool IsAbsolutelyCommutative() const override { return false; }
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }
};



class ExpStm : public IStm {
public:
	const IExp* exp;

	ExpStm(IRTree& tree, const IExp* _exp) : exp(_exp) {
		label = "EXP";
		id = tree.get_tree_name(label);
		std::cout << "create exp stmt " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print exp stmnt" << std::endl;
		//std::cout << exp->id << std::endl;
		tree.add_record(id, label, exp->id, exp->label);
		exp->print(tree);
	}

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
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

	void accept(IRTreeVisitor* visitor) const {
        visitor->visit(this);
    }
};

#endif
