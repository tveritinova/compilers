#pragma once

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

};