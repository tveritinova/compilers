#ifndef H_EQWAP
#define H_EQWAP

class EqualExpWrapper : public ISubtreeWrapper {
public:

	EqualExpWrapper(IRTree& _tree, IExp* _left,  IExp* _right): 
		left(_left), right(_right), tree(_tree) {}

	IExp* to_exp() const override{
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

	IStm* to_stmt() const override{
		return new ExpStm(tree,this->to_exp());
	}

	IStm* to_cond(const Label t, const Label f) const override{
		std::cout << "eq exp to cond" << std::endl;
		return new CJumpStm(tree,IRTree_OP::OP_COMPARE::EQ_, left, right, t, f);
	}

private:
	IExp* left;
	IExp* right;
	IRTree& tree;
};

#endif