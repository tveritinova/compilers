#ifndef H_ORWAP
#define H_ORWAP



class OrExpWrapper : public ISubtreeWrapper {
public:
	OrExpWrapper(IRTree& _tree, IExp* _left, ISubtreeWrapper* _right): 
		left(_left), right(_right), tree(_tree) {}

	IExp* to_exp() const override{
		Temp temp("temp");
		Label t("true");
		Label f("false");
		Label q("quit");
		return new EseqExp(tree,
			new SeqStm(tree,
				new CJumpStm(tree,IRTree_OP::OP_COMPARE::EQ_, left, new ConstExp(tree,1), t, f),
				new SeqStm(tree,
					new SeqStm(tree,
						new LabelStm(tree,t),
						new SeqStm(tree,
							new MoveStm(tree,new TempExp(tree,temp), new ConstExp(tree,1)),
							new JumpStm(tree,new NameExp(tree,q),{q}))),
					new SeqStm(tree,
						new LabelStm(tree,f),
						new MoveStm(tree,new TempExp(tree,temp), right->to_exp())))),
			new EseqExp(tree,
				new LabelStm(tree,q),
				new MemExp(tree,new TempExp(tree,temp), booleanSize)));
	}

	IStm* to_stmt() const override{
		return new ExpStm(tree,this->to_exp());
	}

	IStm* to_cond(const Label t, const Label f) const override{
		std::cout << "or exp to cond" << std::endl;
		Label z("rightFalse");
		return new SeqStm(tree,
			new CJumpStm(tree,IRTree_OP::OP_COMPARE::EQ_, left, new ConstExp(tree,1), t, z),
			new SeqStm(tree,
				new LabelStm(tree,z),
				right->to_cond(t, f)));
	}

private:
	IExp* left;
	ISubtreeWrapper* right;
	IRTree& tree;
};

#endif