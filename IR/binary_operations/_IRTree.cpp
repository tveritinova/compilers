
#include "IRTree.h"

std::vector<std::string> IRTree::treeDependencies;

std::string IRTree::bin_to_string(OP_BIN operation); {

	switch (operation) {
	case OP_BIN::PLUS_: return "plus";
	case OP_BIN::MINUS_: return "minus";
	case OP_BIN::MULTIPLY_: return "mul";
	case OP_BIN::AND_: return "and";
	case OP_BIN::LESS_: return "less";
	case OP_BIN::GREATER_: return "greater";
	case OP_BIN::EQUAL_: return "eq";
	}
}

std::string IRTree::compare_to_string(OP_COMPARE operation) {

	switch (operation) {
	case OP_COMPARE::EQ_: return "EQ";
	case OP_COMPARE::LT_: return "LT";
	case OP_COMPARE::GT_: return "GT";
	}
}

OP_COMPARE IRTree::bin_to_compare(OP_BIN operation) {

	switch (operation) {
	case OP_BIN::LESS_: return OP_COMPARE::LT_;
	case OP_BIN::EQUAL_: return OP_COMPARE::EQ_;
	case OP_BIN::GREATER_: return OP_COMPARE::GT_;
	default: assert(true);
	}

	return OP_COMPARE::LT_;

}

std::string IRTree::GetTreeName(std::string name) {

	static std::map<std::string, int> all_tree_names;
	auto cached = all_tree_names.find(name);

	if (cached != all_tree_names.end()) {
		cached->second++;
		return name + "v" + std::to_string(cached->second);
	}

	all_tree_names.insert({ name, 0 });
	return name + "v0";
}

std::string IRTree::GetUniqueName(std::string name) {

	static std::map<std::string, int> all_names;
	auto cached = all_names.find(name);

	if (cached != all_names.end()) {
		cached->second++;
		return name + std::to_string(cached->second);
	}
	all_names.insert({ name, 0 });
	return name + "0";
}


void IRTree::print() {

	std::ofstream fout("ir_graph.dot");
	fout << "digraph G" << std::endl << "{" << std::endl;
	for (std::string s : treeDependencies) {
		std::cout << "loop treeDependencies" << std::endl;
		std::cout << s << std::endl;
		fout << s << std::endl;
	}
	fout << "}" << std::endl;
	fout.close();
}