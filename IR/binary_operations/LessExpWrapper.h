
#ifndef H_LSWAP
#define H_LSWAP

class LessExpWrapper : public ISubtreeWrapper {
public:
	LessExpWrapper(IRTree& _tree, const IExp* _left, const IExp* _right): 
		left(_left), right(_right), tree(_tree) {}

	const IExp* to_exp() const {
		return new BinopExp(tree, IRTree_OP::OP_BIN::MINUS_, right, left);
	}

	const IStm* to_stmt() const {
		return new ExpStm(tree, this->to_exp());
	}

	const IStm* to_cond(const Label t, const Label f) const {
		std::cout << "less exp to cond" << std::endl;
		return new CJumpStm(tree, IRTree_OP::OP_COMPARE::LT_, left, right, t, f);
	}

private:
	const IExp* left;
	const IExp* right;
	IRTree& tree;
};

#endif