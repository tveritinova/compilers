#ifndef H_WRAPS
#define H_WRAPS

#include "IRTree_classes.h"
#include "IRTree_OP.h"


class ISubtreeWrapper {
public:
	virtual ~ISubtreeWrapper(){}
	virtual IExp* to_exp() const = 0;
	virtual IStm* to_stmt() const = 0;
	virtual IStm* to_cond(const Label t, const Label f) const = 0;
};


class ExpWrapper: public ISubtreeWrapper {
public:
		
	ExpWrapper(IRTree& _tree, IExp* _exp) : exp(_exp), tree(_tree) {}

	IExp* to_exp() const { std::cout << "exp to exp" << std::endl; return exp; }
	IStm* to_stmt() const { std::cout << "exp to stmt" << std::endl; return new ExpStm(tree, exp); }
		
	IStm* to_cond(const Label t, const Label f) const {
		std::cout << "exp to cond" << std::endl;
		return new CJumpStm(tree, IRTree_OP::OP_COMPARE::GT_, exp, new ConstExp(tree, 0), t, f);
	}

private:
	IExp* exp;
	IRTree& tree;
};


class StmWrapper : public ISubtreeWrapper {
public:
	StmWrapper(IRTree& _tree, IStm* _stm) : stm(_stm), tree(_tree) {}

	IExp* to_exp() const {
		std::cout << "stmt to exp" << std::endl;
		return new EseqExp(tree, stm, new ConstExp(tree, 0));
	}

	IStm* to_stmt() const { std::cout << "stmt to stmt" << std::endl; return stm; }

	IStm* to_cond(const Label t, const Label f) const {
		std::cout << "stmt to cond" << std::endl;
		return stm;
	}

private:
	IStm* stm;
	IRTree& tree;
};


#endif