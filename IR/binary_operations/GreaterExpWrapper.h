
#ifndef H_GTWAP
#define H_GTWAP

class GreaterExpWrapper: public ISubtreeWrapper {
public:
	GreaterExpWrapper(IRTree& _tree, IExp* _left, IExp* _right): 
		left(_left), right(_right), tree(_tree) {}

	IExp* to_exp() const {
		return new BinopExp(tree, IRTree_OP::OP_BIN::MINUS_, left, right);
	}

	IStm* to_stmt() const {
		return new ExpStm(tree, this->to_exp());
	}

	IStm* to_cond(const Label t, const Label f) const {
		std::cout << "gt exp to cond" << std::endl;
		return new CJumpStm(tree, IRTree_OP::OP_COMPARE::GT_, left, right, t, f);
	}

private:
	IExp* left;
	IExp* right;
	IRTree& tree;
};

#endif