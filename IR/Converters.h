#ifndef H_WRAPS
#define H_WRAPS

#include "IRTree_classes.h"
#include "IRTree_OP.h"


class ISubtreeWrapper {
public:
	virtual ~ISubtreeWrapper(){}
	virtual const IExp* to_exp() const = 0;
	virtual const IStm* to_stmt() const = 0;
	virtual const IStm* to_cond(const Label t, const Label f) const = 0;
};


class ExpWrapper: public ISubtreeWrapper {
public:
		
	ExpWrapper(IRTree& _tree, const IExp* _exp) : exp(_exp), tree(_tree) {}

	const IExp* to_exp() const { std::cout << "exp to exp" << std::endl; return exp; }
	const IStm* to_stmt() const { std::cout << "exp to stmt" << std::endl; return new ExpStm(tree, exp); }
		
	const IStm* to_cond(const Label t, const Label f) const {
		std::cout << "exp to cond" << std::endl;
		return new CJumpStm(tree, IRTree_OP::OP_COMPARE::GT_, exp, new ConstExp(tree, 0), t, f);
	}

private:
	const IExp* exp;
	IRTree& tree;
};


class StmWrapper : public ISubtreeWrapper {
public:
	StmWrapper(IRTree& _tree, const IStm* _stm) : stm(_stm), tree(_tree) {}

	const IExp* to_exp() const {
		std::cout << "stmt to exp" << std::endl;
		return new EseqExp(tree, stm, new ConstExp(tree, 0));
	}

	const IStm* to_stmt() const { std::cout << "stmt to stmt" << std::endl; return stm; }

	const IStm* to_cond(const Label t, const Label f) const {
		std::cout << "stmt to cond" << std::endl;
		return stm;
	}

private:
	const IStm* stm;
	IRTree& tree;
};


#endif