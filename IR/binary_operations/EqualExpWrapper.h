#ifndef H_EQWAP
#define H_EQWAP

class EqualExpWrapper : public ISubtreeWrapper {
public:

	EqualExpWrapper(IRTree& _tree, const IExp* _left, const IExp* _right): 
		left(_left), right(_right), tree(_tree) {}

	const IExp* to_exp() const {
		Temp temp("temp");
		Label t("true");
		Label f("false");
		Label q("quit");
		return new EseqExp(tree,
			new SeqStm(tree,
				new CJumpStm(tree,IRTree_OP::OP_COMPARE::EQ_, left, right, t, f),
				new SeqStm(tree,
					new SeqStm(tree,
						new LabelStm(tree,t),
						new SeqStm(tree,
							new MoveStm(tree,new TempExp(tree,temp), new ConstExp(tree,1)),
							new JumpStm(tree,new NameExp(tree,q), {q}))),
					new SeqStm(tree,
						new LabelStm(tree,f),
						new MoveStm(tree, new TempExp(tree,temp), new ConstExp(tree,0))))),
			new EseqExp(tree,
				new LabelStm(tree,q),
				new MemExp(tree,new TempExp(tree,temp), booleanSize)));
	}

	const IStm* ToStm() const {
		return new ExpStm(tree,this->to_exp());
	}

	const IStm* ToConditional(const Label t, const Label f) const {
		std::cout << "eq exp to cond" << std::endl;
		return new CJumpStm(tree,IRTree_OP::OP_COMPARE::EQ_, left, right, t, f);
	}

private:
	const IExp* left;
	const IExp* right;
	IRTree& tree;
};

#endif