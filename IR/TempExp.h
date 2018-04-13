#pragma once

class TempExp : public IExp {
public:
	Temp temp;

	TempExp(IRTree& tree, Temp _temp); : temp(_temp) {
		//std::cout << "create temp exp" << std::endl;
		label = "TEMP";
		id = tree.get_tree_name(label);
		std::cout << "create temp expr " << id << std::endl;
	}

	void print(IRTree& tree) const {
		std::cout << "in print temp exp" << std::endl;
		std::cout << "000000     " << temp.tName << std::endl;
		tree.add_record(id, label, tree.get_tree_name(temp.tName), temp.tName);
	}
};