#pragma once

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

};