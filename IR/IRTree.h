
#ifndef H_IRTREE
#define H_IRTREE

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <cassert>

#include "IRTree_OP.h"

class IRTree {

public:

	IRTree():fout("ir_graph.dot") { 
		std::cout << "create IRTree" << std::endl;
		fout << "digraph G" << std::endl << "{" << std::endl; 
	}

	void add_record(std::string first_id, std::string first_label, 
		std::string second_id, std::string second_label) {

		std::cout << std::endl << "add record " << first_id << " " << second_id << std::endl << std::endl;
		
		fout << "{" << first_id << "[label=\"" << first_label << "\"]}";
		fout << "->";
		fout << "{" << second_id << "[label=\"" << second_label << "\"]};" << std::endl;
	}

	void end_printing() {
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