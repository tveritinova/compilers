
#ifndef H_IRTREE
#define H_IRTREE

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cassert>

#include "CCodeFragment.h"
#include "IRTree_OP.h"

class IRTree {

public:

	std::vector<CCodeFragment*> forest;

	IRTree():fout("ir_graph.dot") { 
		std::cout << "create IRTree" << std::endl;
		fout << "digraph G" << std::endl << "{" << std::endl; 
	}

	void add_record(/*std::string first_id, */std::string first_label, 
		/*std::string second_id,*/ std::string second_label) {

		std::cout << std::endl << "add record " << first_id << " " << second_id << std::endl << std::endl;
		
		fout << "{" << get_tree_name(first_label) << "[label=\"" << first_label << "\"]}";
		fout << "->";
		fout << "{" << get_tree_name(second_label) << "[label=\"" << second_label << "\"]};" << std::endl;
	}

	void print() {

		for (auto translation: forest) {
			this->add_record(
				translation->fragmentName, translation->fragmentName,
				translation->body->id, translation->body->label);

			translation->body->print(*this);
		}

		fout << "}" << std::endl;
		fout.close();
	}

	std::string get_tree_name(std::string name) {

		auto cached = all_tree_names.find(name);

		if (cached != all_tree_names.end()) {
			cached->second++;
			return name + "v" + std::to_string(cached->second);
		}

		all_tree_names.insert({ name, 0 });
		return name + "v0";
	}

private:

	std::ofstream fout;

	std::map<std::string, int> all_tree_names;
	std::map<std::string, int> all_names;
};

#endif //H_IRTREE