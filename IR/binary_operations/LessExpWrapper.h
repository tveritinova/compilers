
#ifndef H_LSWAP
#define H_LSWAP

class LessExpWrapper : public ISubtreeWrapper {
public:
	LessExpWrapper(IRTree& _tree, IExp* _left, IExp* _right): 
		left(_left), right(_right), tree(_tree) {}

	IExp* to_exp() const override{
		return new BinopExp(tree, IRTree_OP::OP_BIN::MINUS_, right, left);
	}

	IStm* to_stmt() const override{
		return new ExpStm(tree, this->to_exp());
	}

	IStm* to_cond(const Label t, const Label f) const override {
		std::cout << "less exp to cond" << std::endl;
		return new CJumpStm(tree, IRTree_OP::OP_COMPARE::LT_, left, right, t, f);
	}

private:
	IExp* left;
	IExp* right;
	IRTree& tree;
};

#endif